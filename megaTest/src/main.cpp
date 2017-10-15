#include "Arduino.h"
#include "SPI.h"

#include "const.h"
#include "main.h"
#include "Orchestrator.h"

// #include "MySensors.h"

Orchestrator orchestrator;

void presentation() {
  orchestrator.presentation();
}

void setup() {
  Serial.begin(115200);
  SPI.begin();

  orchestrator.begin();
}

void loop() {
  orchestrator.process();

  debugCpuSpeed(10000);
}

void receive(const MyMessage &message) {
  if (!orchestrator.onMyMessageReceive(message)) {
    Serial.print("Unsupported message : ");
    Serial.print("sensor=");
    Serial.print(message.sensor);
    Serial.print(" type=");
    Serial.print(message.type);
    Serial.print(" data=");
    Serial.println(message.data);
  }
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
