#include "Arduino.h"

class ShutterPowerGroup {
public:
  // minimum delay between two consecutive start of shutter in this group
  const uint32_t delayBetweenConsecutiveStart;
  // maximum number of shutters that can be moving at the same time
  const uint8_t maxSimultaneousMoving;
  // current number of shutters that are actually moving
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

class Shutter {
public:
  ShutterPowerGroup & powerGroup;
  // time required to fully open/close this shutter (in tenth of second, not ms, for performance purpose)
  const uint32_t fullMovingTime;
  // percent of closing now
  int8_t closingPercent = 0;
  // percent of closing at the last stable state
  int8_t closingPercentLast = 0;
  // requested DIFFERENCE percent of closing (beetwee current value abd expected one)
  int8_t closingPercentDiffRequested = 0;
  // if is moving, when it starts (0 means not moving)
  uint32_t startMovingAt = 0;
  // 1 if last move is for closing, 0 otherwise
  bool lastMoveForClosing = 0;
  Shutter(ShutterPowerGroup& powerGroup,
    uint32_t               fullMovingTime) : powerGroup(powerGroup), fullMovingTime(fullMovingTime / 100),
    closingPercent(0),
    closingPercentDiffRequested(0),
    startMovingAt(0) { }
};
