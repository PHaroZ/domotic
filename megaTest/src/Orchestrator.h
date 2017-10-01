#include "Arduino.h"
#include "const.h"

#include "sub/RemoteDeviceManager.h"
#include "sub/SwitchManager.h"
#include "sub/CoilManager.h"

#define noRemoteDevices 2
using SwitchStatesType = uint32_t;

class Orchestrator {
private:
  static RemoteDeviceManager remoteDeviceManager;
  static RemoteDevice remoteDeviceRfReceiver;
  static RemoteDeviceActuator remoteDeviceDimmer1;
  static RemoteDevice remoteDevices[noRemoteDevices];
  static SwitchManager<SwitchStatesType> switchManager;
  static CoilManager<uint32_t> coilManager;

  static void onRfReceive(uint8_t * data, size_t size);
  static void onSwitchChange(SwitchStatesType states);
public:
  Orchestrator() { }

  static void begin();
  static void process();
  static void actionDimmer1Set(uint8_t id, uint8_t powerLvl);
  static void actionDimmer1Swap(uint8_t id);
  static void actionBinarySwapState(uint8_t id);
  static void actionShutterSetClosingPercent(uint8_t id, uint8_t percent);
};
