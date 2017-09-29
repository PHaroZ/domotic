#include "Arduino.h"
#include "const.h"

#include "main.h"

#include "RemoteDeviceManager.h"
#include "SwitchManager.h"

#include "SPI.h"
#include "Debouncer.h"
#include "CoilManager.h"

RemoteDeviceManager remoteDeviceManager;
RemoteDevice remoteDeviceRfReceiver      = RemoteDevice(SNAP_ADDRESS_RFRECEIVER, 20, 100, onRfReceive);
RemoteDeviceActuator remoteDeviceDimmer1 = RemoteDeviceActuator(SNAP_ADDRESS_DIMMER1);
#define noRemoteDevices 2
RemoteDevice remoteDevices[noRemoteDevices] = { remoteDeviceRfReceiver, remoteDeviceDimmer1 };

SwitchManager<SwitchStatesType> switchManager = SwitchManager<SwitchStatesType>(onSwitchChange);

CoilManager coilManager;

void setup() {
  Serial.begin(115200);

  SPI.begin();

  remoteDeviceManager.begin(remoteDevices, noRemoteDevices);
  switchManager.begin(((uint32_t) 0) - 1);
  coilManager.begin();
}

void loop() {
  if (Serial.available() > 0) {
    long startAt = millis();
    byte data[16];
    byte dataIndex = 0;
    while (Serial.available() > 0 || (millis() - startAt) < 100) {
      if (Serial.available() > 0) {
        data[dataIndex++] = Serial.read();
      }
    }
    Serial.print("testCommand");
    for (byte i = 0; i < dataIndex; i++) {
      Serial.print(' ');
      Serial.print(data[i]);
    }
    Serial.println(' ');
    testCommand(data);
  }


  remoteDeviceManager.process();

  switchManager.process();

  coilManager.process();

  // debugCpuSpeed(10000);
} // loop

void onRfReceive(uint8_t * data, size_t size) {
  { // the first two bytes correspond to 16 rf switches, each of then is mapped to a shutter
    uint16_t value = data[0] << 8 | data[1];

    if (value != 0) {
      Serial.print("SNAP response from rfReceiver \"");
      Serial.print(value, BIN);
      Serial.println("\"");
      for (size_t i = 0; i < 16; i++) {
        if (bitRead(value, i)) {
          coilManager.shutterSwapState(i);
        }
      }
    }
  }
}

void onSwitchChange(SwitchStatesType states) {
  // each bit corresponds to the state of a switch which should be mapped to a binary coil
  // when a switch is pressed (LOW state) swap the state of a binary coil
  for (uint8_t i = 0; i < sizeof(SwitchStatesType); i++) {
    if (!bitRead(states, i)) {
      coilManager.binarySwapState(i);
    }
  }
}

void actionDimmer1(byte power1, byte power2) {
  uint8_t payload[] = { 'L', power1, power2 };

  remoteDeviceDimmer1.setOutgoingPayload(payload, sizeof(payload));
}

void debugCpuSpeed(uint16_t noLoop) {
  static uint16_t currentNoLoop    = 0;
  static uint32_t startLoopingTime = 0;

  if (currentNoLoop++ == noLoop) {
    Serial.print(noLoop);
    Serial.print(" loops in");
    Serial.print(millis() - startLoopingTime);
    Serial.println("ms");
    currentNoLoop    = 0;
    startLoopingTime = millis();
  }
}

void testCommand(const byte * commands) {
  // use cutecom to debug and send hex data
  if (0x1 == commands[0]) {
    actionDimmer1(commands[1], commands[2]);
  } else if (0x2 == commands[0]) {
    coilManager.shutterSetClosingPercent(commands[1], commands[2]);
  } else if (0x3 == commands[0]) {
    coilManager.binarySwapState(commands[1]);
  }
} // testCommand
