#include "Arduino.h"
#include "../const.h"

#include "RemoteDevice.h"

#include "SNAP.h"
#include "SNAPChannelHardwareSerial.h"

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

  uint8_t getDeviceIndexFromAddress(uint8_t address);
  void processOutgoingMessage();
  void processIncommingMessage();

  void setCurrentQueryDevice(RemoteDevice * device, bool waitingForResponse = false);
  bool isWaitingForResponse();
  bool queryIsFree();
  bool queryPrepare(RemoteDevice * device, bool waitingForResponse = false);
  void querySend();
  void queryNextDevice();

public:
  RemoteDeviceManager() { }

  void begin(RemoteDevice * devices, size_t noDevice);

  /**
   * in order :
   * - check SNAP ACK reception
   * - read response from remote device. If some data are received from a device,
   *    corresponding <code>receiveCallback</code> is called
   * - send waiting outgoint message
   * - query data from new device if necessary
   */
  void process();
};
