#include "Arduino.h"
#include "main.h"

#include "SNAP.h"
// #include "SNAPChannelSoftwareSerial.h"
#include "SNAPChannelHardwareSerial.h"

#include "RCSwitch.h"

#include "KeyedButtonMapper.h"

using ButtonStateType = uint16_t;
using ButtonKeyType   = uint32_t;

const int32_t SNAP_SPEED              = 57600;
const int16_t SNAP_ACK_WAIT_TIME      = 10;
const int16_t SNAP_NO_ACK             = 0;
const uint8_t SNAP_ADDRESS_MASTER     = 1;
const uint8_t SNAP_ADDRESS_DIMMER1    = 2;
const uint8_t SNAP_ADDRESS_RFRECEIVER = 3;


const uint8_t PIN_RS485_RX         = 7;
const uint8_t PIN_RS485_TX         = 4;
const uint8_t PIN_RS485_TX_CONTROL = 6;

ButtonKeyType rfButtonValues[] = {
  3544968, // remote1 buttonA
  3544964, // remote1 buttonB
  3544962, // remote1 buttonC
  3544961, // remote1 buttonD
};


// SNAPChannelSoftwareSerial snapChannel = SNAPChannelSoftwareSerial(PIN_RS485_RX, PIN_RS485_TX, SNAP_SPEED);
SNAPChannelHardwareSerial snapChannel = SNAPChannelHardwareSerial(&Serial, SNAP_SPEED);
SNAP<16> snap = SNAP<16>(&snapChannel, SNAP_ADDRESS_RFRECEIVER, PIN_RS485_TX_CONTROL);

RCSwitch rcSwitch = RCSwitch();

KeyedButtonMapper<ButtonStateType, ButtonKeyType> keyedButtonMapper;

void setup() {
  // Serial.begin(115200);

  // rcSwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2

  keyedButtonMapper.begin(rfButtonValues, sizeof(rfButtonValues) / sizeof(ButtonKeyType));

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // processRcSwitch();
  processSnap();
} // loop

void processRcSwitch() {
  if (rcSwitch.available() && 1 == rcSwitch.getReceivedProtocol() && 24 == rcSwitch.getReceivedBitlength()) {
    ButtonKeyType buttonKeyPressed = rcSwitch.getReceivedValue();
    // Serial.print("receive rf from ");
    // Serial.println(buttonKeyPressed);
    keyedButtonMapper.setHighStateFor(buttonKeyPressed);
    rcSwitch.resetAvailable();
  }
}

void processSnap() {
  if (snap.receivePacket()) {
    digitalWrite(LED_BUILTIN, HIGH);
    byte receivedCommand = snap.getByte(0);
    // Serial.print("snap message");
    // Serial.println(receivedCommand, HEX);
    if (receivedCommand == '?') { // state requested
      snap.releaseLock();
      { // send response
        snap.sendStart(SNAP_ADDRESS_MASTER, 0);
        {
          ButtonStateType buttonStates = keyedButtonMapper.readStates();
          // sendDataInt dependes of type ButtonStateType
          snap.sendDataInt(buttonStates);
          keyedButtonMapper.resetStates();
        }
        snap.sendMessage();
      }
    } else {
      snap.releaseLock();
    }

    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
