#include "RemoteDeviceManager.h"

/***************************************************************************
 * RemoteDeviceManager
 **************************************************************************/
uint8_t RemoteDeviceManager::getDeviceIndexFromAddress(uint8_t address) {
  for (uint8_t devinceIndex = 0; devinceIndex < this->noDevice; devinceIndex++) {
    if (this->getDevice(devinceIndex)->address == address) {
      return devinceIndex;
    }
  }
  return this->noDevice;
}

void RemoteDeviceManager::processOutgoingMessage() {
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

void RemoteDeviceManager::processIncommingMessage() {
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

void RemoteDeviceManager::setCurrentQueryDevice(RemoteDevice * device, bool waitingForResponse) {
  if (NULL != device) {
    device->lastQueryTime    = millis();
    this->waitingForResponse = waitingForResponse;
  } else {
    this->waitingForResponse = false;
  }
  this->currentQueryDevice = device;
}

bool RemoteDeviceManager::isWaitingForResponse() {
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

bool RemoteDeviceManager::queryIsFree() {
  return !this->isWaitingForResponse() && !this->snap.isWaitingForAck();
}

bool RemoteDeviceManager::queryPrepare(RemoteDevice * device, bool waitingForResponse) {
  // if (!this->queryIsFree()) {
  //   return false;
  // } else {
  this->setCurrentQueryDevice(device, waitingForResponse);
  this->snap.sendStart(device->address, waitingForResponse ? SNAP_NO_ACK : SNAP_ACK_WAIT_TIME);
  return true;
  // }
}

void RemoteDeviceManager::querySend() {
  this->snap.sendMessage();
}

void RemoteDeviceManager::queryNextDevice() {
  if (this->queryIsFree()) {
    for (uint8_t devinceIndex = 0; devinceIndex < this->noDevice; devinceIndex++) {
      RemoteDevice * device = this->getDevice(devinceIndex);
      if ((device->delayBetweenQuery > 0) && (millis() - device->lastQueryTime > device->delayBetweenQuery)) {
        // Serial.print(millis());
        // Serial.print("query device ");
        // Serial.println(device->address);
        this->queryPrepare(device, true);
        this->snap.sendDataByte('?');
        this->querySend();
        break;
      }
    }
  }
}

void RemoteDeviceManager::begin(RemoteDevice * devices, size_t noDevice) {
  this->noDevice = noDevice;
  this->devices  = devices;

  this->snap.begin(SNAP_SPEED);
  this->snap.setPinRxDebug(LED_BUILTIN);
}

void RemoteDeviceManager::process() {
  this->processIncommingMessage();
  this->processOutgoingMessage();
  this->queryNextDevice();
}
