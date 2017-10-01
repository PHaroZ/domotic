#include "Arduino.h"
#include "const.h"

#include "main.h"

#include "Orchestrator.h"

#include "SPI.h"

Orchestrator orchestrator;

void setup() {
  Serial.begin(115200);
  SPI.begin();

  orchestrator.begin();
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


  orchestrator.process();

  // debugCpuSpeed(10000);
} // loop

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
  if (0x01 == commands[0]) {
    orchestrator.actionDimmer1Set(commands[1], commands[2]);
  } else if (0x02 == commands[0]) {
    orchestrator.actionDimmer1Swap(commands[1]);
  } else if (0x20 == commands[0]) {
    orchestrator.actionShutterSetClosingPercent(commands[1], commands[2]);
  } else if (0x30 == commands[0]) {
    orchestrator.actionBinarySwapState(commands[1]);
  }
} // testCommand
