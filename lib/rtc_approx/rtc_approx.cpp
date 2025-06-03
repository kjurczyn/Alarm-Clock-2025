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

void RtcApprox::setMinutesR(uint8_t minutes_r) {
  minutes_ = minutes_ / 10 + minutes_r;
}

void RtcApprox::setMinutesL(uint8_t minutes_l) {
  minutes_ = minutes_l * 10 + minutes_ % 10;
}

void RtcApprox::setHoursR(uint8_t hours_r) { hours_ = hours_ / 10 + hours_r; }

void RtcApprox::setHoursL(uint8_t hours_l) {
  hours_ = hours_l * 10 + hours_ % 10;
}