#include "Arduino.h"
#include "const.h"

#include "main.h"

#include "RemoteDeviceManager.h"

#include "SPI.h"
#include "Debouncer.h"
#include "CoilManager.h"

RemoteDeviceManager removeDeviceManager;
RemoteDevice remoteDevices[RemoteDeviceIndex::count] = {
  RemoteDevice(SNAP_ADDRESS_RFRECEIVER, 20, 100, onRfReceive),
};

Debouncer<16> rfDebouncer;
Debouncer<32> switchDebouncer;
CoilManager coilManager;

void setup() {
  Serial.begin(115200);

  removeDeviceManager.begin(remoteDevices);

  SPI.begin();
  { // config for ShiftIn read
    pinMode(SPI_SS_SWITCH, OUTPUT);
    digitalWrite(SPI_SS_SWITCH, HIGH);
  }
  rfDebouncer.begin(LOW);
  switchDebouncer.begin(HIGH);
  coilManager.begin();
}

void loop() {
  removeDeviceManager.process();

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

  {
    if (switchDebouncer.debounce(getShiftInData(2))) {
      for (uint8_t i = 0; i < switchDebouncer.getDataWidth(); i++) {
        if (!switchDebouncer.state(i)) {
          coilManager.binarySwitch(i);
        }
      }
    }
  }

  coilManager.process();

  // debugCpuSpeed(10000);
} // loop

uint32_t getShiftInData(uint8_t size) {
  // see https://www.gammon.com.au/forum/?id=11979 for more details
  uint32_t shiftInData = 0 - 1;

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI_SS_SWITCH, LOW);
  digitalWrite(SPI_SS_SWITCH, HIGH);
  // uint32_t shiftInData = (SPI.transfer(0) & 0xFF);
  // shiftInData |= (SPI.transfer(0) & 0xFF) << 8;
  SPI.transfer(&shiftInData, size);
  SPI.endTransaction();
  return shiftInData;
}

void onRfReceive(uint8_t * data, size_t size) {
  uint16_t value = data[0] << 8 | data[1];

  if (value != 0) {
    Serial.print("SNAP response from rfReceiver \"");
    Serial.print(value, BIN);
    Serial.println("\"");
    for (size_t i = 0; i < 16; i++) {
      if (bitRead(value, i)) {
        coilManager.shutterSwith(i);
      }
    }
  }
}

void actionDimmer1(byte power1, byte power2) {
  SNAP<16> snap = removeDeviceManager.getSnap();
  snap.waitForAck();
  snap.sendStart(SNAP_ADDRESS_DIMMER1, SNAP_ACK_WAIT_TIME);
  snap.sendDataByte('L');
  snap.sendDataByte(power1);
  snap.sendDataByte(power2);
  snap.sendMessage();
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
    coilManager.binarySwitch(commands[1]);
  }
} // testCommand
