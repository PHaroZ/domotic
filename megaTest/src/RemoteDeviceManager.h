#include "Arduino.h"
#include "const.h"

#include "SNAP.h"
#include "SNAPChannelHardwareSerial.h"

class RemoteDevice {
public:
  const uint8_t address;
  const uint32_t delayForResponse;
  const uint32_t delayBetweenQuery;
  void (* receiveCallback)(uint8_t *, size_t);
  uint32_t lastQueryTime;

  explicit RemoteDevice(uint8_t address, uint32_t delayForResponse,
    uint32_t delayBetweenQuery,
    void(*receiveCallback)(uint8_t *, size_t)) : address(address), delayForResponse(delayForResponse),
    delayBetweenQuery(delayBetweenQuery), receiveCallback(receiveCallback) { }

  bool hasOutgoingPayload() {
    return false;
  }

  uint8_t readOutgoingPayload(size_t index) {
    return 0x00;
  }

  size_t getOutgoingPayloadSize() {
    return 0;
  }

  void clearOutgoingPayload() {
    // nothing to do
  }
};

/**
 * remote device for which we can send data. Max data size is 16 bytes
 */
class RemoteDeviceActuator : public RemoteDevice {
private:
  // when it's >0 this means that a message should be send sooner as possible
  // with a payload corresponding to the first <code>outgoingPayloadSize</code> bytes of <code>outgoingPayloadBuffer</code>
  size_t outgoingPayloadSize        = 0;
  uint8_t outgoingPayloadBuffer[16] = { };
public:
  using RemoteDevice::RemoteDevice;
  explicit RemoteDeviceActuator(uint8_t address) : RemoteDevice(address, 0, 0, NULL) { }

  void setOutgoingPayload(uint8_t * payload, size_t size) {
    this->outgoingPayloadSize = size;
    for (size_t i = 0; i < size; i++) {
      this->outgoingPayloadBuffer[i] = payload[i];
    }
  }

  bool hasOutgoingPayload() {
    return this->outgoingPayloadSize > 0;
  }

  uint8_t readOutgoingPayload(size_t index) {
    return this->outgoingPayloadBuffer[index];
  }

  size_t getOutgoingPayloadSize() {
    return this->outgoingPayloadSize;
  }

  void clearOutgoingPayload() {
    this->outgoingPayloadSize = 0;
  }
};

class RemoteDeviceManager {
private:
  SNAPChannelHardwareSerial snapChannel = SNAPChannelHardwareSerial(RS485_SERIAL);
  SNAP<16> snap = SNAP<16>(&snapChannel, SNAP_ADDRESS_MASTER, RS485_PIN_TX_CONTROL);
  uint8_t incommingPayloadBuffer[16];
  size_t noDevice;
  RemoteDevice * devices;
  bool waitingForResponse;
  RemoteDevice * currentQueryDevice = NULL;

  inline RemoteDevice * getDevice(uint8_t index) {
    // return (RemoteDevice *) (this->devices + (index - 1));
    return &(this->devices[index]);
  }

  uint8_t getDeviceIndexFromAddress(uint8_t address) {
    for (uint8_t devinceIndex = 0; devinceIndex < this->noDevice; devinceIndex++) {
      if (this->getDevice(devinceIndex)->address == address) {
        return devinceIndex;
      }
    }
    return this->noDevice;
  }

  void processOutgoingMessage() {
    if (this->queryIsFree()) {
      for (uint8_t devinceIndex = 0; devinceIndex < this->noDevice; devinceIndex++) {
        RemoteDevice * device = this->getDevice(devinceIndex);
        if (device->hasOutgoingPayload()) {
          this->queryPrepare(device, false);
          for (size_t i = 0; i < device->getOutgoingPayloadSize(); i++) {
            this->snap.sendDataByte(device->readOutgoingPayload(i));
          }
          this->querySend();
          return;
        }
      }
    }
  }

  void processIncommingMessage() {
    while (this->snap.checkForPacket()) {
      uint8_t receivedFromIndex = this->getDeviceIndexFromAddress(snap.getSource());
      if (receivedFromIndex < this->noDevice) {
        RemoteDevice * device = this->getDevice(receivedFromIndex);
        void (* receiveCallback)(uint8_t *, size_t) = device->receiveCallback;
        if (NULL != receiveCallback) {
          size_t payloadSize = this->snap.readBytes(this->incommingPayloadBuffer, 16);
          // Serial.print(millis());
          // Serial.print("receive message from ");
          // Serial.println(this->snap.getSource());
          receiveCallback(this->incommingPayloadBuffer, payloadSize);
        }
        // } else {
        //   Serial.print("receive message from unknown source ");
        //   Serial.println(this->snap.getSource());
      }

      // response receive from lastQuery ?
      if (this->waitingForResponse && this->snap.getSource() == this->currentQueryDevice->address) {
        // yes it is, clear lastQuery infos
        this->setCurrentQueryDevice(NULL);
      }

      this->snap.releaseReceive();
    }
  }

  void setCurrentQueryDevice(RemoteDevice * device, bool waitingForResponse = false) {
    if (NULL != device) {
      device->lastQueryTime    = millis();
      this->waitingForResponse = waitingForResponse;
    } else {
      this->waitingForResponse = false;
    }
    this->currentQueryDevice = device;
  }

  bool isWaitingForResponse() {
    // response is waiting ?
    if (this->waitingForResponse) {
      // yes
      // do we wait for too long ?
      if (millis() - this->currentQueryDevice->lastQueryTime > this->currentQueryDevice->delayForResponse) {
        // stop waiting for a reponse
        this->setCurrentQueryDevice(NULL);
        return false;
      } else {
        return true;
      }
    } else {
      return false;
    }
  }

  bool queryIsFree() {
    return !this->isWaitingForResponse() && !this->snap.isWaitingForAck();
  }

  bool queryPrepare(RemoteDevice * device, bool waitingForResponse = false) {
    // if (!this->queryIsFree()) {
    //   return false;
    // } else {
    this->setCurrentQueryDevice(device, waitingForResponse);
    this->snap.sendStart(device->address, waitingForResponse ? SNAP_NO_ACK : SNAP_ACK_WAIT_TIME);
    return true;
    // }
  }

  void querySend() {
    this->snap.sendMessage();
  }

  void queryNextDevice() {
    if (this->queryIsFree()) {
      for (uint8_t devinceIndex = 0; devinceIndex < this->noDevice; devinceIndex++) {
        RemoteDevice * device = this->getDevice(devinceIndex);
        if ((device->delayBetweenQuery > 0) && (millis() - device->lastQueryTime > device->delayBetweenQuery)) {
          Serial.print(millis());
          Serial.print("query device ");
          Serial.println(device->address);
          this->queryPrepare(device, true);
          this->snap.sendDataByte('?');
          this->querySend();
          break;
        }
      }
    }
  }

public:
  RemoteDeviceManager() { }

  void begin(RemoteDevice * devices, size_t noDevice) {
    this->noDevice = noDevice;
    this->devices  = devices;

    this->snap.begin(SNAP_SPEED);
    this->snap.setPinRxDebug(LED_BUILTIN);
  }

  /**
   * in order :
   * - check SNAP ACK reception
   * - read response from remote device. If some data are received from a device,
   *    corresponding <code>receiveCallback</code> is called
   * - send waiting outgoint message
   * - query data from new device if necessary
   */
  void process() {
    this->processIncommingMessage();
    this->processOutgoingMessage();
    this->queryNextDevice();
  }
};
