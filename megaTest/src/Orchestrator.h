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
class Sensor {
public:
  // sensor id on MySensors
  const uint8_t id;
  // sensor type on MySensors
  const uint8_t type;
  explicit Sensor(uint8_t id, uint8_t type) : id(id), type(type) { }
};
class SensorIndexed : public Sensor {
public:
  // index of the corresponding actuator
  const uint8_t actuatorIndex;
  using Sensor::Sensor;
  explicit SensorIndexed(uint8_t id, uint8_t type, uint8_t actuatorIndex) : Sensor(id,
      type), actuatorIndex(actuatorIndex) { }
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
  static MyMessage myMessage;

  static void presentSensor(Sensor * pres, const char * desc = NULL);
  static void presentSensors(uint8_t type, uint8_t no, uint8_t sensorStartIndex, const char * descTpl);
  static void onRfReceive(uint8_t * data, size_t size);
  static void onSwitchChange(SwitchStatesType states);
  static void onShutterMoveEnd(uint8_t id, int8_t percent);
  static void actionDimmer1Set(uint8_t id, uint8_t powerLvl);
  static void actionDimmer1Swap(uint8_t id);
  static void actionBinarySwapState(uint8_t id);
  static void actionShutterSetClosingPercent(uint8_t id, int8_t percent);
  static void sendMyMessage(MyMessage &message = Orchestrator::myMessage);
  static void sendMyMessageForBinary(uint8_t id);
  static void sendMyMessageForShutter(uint8_t id);
  static void sendMyMessageForDimmer1(uint8_t id);
public:
  Orchestrator() { }

  static void presentation();
  static void begin();
  static void process();
  static bool onMyMessageReceive(const MyMessage &message);
};
