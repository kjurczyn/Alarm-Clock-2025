#ifndef RTC_APPROX
#define RTC_APPROX

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

class RtcApprox {
 public:
  RtcApprox() : seconds_{}, minutes_{}, hours_{} {};
  RtcApprox(uint8_t seconds, uint8_t minutes, uint8_t hours)
      : seconds_(seconds), minutes_(minutes), hours_(hours){};

  /* @brief update the RTC time by one second.
   * This function should be called every second, typically in a timer
   * interrupt.
   */
  void update();

  uint8_t getSeconds() const;
  uint8_t getMinutes() const;
  uint8_t getHours() const;

  char getMinutesCharL() const;
  char getMinutesCharR() const;
  char getHoursCharL() const;
  char getHoursCharR() const;

 private:
  uint8_t seconds_;
  uint8_t minutes_;
  uint8_t hours_;
};

#endif