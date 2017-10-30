#include "Orchestrator.h"
#include "MySensors.h"

namespace {
Sensor sensorDebug(254, S_CUSTOM);
SensorIndexed sensorDimmer1Cold(1, S_DIMMER, 0);
SensorIndexed sensorDimmer1Warm(2, S_DIMMER, 1);
const uint8_t sensorIndexStartForShutter = 100;
const uint8_t sensorIndexEndForShutter   = sensorIndexStartForShutter + noShutter - 1;
const uint8_t sensorIndexStartForBinary  = 115;
const uint8_t sensorIndexEndForBinary    = sensorIndexStartForBinary + noBinary - 1;
const uint8_t sensorIndexStartForSwitch  = 164;
const uint8_t sensorIndexEndForSwitch    = sensorIndexStartForSwitch + noSwitch - 1;
}

// RemoteDevice part
RemoteDevice Orchestrator::remoteDeviceRfReceiver(SNAP_ADDRESS_RFRECEIVER, 20, 100, Orchestrator::onRfReceive);
RemoteDeviceActuator Orchestrator::remoteDeviceDimmer1(SNAP_ADDRESS_DIMMER1);
RemoteDevice Orchestrator::remoteDevices[noRemoteDevice] = {
  Orchestrator::remoteDeviceRfReceiver,
  Orchestrator::remoteDeviceDimmer1,
};
RemoteDeviceManager Orchestrator::remoteDeviceManager;

// coils part
ShutterPowerGroup Orchestrator::shutterPowerGroupVelux(2000, 1);
ShutterPowerGroup Orchestrator::shutterPowerGroupAC(2000, 5);
Shutter Orchestrator::shutters[noShutter] = {
  Shutter(Orchestrator::shutterPowerGroupVelux,  5000),
  Shutter(Orchestrator::shutterPowerGroupVelux, 10000),
  Shutter(Orchestrator::shutterPowerGroupAC,    15000),
};
CoilManager<uint32_t> Orchestrator::coilManager(Orchestrator::onShutterMoveEnd);

// switches part
SwitchManager<SwitchStatesType> Orchestrator::switchManager(Orchestrator::onSwitchChange);
SwitchStatesType Orchestrator::switchStates = ~SwitchStatesType(0);

// MySensor message holder
MyMessage Orchestrator::myMessage(0, 0);

// dimmer initial states
uint8_t Orchestrator::dimmer1States[2] = { 0, 0 };


void Orchestrator::presentation() {
  {
    char buffer[25]; // 25 is the max size of MySensors description
    presentSensor(&sensorDebug, strcpy_P(buffer, PSTR("DEBUG")));
    presentSensor(&sensorDimmer1Cold, strcpy_P(buffer, PSTR("Salon, dimmer1 froid")));
    presentSensor(&sensorDimmer1Warm, strcpy_P(buffer, PSTR("Salon, dimmer1 chaud")));
  }

  presentSensors(S_COVER, noShutter, sensorIndexStartForShutter, PSTR("Volet %02d"));
  presentSensors(S_BINARY, noBinary, sensorIndexStartForBinary, PSTR("Relais %02d"));
  presentSensors(S_BINARY, noSwitch, sensorIndexStartForSwitch, PSTR("Interrupteur %02d"));
}

void Orchestrator::begin() {
  Orchestrator::remoteDeviceManager.begin(Orchestrator::remoteDevices, noRemoteDevice);
  Orchestrator::switchManager.begin(Orchestrator::switchStates);
  coilManager.begin(Orchestrator::shutters, noShutter, noBinary);

  // force sending current state to MySensors controller
  Orchestrator::sendMyMessageForAll();
}

void Orchestrator::process() {
  Orchestrator::remoteDeviceManager.process();
  Orchestrator::switchManager.process();
  Orchestrator::coilManager.process();
}

bool Orchestrator::onMyMessageReceive(const MyMessage &message) {
  if (message.sensor == sensorDebug.id) {
    // incomming data to this device should be send to debug purpose
    // in "cutecom" program input should be
    // 0;254;1;0;48;<PAYLOAD>
    // <PAYLOAD> is composed by :
    // 1st char specify the command
    // other for the command payload
    const char * commands = message.data;
    const char command    = commands[0];
    commands += 1;
    if ('A' == command) {
      char * pos = strchr(commands, ',');
      if (pos != NULL) {
        *pos = '\0';
        Orchestrator::actionShutterSetClosingPercent(atoi(commands), atoi(pos + 1));
        return true;
      }
    } else if ('B' == command) {
      Orchestrator::actionBinarySwapState(atoi(commands));
      return true;
    }
  } else if (message.sensor == sensorDimmer1Cold.id || message.sensor == sensorDimmer1Warm.id) {
    // dimmer1 command
    if (message.type == V_STATUS || message.type == V_PERCENTAGE) {
      uint8_t requestedLevel = atoi(message.data);
      requestedLevel *= ( message.type == V_STATUS ? 100 : 1 );
      SensorIndexed * sensor = NULL;
      if (message.sensor == sensorDimmer1Cold.id) {
        sensor = &sensorDimmer1Cold;
      } else if (message.sensor == sensorDimmer1Warm.id) {
        sensor = &sensorDimmer1Warm;
      }
      if (NULL != sensor) {
        Orchestrator::actionDimmer1Set(sensor->actuatorIndex, requestedLevel);
        return true;
      }
    }
  } else if (message.sensor >= sensorIndexStartForShutter && message.sensor <= sensorIndexEndForShutter) {
    // shutters command
    if (message.type == V_PERCENTAGE) {
      int8_t requestedLevel = atoi(message.data);
      Orchestrator::actionShutterSetClosingPercent(message.sensor - sensorIndexStartForShutter, requestedLevel);
      return true;
    }
  } else if (message.sensor >= sensorIndexStartForBinary && message.sensor <= sensorIndexEndForBinary) {
    // binary command
    if (message.type == V_STATUS) {
      bool requestedLevel = atoi(message.data);
      Orchestrator::coilManager.binarySetState(message.sensor - sensorIndexStartForBinary, requestedLevel);
      return true;
    }
  }
  return false;
} // receive

