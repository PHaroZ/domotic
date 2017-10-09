#include "Arduino.h"
#include "SPI.h"

#include "const.h"
#include "main.h"
#include "Orchestrator.h"

// #include "MySensors.h"

Orchestrator orchestrator;

void setup() {
  Serial.begin(115200);
  SPI.begin();

  orchestrator.begin();
}

void presentation() {
  orchestrator.presentation();
}

void loop() {
  orchestrator.process();

  // debugCpuSpeed(10000);
}

void receive(const MyMessage &message) {
  orchestrator.onMessageReceive(message);
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
