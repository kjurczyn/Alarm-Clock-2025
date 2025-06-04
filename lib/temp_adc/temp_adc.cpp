#include "temp_adc.hpp"

void AdcThermo::init() {
  ADMUX = (0x1 << REFS0);  // ADC0, Vcc = Vref
  ADCSRA |= (0x1 << ADEN);
  // Enable
}

uint8_t AdcThermo::getTemp() {
  ADCSRA |= 0x1 << ADSC;
  while ((ADCSRA & (0x1 << ADSC)) == 1)
    ;

  uint8_t adcl = ADCL;
  uint8_t adch = ADCH;
  uint16_t adcval = ((adch << 8) | adcl);  // to 10-bit value
  return (uint8_t)(adcval);
}

void AdcThermo::getTempChars(char* temp_chars) {
  uint8_t cur_temp = getTemp();  // mean
  prev_temp_ = cur_temp;
  temp_chars[1] = '0' + (cur_temp / 10);
  temp_chars[2] = '0' + (cur_temp % 10);
}