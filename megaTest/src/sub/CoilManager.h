#include "Arduino.h"
#include "../const.h"

#include "CoilManagerUtils.h"

namespace {
ShutterPowerGroup shutterPowerGroupVelux = ShutterPowerGroup(2000, 1);
ShutterPowerGroup shutterPowerGroupAC    = ShutterPowerGroup(2000, 5);
}

template <typename DataType>
class CoilManager {
private:
  DataType state                = 1;
  DataType nextState            = 0;
  const uint8_t noShutter       = 3;
  ShutterState shutterStates[3] = {
    ShutterState(shutterPowerGroupVelux, 10000),
    ShutterState(shutterPowerGroupVelux, 30000),
    ShutterState(shutterPowerGroupAC,    10000),
  };
  const size_t dataTypeSize = sizeof(DataType) * 8;

  inline boolean getNextState(uint8_t id) { return bitRead(this->nextState, id); }

  inline uint8_t getShutterCoilIndexOppening(uint8_t id) { return id * 2; }

  inline uint8_t getShutterCoilIndexClosing(uint8_t id) { return getShutterCoilIndexOppening(id) + 1; }

  inline uint8_t getBinaryCoilIndex(uint8_t id) { return this->noShutter * 2 + id; };

  bool writeCoils();
  void setCoilState(uint8_t id, bool state);
  bool getCoilState(uint8_t id);
  void shutterSetState(uint8_t id, uint8_t closingPercent);
  void shutterSetStopped(uint8_t id);
  void shutterCheckAll();

public:
  CoilManager()  {  }

  void begin();

  /**
   * commit/apply state changes previously requested to coils.
   * verify if some shutters should be stop or start (according to previous commited orders)
   */
  bool process();

  /**
   * return the current closing percent of a shutter, even it's currently moving
   */
  inline uint8_t shutterGetClosingPercent(uint8_t id) {
    return this->shutterStates[id].closingPercent;
  }

  /**
   * set the closing percent for a shutter
   */
  inline void shutterSetClosingPercent(uint8_t id, uint8_t closingPercent) {
    this->shutterSetState(id, closingPercent);
  }

  /**
   * stop the move of a shutter
   */
  inline void shutterStop(uint8_t id) {
    this->shutterSetClosingPercent(id, this->shutterGetClosingPercent(id));
  }

  /**
   * launch closing of ALL shutters
   */
  void shutterCloseAll();

  /**
   * swap state : if shutter is currenlty moving, stop it ;
   * else if its last move is for closing, open it ; else close it.
   */
  void shutterSwapState(uint8_t id);

  /**
   * swap state beetween ON or OFF
   */
  bool binarySwapState(uint8_t id);
};
