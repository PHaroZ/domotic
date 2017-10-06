#include "Orchestrator.h"
#include "MySensors.h"

namespace {
Sensor sensorDimmer1Cold = { 1, S_DIMMER };
Sensor sensorDimmer1Warm = { 2, S_DIMMER };
const uint8_t sensorStartIndexForShutter = 100;
const uint8_t sensorStartIndexForBinary  = 115;
const uint8_t sensorStartIndexForSwitch  = 164;
}

// RemoteDevice part
RemoteDeviceManager Orchestrator::remoteDeviceManager;
RemoteDevice Orchestrator::remoteDeviceRfReceiver(SNAP_ADDRESS_RFRECEIVER, 20, 100, Orchestrator::onRfReceive);
RemoteDeviceActuator Orchestrator::remoteDeviceDimmer1(SNAP_ADDRESS_DIMMER1);
RemoteDevice Orchestrator::remoteDevices[noRemoteDevice] = {
  Orchestrator::remoteDeviceRfReceiver,
  Orchestrator::remoteDeviceDimmer1,
};

// switch part
SwitchManager<SwitchStatesType> Orchestrator::switchManager(Orchestrator::onSwitchChange);

// coil part
CoilManager<uint32_t> Orchestrator::coilManager;
namespace {
ShutterPowerGroup shutterPowerGroupVelux = ShutterPowerGroup(2000, 1);
ShutterPowerGroup shutterPowerGroupAC    = ShutterPowerGroup(2000, 5);
}
Shutter Orchestrator::shutters[noShutter] = {
  Shutter(shutterPowerGroupVelux, 10000),
  Shutter(shutterPowerGroupVelux, 30000),
  Shutter(shutterPowerGroupAC,    10000),
};

void Orchestrator::begin() {
  Orchestrator::remoteDeviceManager.begin(Orchestrator::remoteDevices, noRemoteDevice);
  Orchestrator::switchManager.begin(~SwitchStatesType(0));
  coilManager.begin(Orchestrator::shutters, noShutter, noBinary);
}

void Orchestrator::presentation() {
  {
    char buffer[25]; // 25 is the max size of MySensors description

    presentSensor(&sensorDimmer1Cold, strcpy_P(buffer, PSTR("Salon, dimmer1 froid")));
    presentSensor(&sensorDimmer1Warm, strcpy_P(buffer, PSTR("Salon, dimmer1 chaud")));
  }

  presentSensors(S_COVER, noShutter, sensorStartIndexForShutter, PSTR("Volet %02d"));
  presentSensors(S_BINARY, noBinary, sensorStartIndexForBinary, PSTR("Relais %02d"));
  presentSensors(S_BINARY, noSwitch, sensorStartIndexForSwitch, PSTR("Interrupteur %02d"));
}

void Orchestrator::process() {
  Orchestrator::remoteDeviceManager.process();
  Orchestrator::switchManager.process();
  Orchestrator::coilManager.process();
}

void Orchestrator::receive(const MyMessage &message) {
  // TODO
}

void Orchestrator::actionDimmer1Set(uint8_t id, uint8_t powerLvl) {
  uint8_t payload[] = { 'L', id, powerLvl };

  Orchestrator::remoteDeviceDimmer1.setOutgoingPayload(payload, sizeof(payload));
}

void Orchestrator::actionDimmer1Swap(uint8_t id) {
  uint8_t payload[] = { 'S', id };

  Orchestrator::remoteDeviceDimmer1.setOutgoingPayload(payload, sizeof(payload));
}

void Orchestrator::actionBinarySwapState(uint8_t id) {
  Orchestrator::coilManager.binarySwapState(id);
}

void Orchestrator::actionShutterSetClosingPercent(uint8_t id, uint8_t percent) {
  Orchestrator::coilManager.shutterSetClosingPercent(id, percent);
}

// *************************************************************************
// private methods bellow
// *************************************************************************

void Orchestrator::presentSensor(Sensor * sensor, const char * desc) {
  present(sensor->childSensorId, sensor->sensorType, desc, false);
}

void Orchestrator::presentSensors(uint8_t type, uint8_t no, uint8_t sensorStartIndex, const char * descTpl) {
  char buffer[25]; // 25 is the max size of MySensors description

  for (uint8_t index = 0; index < no; index++) {
    const uint8_t sensorId = sensorStartIndex + index;
    Sensor sensor = { sensorId, type };
    sprintf_P(buffer, descTpl, index + 1);
    Orchestrator::presentSensor(&sensor, buffer);
  }
}

void Orchestrator::onRfReceive(uint8_t * data, size_t size) {
  { // the first two bytes correspond to 16 rf switches, each of then is mapped to a shutter
    uint16_t value = data[0] << 8 | data[1];

    if (value != 0) {
      Serial.print(F("SNAP response from rfReceiver \""));
      Serial.print(value, BIN);
      Serial.println("\"");
      for (size_t i = 0; i < 16; i++) {
        if (bitRead(value, i)) {
          Orchestrator::coilManager.shutterSwapState(i);
        }
      }
    }
  }
}

void Orchestrator::onSwitchChange(SwitchStatesType states) {
  // each bit corresponds to the state of a switch which should be mapped to a binary coil
  // when a switch is pressed (LOW state) swap the state of a binary coil
  for (uint8_t i = 0; i < 16; i++) {
    if (!bitRead(states, i)) {
      Orchestrator::coilManager.binarySwapState(i);
    }
  }

  if (bitRead(states, 16)) {
    Orchestrator::actionDimmer1Swap(0);
  } else if (bitRead(states, 17)) {
    Orchestrator::actionDimmer1Swap(1);
  }
}
