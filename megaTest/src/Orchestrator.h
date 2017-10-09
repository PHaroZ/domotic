#include "Arduino.h"
#include "const.h"
#include "core/MyMessage.h"

#include "sub/RemoteDeviceManager.h"
#include "sub/SwitchManager.h"
#include "sub/CoilManager.h"

#define noRemoteDevice 2
#define noShutter      3
#define noBinary       2
#define noSwitch       16
using SwitchStatesType = uint32_t;

namespace {
struct Sensor {
  const uint8_t id;
  const uint8_t type;
};
}

class Orchestrator {
private:
  static RemoteDeviceManager remoteDeviceManager;
  static RemoteDevice remoteDeviceRfReceiver;
  static RemoteDeviceActuator remoteDeviceDimmer1;
  static RemoteDevice remoteDevices[noRemoteDevice];
  static Shutter shutters[noShutter];
  static SwitchManager<SwitchStatesType> switchManager;
  static CoilManager<uint32_t> coilManager;
  static uint8_t dimmer1States[2];

  static void presentSensor(Sensor * pres, const char * desc = NULL);
  static void presentSensors(uint8_t type, uint8_t no, uint8_t sensorStartIndex, const char * descTpl);
  static void onRfReceive(uint8_t * data, size_t size);
  static void onSwitchChange(SwitchStatesType states);
public:
  Orchestrator() { }

  static void begin();
  static void presentation();
  static void process();
  static void onMessageReceive(const MyMessage &message);
  static void actionDimmer1Set(uint8_t id, uint8_t powerLvl);
  static void actionDimmer1Swap(uint8_t id);
  static void actionBinarySwapState(uint8_t id);
  static void actionShutterSetClosingPercent(uint8_t id, uint8_t percent);
};
