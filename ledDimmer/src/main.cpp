// see https://arduino-info.wikispaces.com/ArduinoPower
// see http://bildr.org/2012/03/rfp30n06le-arduino/
// see
// https://electronics.stackexchange.com/questions/17116/how-to-drive-a-mosfet-with-an-optocoupler

#include "Arduino.h"
#include "main.h"

#include "SNAP.h"
#include "SNAP.cpp" // required, because of https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
#include "SNAPChannelSoftwareSerial.h"

const int32_t SNAP_SPEED         = 57600;
const int16_t SNAP_ACK_WAIT_TIME = 10;
const int16_t SNAP_NO_ACK        = 0;
const byte SNAP_ADDRESS_MASTER   = 1;
const byte SNAP_ADDRESS_DIMMER1  = 2;


const byte PIN_RS485_RX         = 7;
const byte PIN_RS485_TX         = 4;
const byte PIN_RS485_TX_CONTROL = 6;
const byte PIN_RELAY = 8;
const byte PIN_GATE1 = 3;
const byte PIN_GATE2 = 9;

const byte RELAY_ON  = 0;
const byte RELAY_OFF = 1;

SNAPChannelSoftwareSerial snapChannel = SNAPChannelSoftwareSerial(PIN_RS485_RX, PIN_RS485_TX);
SNAP<16> snap = SNAP<16>(&snapChannel, SNAP_ADDRESS_DIMMER1, PIN_RS485_TX_CONTROL);

#define noActuator 2
byte pinGates[noActuator] = { 3, 9 };
uint8_t powerLvls[noActuator] = { 0, 0 };

void setup() {
  snap.begin(SNAP_SPEED);

  for (size_t i = 0; i < noActuator; i++) {
    pinMode(pinGates[i], OUTPUT);
  }

  toggleRelay(false); // order matters
  pinMode(PIN_RELAY, OUTPUT);
}

void loop() {
  if (snap.checkForPacket()) {
    byte receivedCommand = snap.getByte(0);
    // Serial.println("received from master " + String(receivedCommand, HEX));

    if (receivedCommand == 'L') {
      uint8_t index    = snap.getByte(1);
      uint8_t powerLvl = snap.getByte(2);
      powerLight(index, powerLvl);
    } else if (receivedCommand == 'S') {
      uint8_t index    = snap.getByte(1);
      uint8_t powerLvl = powerLvls[index] ? 0 : 255;
      powerLight(index, powerLvl);
    }

    snap.releaseReceive();
  }
} // loop

void powerLight(uint8_t index, uint8_t powerLvl) {
  powerLvls[index] = powerLvl;

  bool powerRequired = false;
  for (size_t i = 0; i < noActuator; i++) {
    if (powerLvls[i]) {
      powerRequired = true;
      break;
    }
  }

  toggleRelay(powerRequired);

  // try to use fade effect
  //  int periode = 2000;
  // time = millis();
  // value = 128+127*cos(2*PI/periode*time);
  // analogWrite(ledpin, value);

  analogWrite(pinGates[index], powerLvl);
}

void toggleRelay(bool on) {
  digitalWrite(PIN_RELAY, on ? RELAY_ON : RELAY_OFF);
  // digitalWrite(LED_BUILTIN, on ? HIGH : LOW);
}
