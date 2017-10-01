#ifndef const_h
#define const_h

#include "Arduino.h"

const int32_t SNAP_SPEED              = 57600;
const int16_t SNAP_ACK_WAIT_TIME      = 10;
const int16_t SNAP_NO_ACK             = 0;
const uint8_t SNAP_ADDRESS_MASTER     = 1;
const uint8_t SNAP_ADDRESS_DIMMER1    = 2;
const uint8_t SNAP_ADDRESS_RFRECEIVER = 3;
const uint8_t RS485_PIN_TX_CONTROL    = 24;

// HardwareSerial * RS485_SERIAL = &Serial3;
#define RS485_SERIAL &Serial3

// number of 75HC165N connected
const uint8_t NO_SHIFT_IN_PIC = 2;

const bool COIL_ON       = LOW;
const bool COIL_OFF      = HIGH;
const uint8_t COIL_DS    = 38;
const uint8_t COIL_ST_CP = 39;
const uint8_t COIL_SH_CP = 40;
const uint8_t COIL_OE    = 41;

const uint8_t SPI_SS_SWITCH = 8;

#endif // ifndef const_h
