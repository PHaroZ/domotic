#include "Arduino.h"
#include "../const.h"

#include "SPI.h"
#include "Debouncer.h"

template <typename DataType>
class SwitchManager {
private:
  // represents last read states from SPI, not debounced
  DataType states;
  // debouncer  instance
  _Debouncer<sizeof(DataType) *8, DataType> debouncer;
  // callback which should be called when states changer
  void (* changeCallback)(DataType);

  void loadStatesFromSpi();

public:
  SwitchManager(void(*changeCallback)(DataType)) : changeCallback(changeCallback) { }

  void begin(DataType initialStates);

  /**
   * read states from SPI, debounce it and call <code>changeCallback</code> if some data have changed
   */
  void process();
};
