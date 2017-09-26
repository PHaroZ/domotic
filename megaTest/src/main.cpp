#include "Arduino.h"
#include "const.h"

#include "main.h"

#include "SNAP.h"
#include "SNAPChannelHardwareSerial.h"

#include "SPI.h"
#include "Debouncer.h"
#include "CoilManager.h"


SNAPChannelHardwareSerial snapChannelMaster = SNAPChannelHardwareSerial(&Serial3, SNAP_SPEED);
SNAP<16> snapMaster = SNAP<16>(&snapChannelMaster, SNAP_ADDRESS_MASTER, 24);

Debouncer<32> debouncer;
CoilManager coilManager;

void setup() {
  Serial.begin(115200);

  SPI.begin();
  { // config for ShiftIn read
    pinMode(SPI_SS_SWITCH, OUTPUT);
    digitalWrite(SPI_SS_SWITCH, HIGH);
  }
  debouncer.begin(HIGH);
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

  {
    if (debouncer.debounce(getShiftInData(2))) {
      if (!debouncer.state(8))
        coilManager.binarySwitch(0);
      for (uint8_t i = 0; i < debouncer.getDataWidth(); i++) {
        Serial.print(debouncer.state(i));
      }
      Serial.println();
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
  } else if (0x4 == commands[0]) {
    // snapMaster.waitForAck();
    snapMaster.sendStart(SNAP_ADDRESS_RFRECEIVER, SNAP_NO_ACK);
    snapMaster.sendDataByte('?');
    snapMaster.sendMessage();
    snapMaster.waitForAck();

    uint16_t duration = millis();
    while (!snapMaster.receivePacket() && millis() - duration < 20) ;
    if (snapMaster.receivePacket()) {
      duration = millis() - duration;
      Serial.print("SNAP response \"");
      Serial.print(snapMaster.getInt(0), BIN);
      Serial.print("\" received in ");
      Serial.print("SNAP response received in ");
      Serial.print(duration);
      Serial.println("ms");
      snapMaster.releaseLock();
    } else {
      Serial.println("no response");
    }
  }
} // testCommand

void actionDimmer1(byte power1, byte power2) {
  snapMaster.waitForAck();
  snapMaster.sendStart(SNAP_ADDRESS_DIMMER1, SNAP_ACK_WAIT_TIME);
  snapMaster.sendDataByte('L');
  snapMaster.sendDataByte(power1);
  snapMaster.sendDataByte(power2);
  snapMaster.sendMessage();
}
