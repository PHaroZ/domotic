#include "Arduino.h"
#include "main.h"

#include "SNAP.h"
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


// const uint8_t PIN_RS485_RX         = 7;
// const uint8_t PIN_RS485_TX         = 4;
const uint8_t PIN_RS485_TX_CONTROL = 6;

const uint8_t PIN_RF_RX_CONTROL = 9;

ButtonKeyType rfButtonValues[] = {
  3544968, // remote1 buttonA
  3544964, // remote1 buttonB
  3544962, // remote1 buttonC
  3544961, // remote1 buttonD
};


SNAPChannelHardwareSerial snapChannel = SNAPChannelHardwareSerial(&Serial);
SNAP<16> snap = SNAP<16>(&snapChannel, SNAP_ADDRESS_RFRECEIVER, PIN_RS485_TX_CONTROL);

RCSwitch rcSwitch = RCSwitch();

KeyedButtonMapper<ButtonStateType, ButtonKeyType> keyedButtonMapper;

void setup() {
  snap.begin(SNAP_SPEED);
  snap.setPinRxDebug(LED_BUILTIN);

  Serial.println("setup");

  rcSwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2

  pinMode(PIN_RF_RX_CONTROL, OUTPUT);

  keyedButtonMapper.begin(rfButtonValues, sizeof(rfButtonValues) / sizeof(ButtonKeyType));
}

void loop() {
  processRcSwitch();
  processSnap();
} // loop

void processRcSwitch() {
  if (rcSwitch.available() && 1 == rcSwitch.getReceivedProtocol() && 24 == rcSwitch.getReceivedBitlength()) {
    ButtonKeyType buttonKeyPressed = rcSwitch.getReceivedValue();
    if (keyedButtonMapper.setHighStateFor(buttonKeyPressed)) {
      digitalWrite(PIN_RF_RX_CONTROL, HIGH);
    }
    rcSwitch.resetAvailable();
  }
}

void processSnap() {
  if (snap.receivePacket()) {
    byte receivedCommand = snap.getByte(0);
    if (receivedCommand == '?') { // state requested
      snap.releaseReceive();
      { // send response
        snap.sendStart(SNAP_ADDRESS_MASTER, 0);
        {
          ButtonStateType buttonStates = keyedButtonMapper.readStates();
          // use of "sendDataInt" depends on type of ButtonStateType
          snap.sendDataInt(buttonStates);
          if (buttonStates) {
            digitalWrite(PIN_RF_RX_CONTROL, LOW);
          }
          keyedButtonMapper.resetStates();
        }
        snap.sendMessage();
      }
    } else {
      snap.releaseReceive();
    }
  }
}
