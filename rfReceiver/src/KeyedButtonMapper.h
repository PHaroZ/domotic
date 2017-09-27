#ifndef KeyedButtonMapper_h
#define KeyedButtonMapper_h

#include "Arduino.h"

template <typename StateType, typename ButtonKeyType>
class KeyedButtonMapper  {
private:
  // button values
  ButtonKeyType * buttonKeys;
  // number of button
  uint8_t noButton;
  // save which buttons have HIGH state between 2 read
  StateType states;
  // when a button have been pressed for the last time
  unsigned long lastPressTime;
  // minimum delay between 2 press of a buttons
  const unsigned long delayBetween2Press;

public:
  KeyedButtonMapper(unsigned long delayBetween2Press) : delayBetween2Press(delayBetween2Press) { }

  void begin(ButtonKeyType * buttonKeys, uint8_t noButton) {
    this->buttonKeys = buttonKeys;
    this->noButton   = noButton;
    this->states     = 0;
  }

  /**
   * read saved states
   */
  inline StateType readStates() { return this->states; }

  /**
   * clear saved states
   */
  inline void resetStates() { this->states = 0; }

  /**
   * save HIGH state for a button if it :
   *  - is a known button
   *  - has not been pressed in the last <code>delayBetween2Push</code> ms
   *
   * @return <code>true</code> if state has been saved
   */
  bool setHighStateFor(ButtonKeyType buttonKey) {
    for (uint8_t buttonIndex = 0; buttonIndex < noButton; buttonIndex++) {
      if (this->buttonKeys[buttonIndex] == buttonKey) {
        if ((millis() - this->lastPressTime) > this->delayBetween2Press) {
          this->lastPressTime = millis();
          bitWrite(this->states, buttonIndex, 1);
          return true;
        } else {
          break;
        }
      }
    }
    return false;
  }
};

#endif // ifndef KeyedButtonMapper_h
