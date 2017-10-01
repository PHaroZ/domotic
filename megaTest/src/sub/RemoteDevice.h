#include "Arduino.h"

/**
 * a remote defice which we can query
 */
class RemoteDevice {
public:
  // device unique address
  const uint8_t address;
  // when a query is send to this device, it should response max in <code>delayForResponse</code> ms
  const uint32_t delayForResponse;
  // minimum delay between 2 consecutove query to ths device
  const uint32_t delayBetweenQuery;
  // callback to call when response of query is received
  void (* receiveCallback)(uint8_t *, size_t);
  // last time this device have been queried
  uint32_t lastQueryTime;

  explicit RemoteDevice(uint8_t address, uint32_t delayForResponse,
    uint32_t delayBetweenQuery,
    void(*receiveCallback)(uint8_t *, size_t)) : address(address), delayForResponse(delayForResponse),
    delayBetweenQuery(delayBetweenQuery), receiveCallback(receiveCallback) { }

  bool hasOutgoingPayload();
  uint8_t readOutgoingPayload(size_t index);
  size_t getOutgoingPayloadSize();
  void clearOutgoingPayload();
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

  void setOutgoingPayload(uint8_t * payload, size_t size);
  bool hasOutgoingPayload();
  uint8_t readOutgoingPayload(size_t index);
  size_t getOutgoingPayloadSize();
  void clearOutgoingPayload();
};