// *************************************************************************
// private methods bellow
// *************************************************************************

void Orchestrator::presentSensor(Sensor * sensor, const char * desc) {
  present(sensor->id, sensor->type, desc, false);
}

void Orchestrator::presentSensors(uint8_t type, uint8_t no, uint8_t sensorStartIndex, const char * descTpl) {
  char buffer[26] = { 0 }; // 25 is the max size of MySensors description

  for (uint8_t index = 0; index < no; index++) {
    const uint8_t sensorId = sensorStartIndex + index;
    Sensor sensor(sensorId, type);
    sprintf_P(buffer, descTpl, index + 1);
    Orchestrator::presentSensor(&sensor, buffer);
  }
}

void Orchestrator::onRfReceive(uint8_t * data, size_t size) {
  { // the first two bytes correspond to 16 rf switches, each of then is mapped to a shutter
    uint16_t value = data[0] << 8 | data[1];
    if (value != 0) {
      for (size_t i = 0; i < noShutter; i++) {
        if (bitRead(value, i)) {
          Orchestrator::coilManager.shutterSwapState(i);
        }
      }
      if (bitRead(value, noShutter)) {
        Orchestrator::coilManager.shutterOpenAll();
      }
    }
  }
}

void Orchestrator::onSwitchChange(SwitchStatesType states) {
  // compute the bits which go from HIGH to LOW
  SwitchStatesType changedBits = Orchestrator::switchStates & (~states);

  // each bit corresponds to the state of a switch which should be mapped to a binary coil
  // when a switch is pressed (LOW state) swap the state of a binary coil
  for (uint8_t i = 0; i < noBinary; i++) {
    if (bitRead(changedBits, i)) {
      Orchestrator::actionBinarySwapState(i);
    }
  }

  if (bitRead(changedBits, noBinary + 1)) {
    Orchestrator::actionDimmer1Swap(0);
  } else if (bitRead(changedBits, noBinary + 2)) {
    Orchestrator::actionDimmer1Swap(1);
  }

  Orchestrator::switchStates = states;
}

void Orchestrator::onShutterMoveEnd(uint8_t id, int8_t percent) {
  Orchestrator::sendMyMessageForShutter(id);
}

void Orchestrator::actionDimmer1Set(uint8_t id, uint8_t powerLvl) {
  uint8_t payload[] = { 'L', id, powerLvl };

  Orchestrator::remoteDeviceDimmer1.setOutgoingPayload(payload, sizeof(payload));
  Orchestrator::dimmer1States[id] = powerLvl;

  Orchestrator::sendMyMessageForDimmer1(id);
}

void Orchestrator::actionDimmer1Swap(uint8_t id) {
  Orchestrator::actionDimmer1Set(id, Orchestrator::dimmer1States[id] > 0 ? 0 : 100);
}

void Orchestrator::actionBinarySwapState(uint8_t id) {
  Orchestrator::coilManager.binarySwapState(id);
  Orchestrator::sendMyMessageForBinary(id);
}

void Orchestrator::actionShutterSetClosingPercent(uint8_t id, int8_t percent) {
  Orchestrator::coilManager.shutterSetClosingPercent(id, percent);
}

void Orchestrator::sendMyMessage(MyMessage &message) {
  send(message, false);
}

void Orchestrator::sendMyMessageForAll() {
  Orchestrator::sendMyMessageForDimmer1(sensorDimmer1Cold.actuatorIndex);
  Orchestrator::sendMyMessageForDimmer1(sensorDimmer1Warm.actuatorIndex);
  for (uint8_t i = 0; i < noShutter; i++) {
    Orchestrator::sendMyMessageForShutter(i);
  }
  for (uint8_t i = 0; i < noBinary; i++) {
    Orchestrator::sendMyMessageForBinary(i);
  }
}

void Orchestrator::sendMyMessageForDimmer1(uint8_t id) {
  uint8_t powerLvl       = Orchestrator::dimmer1States[id];
  SensorIndexed * sensor = NULL;

  if (id == sensorDimmer1Cold.actuatorIndex) {
    sensor = &sensorDimmer1Cold;
  } else if (id == sensorDimmer1Warm.actuatorIndex) {
    sensor = &sensorDimmer1Warm;
  }
  Orchestrator::sendMyMessage(Orchestrator::myMessage.setSensor(sensor->id).setType(V_PERCENTAGE).set(powerLvl));
}

void Orchestrator::sendMyMessageForBinary(uint8_t id) {
  Orchestrator::sendMyMessage(Orchestrator::myMessage.setSensor(sensorIndexStartForBinary
      + id).setType(S_BINARY).set(Orchestrator::coilManager.binaryGetState(id)));
}

void Orchestrator::sendMyMessageForShutter(uint8_t id) {
  Orchestrator::sendMyMessage(Orchestrator::myMessage.setSensor(sensorIndexStartForShutter
      + id).setType(V_PERCENTAGE).set(Orchestrator::coilManager.shutterGetClosingPercent(id)));
}
