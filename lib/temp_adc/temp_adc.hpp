#ifndef TEMP_ADC
#define TEMP_ADC

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

class AdcThermo {
 public:
  AdcThermo(){};
  void init();
  void start();
  void getTempChars(char* temp_chars);
  uint8_t getTemp();

 private:
  uint8_t prev_temp_;
};

#endif