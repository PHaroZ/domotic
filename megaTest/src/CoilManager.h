#include "Arduino.h"
#include "const.h"
#include "CoilManagerUtils.h"

namespace {
ShutterPowerGroup shutterPowerGroupVelux = ShutterPowerGroup(2000, 1);
ShutterPowerGroup shutterPowerGroupAC    = ShutterPowerGroup(2000, 5);

template <typename DataType, uint8_t dataTypeSize>
class _CoilManager {
private:
  DataType state                = 1;
  DataType nextState            = 0;
  const uint8_t noShutter       = 3;
  ShutterState shutterStates[3] = {
    ShutterState(shutterPowerGroupVelux, 10000),
    ShutterState(shutterPowerGroupVelux, 30000),
    ShutterState(shutterPowerGroupAC,    10000),
  };

  inline boolean getNextState(uint8_t id) { return bitRead(this->nextState, id); }

  inline uint8_t getShutterCoilIndexOppening(uint8_t id) { return id * 2; }

  inline uint8_t getShutterCoilIndexClosing(uint8_t id) { return getShutterCoilIndexOppening(id) + 1; }

  inline uint8_t getBinaryCoilIndex(uint8_t id) { return this->noShutter * 2 + id; };

  bool writeCoils() {
    if (this->state == this->nextState) {
      return false;
    } else {
      this->state = this->nextState;
      digitalWrite(COIL_ST_CP, LOW);
      for (int index = 0; index < dataTypeSize; index++) {
        digitalWrite(COIL_SH_CP, LOW);
        digitalWrite(COIL_DS, bitRead(this->state, dataTypeSize - index - 1) ? COIL_ON : COIL_OFF);
        digitalWrite(COIL_SH_CP, HIGH);
      }
      digitalWrite(COIL_ST_CP, HIGH);
      return true;
    }
  }

  void setCoilState(uint8_t id, bool state) {
    bitWrite(this->nextState, id, state);
  }

  bool getCoilState(uint8_t id) {
    return bitRead(this->state, id);
  }

  void shutterSetState(uint8_t id, uint8_t closingPercent) {
    ShutterState& shutterState = shutterStates[id];

    if (shutterState.startMovingAt) { // it is moving, stop it first
      this->shutterSetStopped(id);
    }

    int8_t closingPercentDiff = closingPercent - shutterState.closingPercent;
    if (closingPercentDiff) {
      { // for a fully closing or opening, request 5% more
        if (0 == closingPercent) {
          closingPercentDiff -= 5;
        } else if (100 == closingPercent) {
          closingPercentDiff += 5;
        }
      }
      shutterState.closingPercentDiffRequested = closingPercentDiff;
    }
  } // shutterSetState

  void shutterSetStopped(uint8_t id) {
    ShutterState& shutterState = shutterStates[id];

    shutterState.powerGroup.noSimultaneousMoving--;
    shutterState.closingPercentLast = shutterState.closingPercent;
    shutterState.lastMoveForClosing = shutterState.closingPercentDiffRequested > 0;
    shutterState.closingPercentDiffRequested = 0;
    shutterState.startMovingAt = 0;
    this->setCoilState(this->getShutterCoilIndexOppening(id), 0);
    this->setCoilState(this->getShutterCoilIndexClosing(id), 0);
  }

  void shutterCheckAll() {
    uint32_t now = millis();

    for (uint8_t id; id < this->noShutter; id++) {
      ShutterState& shutterState = this->shutterStates[id];
      if (shutterState.startMovingAt) { // it is moving
        // update its state & check if it must be stoppped
        int8_t progressPercent = (now - shutterState.startMovingAt) / 0.01 / shutterState.fullMovingTime;
        bool shouldBeStopped   = false;
        if (shutterState.closingPercentDiffRequested < 0) { // shutter is opening
          progressPercent *= -1;                            // progress is negative
          if (progressPercent <= shutterState.closingPercentDiffRequested) {
            shouldBeStopped = true;
          }
        } else { // shutter is closing
          if (progressPercent >= shutterState.closingPercentDiffRequested) {
            shouldBeStopped = true;
          }
        }
        // update current state
        shutterState.closingPercent = shutterState.closingPercentLast + progressPercent;
        if (shouldBeStopped) {
          // must be done AFTER updating shutterState.closingPercent
          this->shutterSetStopped(id);
        }
      } else {
        // verify if it should start moving
        if (0 != shutterState.closingPercentDiffRequested) {
          // it should start, is it allowed to start ?
          if (shutterState.powerGroup.shutterCouldStart()) { // yes it can start, do it !
            shutterState.powerGroup.noSimultaneousMoving++;
            shutterState.powerGroup.lastStartingTime = now;
            shutterState.startMovingAt = now;
            if (0 == shutterState.startMovingAt) {
              // 0 means not moving, so ensure that millis()!=0
              shutterState.startMovingAt = 1;
            }
            if (shutterState.closingPercentDiffRequested > 0) {
              this->setCoilState(this->getShutterCoilIndexOppening(id), 0);
              this->setCoilState(this->getShutterCoilIndexClosing(id), 1);
            } else {
              this->setCoilState(this->getShutterCoilIndexOppening(id), 1);
              this->setCoilState(this->getShutterCoilIndexClosing(id), 0);
            }
          }
        }
      }
    }
  } // shutterCheckAll

public:
  _CoilManager()  {  }

  void begin() {
    pinMode(COIL_DS, OUTPUT);
    pinMode(COIL_ST_CP, OUTPUT);
    pinMode(COIL_SH_CP, OUTPUT);

    // avoid coild flickering at power up (in conjunction with a pull-up resistor)
    // for more details see http://forums.parallax.com/discussion/139862/74hc595-on-start-up
    digitalWrite(COIL_OE, HIGH);
    pinMode(COIL_OE, OUTPUT);

    this->writeCoils();

    digitalWrite(COIL_OE, LOW);
  }

  bool process() {
    this->shutterCheckAll();
    return this->writeCoils();
  }

  inline uint8_t shutterGetClosingPercent(uint8_t id) {
    return this->shutterStates[id].closingPercent;
  }

  inline void shutterSetClosingPercent(uint8_t id, uint8_t closingPercent) {
    this->shutterSetState(id, closingPercent);
  }

  inline void shutterStop(uint8_t id) {
    this->shutterSetClosingPercent(id, this->shutterGetClosingPercent(id));
  }

  void shutterCloseAll() {
    for (uint8_t id; id < this->noShutter; id++) {
      this->shutterSetClosingPercent(id, 100);
    }
  }

  void shutterSwith(uint8_t id) {
    if (id < this->noShutter) {
      ShutterState& shutterState = this->shutterStates[id];

      Serial.print("shutterSwith ");
      Serial.println(id);

      // is it moving ?
      if (shutterState.startMovingAt) {
        // yes, stop it
        this->shutterStop(id);
      } else {
        // not moving, start in opposite direction as last move
        this->shutterSetClosingPercent(id, shutterState.lastMoveForClosing ? 0 : 100);
      }
    }
  }

  bool binarySwitch(uint8_t id) {
    uint8_t coilIndex = this->getBinaryCoilIndex(id);
    bool state        = !this->getCoilState(coilIndex);

    this->setCoilState(coilIndex, state);
    return state;
  }
};


class CoilManager : public _CoilManager<uint32_t, 32> {
public:
  CoilManager() : _CoilManager() { }
};
}
