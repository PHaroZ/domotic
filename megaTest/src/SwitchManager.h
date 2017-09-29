#include "Arduino.h"
#include "const.h"

#include "SPI.h"
#include "Debouncer.h"

template <typename DataType>
class SwitchManager {
private:
  // represents last read states from SPI, not debounced
  DataType states;
  _Debouncer<sizeof(DataType), DataType> debouncer;
  void (* changeCallback)(DataType);

  void loadStatesFromSpi() {
    // see https://www.gammon.com.au/forum/?id=11979 for more details
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SPI_SS_SWITCH, LOW);
    digitalWrite(SPI_SS_SWITCH, HIGH);
    SPI.transfer(&this->states, sizeof(DataType));
    SPI.endTransaction();
  }

public:
  SwitchManager(void(*changeCallback)(DataType)) : changeCallback(changeCallback) { }

  void begin(DataType initialStates) {
    this->states = initialStates;
    pinMode(SPI_SS_SWITCH, OUTPUT);
    digitalWrite(SPI_SS_SWITCH, HIGH);
    this->debouncer.begin(initialStates);
  }

  /**
   * read states from SPI, debounce it and call <code>changeCallback</code> if some data have changed
   */
  void process() {
    this->loadStatesFromSpi();
    if (this->debouncer.debounce(this->states)) {
      this->changeCallback(this->debouncer.read());
    }
  }
};
