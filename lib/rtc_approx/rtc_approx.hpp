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

  /* @brief update the RTC time by one millisecond.
   * This function should be called every millisecond, typically in a timer
   * interrupt.
   */
  void update();

  uint8_t getSeconds() const;
  uint8_t getMinutes() const;
  uint8_t getHours() const;
  uint32_t getMillis() const;

  char getMinutesCharL() const;
  char getMinutesCharR() const;
  char getHoursCharL() const;
  char getHoursCharR() const;

  char* getChars() {
    static char chars[4];
    chars[0] = getHoursCharL();
    chars[1] = getHoursCharR();
    chars[2] = getMinutesCharL();
    chars[3] = getMinutesCharR();
    return chars;
  }

  void setMinutesR(uint8_t minutes_r);
  void setMinutesL(uint8_t minutes_l);
  void setHoursR(uint8_t hours_r);
  void setHoursL(uint8_t hours_l);

 private:
  uint8_t seconds_;
  uint8_t minutes_;
  uint8_t hours_;
  uint32_t millis_;  // System uptime
};

#endif