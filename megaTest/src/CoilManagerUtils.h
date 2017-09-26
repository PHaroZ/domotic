#include "Arduino.h"
#include "const.h"

class ShutterPowerGroup {
public:
  // minimum delay between two consecutive start of shutter in this group
  const uint32_t delayBetweenConsecutiveStart;
  // maximum number of shutters that can be moving at the same time
  const uint8_t maxSimultaneousMoving;
  // current number of shutters that are moving
  uint32_t noSimultaneousMoving = 0;
  // last starting time of a shutter
  uint32_t lastStartingTime = 0;

  ShutterPowerGroup(uint32_t delayBetweenConsecutiveStart,
    uint8_t                  maxSimultaneousMoving) : delayBetweenConsecutiveStart(delayBetweenConsecutiveStart),
    maxSimultaneousMoving(maxSimultaneousMoving) { }

  bool shutterCouldStart() {
    return 0 == this->noSimultaneousMoving ||
           ((this->noSimultaneousMoving < this->maxSimultaneousMoving) &&
      (millis() - this->lastStartingTime > this->delayBetweenConsecutiveStart));
  }
};

struct ShutterState {
  ShutterPowerGroup & powerGroup;
  // time required to fully open/close this shutter
  const uint32_t    fullMovingTime;
  // percent of closing now
  uint8_t           closingPercent = 0;
  // percent of closing at the last stable state
  uint8_t           closingPercentLast = 0;
  // requested DIFFERENCE percent of closing
  int8_t            closingPercentDiffRequested = 0;
  // if isMoving, when it starts (0 means not moving)
  uint32_t          startMovingAt = 0;
  ShutterState(ShutterPowerGroup& powerGroup,
    uint32_t                    fullMovingTime) : powerGroup(powerGroup), fullMovingTime(fullMovingTime),
    closingPercent(0),
    closingPercentDiffRequested(0),
    startMovingAt(0) { }
};
