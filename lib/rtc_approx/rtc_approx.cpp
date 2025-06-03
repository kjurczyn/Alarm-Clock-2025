#include "rtc_approx.hpp"

void RtcApprox::update() {
  millis_++;
  if (millis_ % 1000 == 0) {
    seconds_++;
    if (seconds_ >= 60) {
      seconds_ = 0;
      minutes_++;
      if (minutes_ >= 60) {
        minutes_ = 0;
        hours_++;
        if (hours_ >= 24) {
          hours_ = 0;
        }
      }
    }
  }
}

uint8_t RtcApprox::getSeconds() const { return seconds_; }

uint8_t RtcApprox::getMinutes() const { return minutes_; }

uint8_t RtcApprox::getHours() const { return hours_; }

uint32_t RtcApprox::getMillis() const { return millis_; }

char RtcApprox::getMinutesCharL() const { return '0' + (minutes_ / 10); }

char RtcApprox::getMinutesCharR() const { return '0' + (minutes_ % 10); }

char RtcApprox::getHoursCharL() const { return '0' + (hours_ / 10); }

char RtcApprox::getHoursCharR() const { return '0' + (hours_ % 10); }