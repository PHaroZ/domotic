#include "RemoteDevice.h"

/***************************************************************************
 * RemoteDevice
 **************************************************************************/
bool RemoteDevice::hasOutgoingPayload() {
  return false;
}

uint8_t RemoteDevice::readOutgoingPayload(size_t index) {
  return 0x00;
}

size_t RemoteDevice::getOutgoingPayloadSize() {
  return 0;
}

void RemoteDevice::clearOutgoingPayload() {
  // nothing to do
}

/***************************************************************************
 * RemoteDeviceActuator
 **************************************************************************/
void RemoteDeviceActuator::setOutgoingPayload(uint8_t * payload, size_t size) {
  this->outgoingPayloadSize = size;
  for (size_t i = 0; i < size; i++) {
    this->outgoingPayloadBuffer[i] = payload[i];
  }
}

bool RemoteDeviceActuator::hasOutgoingPayload() {
  return this->outgoingPayloadSize > 0;
}

uint8_t RemoteDeviceActuator::readOutgoingPayload(size_t index) {
  return this->outgoingPayloadBuffer[index];
}

size_t RemoteDeviceActuator::getOutgoingPayloadSize() {
  return this->outgoingPayloadSize;
}

void RemoteDeviceActuator::clearOutgoingPayload() {
  this->outgoingPayloadSize = 0;
}
