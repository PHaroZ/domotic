#include "SwitchManager.h"

// see https : www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// and https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl-export-keyword
template class SwitchManager<uint16_t>;
template class SwitchManager<uint32_t>;
template class SwitchManager<uint64_t>;

template <typename DataType> void SwitchManager<DataType>::loadStatesFromSpi() {
  // see https://www.gammon.com.au/forum/?id=11979 for more details
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI_SS_SWITCH, LOW);
  digitalWrite(SPI_SS_SWITCH, HIGH);
  SPI.transfer(&this->states, NO_SHIFT_IN_PIC);
  SPI.endTransaction();
}

template <typename DataType>   void SwitchManager<DataType>::begin(DataType initialStates) {
  this->states = initialStates;
  pinMode(SPI_SS_SWITCH, OUTPUT);
  digitalWrite(SPI_SS_SWITCH, HIGH);
  this->debouncer.begin(initialStates);
}

template <typename DataType>   void SwitchManager<DataType>::process() {
  this->loadStatesFromSpi();
  if (this->debouncer.debounce(this->states)) {
    this->changeCallback(this->debouncer.read());
  }
}
