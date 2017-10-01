#include "Orchestrator.h"

RemoteDeviceManager Orchestrator::remoteDeviceManager;
RemoteDevice Orchestrator::remoteDeviceRfReceiver(SNAP_ADDRESS_RFRECEIVER, 20, 100, Orchestrator::onRfReceive);
RemoteDeviceActuator Orchestrator::remoteDeviceDimmer1(SNAP_ADDRESS_DIMMER1);
RemoteDevice Orchestrator::remoteDevices[noRemoteDevices] = {
  Orchestrator::remoteDeviceRfReceiver,
  Orchestrator::remoteDeviceDimmer1,
};
SwitchManager<SwitchStatesType> Orchestrator::switchManager(Orchestrator::onSwitchChange);
CoilManager<uint32_t> Orchestrator::coilManager;

void Orchestrator::begin() {
  Orchestrator::remoteDeviceManager.begin(Orchestrator::remoteDevices, noRemoteDevices);
  Orchestrator::switchManager.begin(~SwitchStatesType(0));
  coilManager.begin();
}

void Orchestrator::process() {
  Orchestrator::remoteDeviceManager.process();
  Orchestrator::switchManager.process();
  Orchestrator::coilManager.process();
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

void Orchestrator::onRfReceive(uint8_t * data, size_t size) {
  { // the first two bytes correspond to 16 rf switches, each of then is mapped to a shutter
    uint16_t value = data[0] << 8 | data[1];

    if (value != 0) {
      Serial.print("SNAP response from rfReceiver \"");
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
