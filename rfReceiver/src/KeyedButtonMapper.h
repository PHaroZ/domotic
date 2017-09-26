#ifndef KeyedButtonMapper_h
#define KeyedButtonMapper_h

#include "Arduino.h"

template <typename StateType, typename ButtonKeyType>
class KeyedButtonMapper  {
private:
  ButtonKeyType * buttonKeys;
  uint8_t noButton;
  StateType states;

public:
  KeyedButtonMapper() { }


  void begin(ButtonKeyType * buttonKeys, uint8_t noButton) {
    this->buttonKeys = buttonKeys;
    this->noButton   = noButton;
    this->states     = 0;
  }

  inline StateType readStates() { return this->states; }

  inline void resetStates() { this->states = 0; }

  bool setHighStateFor(ButtonKeyType buttonKey) {
    for (uint8_t buttonIndex = 0; buttonIndex < noButton; buttonIndex++) {
      if (this->buttonKeys[buttonIndex] == buttonKey) {
        bitWrite(this->states, buttonIndex, 1);
        return true;
      }
    }
    return false;
  }
};

#endif // ifndef KeyedButtonMapper_h
