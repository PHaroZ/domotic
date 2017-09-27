#include "Arduino.h"
#include "const.h"

#include "SNAP.h"
#include "SNAPChannelHardwareSerial.h"

enum RemoteDeviceIndex {
  RfReceiver,
  count // should always be the last
};

class RemoteDevice {
public:
  const uint8_t address;
  const uint32_t delayForResponse;
  const uint32_t delayBetweenQuery;
  void (* receiveCallback)(uint8_t *, size_t);
  uint32_t lastQueryTime;
  RemoteDevice(uint8_t address, uint32_t delayForResponse,
    uint32_t delayBetweenQuery,
    void(*receiveCallback)(uint8_t *, size_t)) : address(address), delayForResponse(delayForResponse),
    delayBetweenQuery(delayBetweenQuery), receiveCallback(receiveCallback) { }
};

class RemoteDeviceManager {
private:
  SNAPChannelHardwareSerial snapChannel = SNAPChannelHardwareSerial(RS485_SERIAL);
  SNAP<16> snap = SNAP<16>(&snapChannel, SNAP_ADDRESS_MASTER, RS485_PIN_TX_CONTROL);
  uint8_t incommingMessageBuffer[16];

  RemoteDevice * devices;
  inline RemoteDevice * getDevice(uint8_t index) {
    // return (RemoteDevice *) (this->devices + (index - 1));
    return &(this->devices[index]);
  }

  uint8_t getDeviceIndexFromAddress(uint8_t address) {
    for (uint8_t devinceIndex = 0; devinceIndex < RemoteDeviceIndex::count; devinceIndex++) {
      if (this->getDevice(devinceIndex)->address == address) {
        return devinceIndex;
      }
    }
    return RemoteDeviceIndex::count;
  }

  RemoteDevice * currentQueryDevice = NULL;

  void processIncommingMessage() {
    while (this->snap.receivePacket()) {
      uint8_t receivedFromIndex = this->getDeviceIndexFromAddress(snap.getSource());
      if (receivedFromIndex < RemoteDeviceIndex::count) {
        RemoteDevice * device = this->getDevice(receivedFromIndex);
        void (* receiveCallback)(uint8_t *, size_t) = device->receiveCallback;
        if (NULL != receiveCallback) {
          size_t messageSize = this->snap.readBytes(this->incommingMessageBuffer, 16);
          receiveCallback(this->incommingMessageBuffer, messageSize);
        }
      } else {
        Serial.print("receive message from unknown source ");
        Serial.println(this->snap.getSource());
      }

      // response receive from lastQuery ?
      if (this->snap.getSource() == this->currentQueryDevice->address) {
        // yes it is, clear lastQuery infos
        this->setCurrentQueryDevice(NULL);
      }

      this->snap.releaseReceive();
    }
  }

  void setCurrentQueryDevice(RemoteDevice * device) {
    if (NULL != device) {
      device->lastQueryTime = millis();
    }
    this->currentQueryDevice = device;
  }

  bool isWaitingForResponse() {
    // response is waiting ?
    if (NULL != this->currentQueryDevice) {
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

  bool queryPrepare(RemoteDevice * device) {
    // if (!this->queryIsFree()) {
    //   return false;
    // } else {
    this->setCurrentQueryDevice(device);
    this->snap.sendStart(device->address, SNAP_NO_ACK);
    return true;
    // }
  }

  void querySend() {
    this->snap.sendMessage();
  }

  void queryNextDevice() {
    if (this->queryIsFree()) {
      for (uint8_t devinceIndex = 0; devinceIndex < RemoteDeviceIndex::count; devinceIndex++) {
        RemoteDevice * device = this->getDevice(devinceIndex);
        if (millis() - device->lastQueryTime > device->delayBetweenQuery) {
          this->queryPrepare(device);
          this->snap.sendDataByte('?');
          this->querySend();
          break;
        }
      }
    }
  }

public:
  RemoteDeviceManager() { }

  void begin(RemoteDevice * devices) {
    this->devices = devices;

    this->snap.begin(SNAP_SPEED);
    this->snap.setPinRxDebug(LED_BUILTIN);
  }

  SNAP<16>& getSnap() { // TODO remove this method
    return this->snap;
  }

  void process() {
    this->processIncommingMessage();
    this->queryNextDevice();
  }
};
