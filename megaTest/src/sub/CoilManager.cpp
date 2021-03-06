#include "CoilManager.h"

// see https : www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// and https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl-export-keyword
template class CoilManager<uint16_t>;
template class CoilManager<uint32_t>;
template class CoilManager<uint64_t>;

template <typename DataType> bool CoilManager<DataType>::writeCoils() {
  if (this->state == this->nextState) {
    return false;
  } else {
    this->state = this->nextState;
    digitalWrite(COIL_ST_CP, LOW);
    for (size_t index = 0; index < dataTypeSize; index++) {
      digitalWrite(COIL_SH_CP, LOW);
      digitalWrite(COIL_DS, bitRead(this->state, dataTypeSize - index - 1) ? COIL_ON : COIL_OFF);
      digitalWrite(COIL_SH_CP, HIGH);
    }
    digitalWrite(COIL_ST_CP, HIGH);
    return true;
  }
}

template <typename DataType> void CoilManager<DataType>::setCoilState(uint8_t id, bool state) {
  bitWrite(this->nextState, id, state);
}

template <typename DataType> bool CoilManager<DataType>::getCoilState(uint8_t id) {
  return bitRead(this->state, id);
}

template <typename DataType> void CoilManager<DataType>::shutterSetState(uint8_t id, int8_t closingPercent) {
  Shutter& shutterState = shutterStates[id];

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

template <typename DataType> void CoilManager<DataType>::shutterSetStopped(uint8_t id) {
  Shutter& shutterState = shutterStates[id];

  shutterState.powerGroup.noSimultaneousMoving--;
  shutterState.closingPercentLast = shutterState.closingPercent;
  shutterState.lastMoveForClosing = shutterState.closingPercentDiffRequested > 0;
  shutterState.closingPercentDiffRequested = 0;
  shutterState.startMovingAt = 0;
  this->setCoilState(this->getShutterCoilIndexOppening(id), 0);
  this->setCoilState(this->getShutterCoilIndexClosing(id), 0);
  if (NULL != this->shutterMoveEndCallback) {
    this->shutterMoveEndCallback(id, shutterState.closingPercent);
  }
}

template <typename DataType> void CoilManager<DataType>::shutterCheckAll() {
  uint32_t now = millis();

  for (uint8_t id; id < this->noShutter; id++) {
    Shutter& shutterState = this->shutterStates[id];
    if (shutterState.startMovingAt) { // it is moving
      // update its state & check if it must be stoppped
      int8_t progressPercent = (now - shutterState.startMovingAt) / shutterState.fullMovingTime;
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
      // update current state & avoid closingPercent overflow uppper to 100 or lower to 0
      shutterState.closingPercent = min(100, max(0, shutterState.closingPercentLast + progressPercent));
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

template <typename DataType> void CoilManager<DataType>::begin(Shutter * shutters, uint8_t noShutter,
  uint8_t noBinary) {
  this->shutterStates = shutters;
  this->noShutter     = noShutter;
  this->noBinary      = noBinary;

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

template <typename DataType> bool CoilManager<DataType>::process() {
  this->shutterCheckAll();
  return this->writeCoils();
}

template <typename DataType> void CoilManager<DataType>::shutterCloseAll() {
  for (uint8_t id = 0; id < this->noShutter; id++) {
    this->shutterSetClosingPercent(id, 100);
  }
}

template <typename DataType> void CoilManager<DataType>::shutterOpenAll(bool force) {
  for (uint8_t id = 0; id < this->noShutter; id++) {
    this->shutterSetClosingPercent(id, force ? -105 : 0);
  }
}

template <typename DataType> void CoilManager<DataType>::shutterSwapState(uint8_t id) {
  if (id < this->noShutter) {
    Shutter& shutterState = this->shutterStates[id];

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

template <typename DataType> bool CoilManager<DataType>::binarySetState(uint8_t id, bool state) {
  uint8_t coilIndex = this->getBinaryCoilIndex(id);

  this->setCoilState(coilIndex, state);
  return state;
}

template <typename DataType> bool CoilManager<DataType>::binaryGetState(uint8_t id) {
  uint8_t coilIndex = this->getBinaryCoilIndex(id);

  return this->getCoilState(coilIndex);
}

template <typename DataType> bool CoilManager<DataType>::binarySwapState(uint8_t id) {
  uint8_t coilIndex = this->getBinaryCoilIndex(id);
  bool state        = !this->getCoilState(coilIndex);

  this->setCoilState(coilIndex, state);
  return state;
}
