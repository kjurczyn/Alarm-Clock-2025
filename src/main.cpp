
#include "../lib/rtc_approx/rtc_approx.hpp"
#include "../lib/tpic_4x7/tpic_4x7.hpp"
#include "main.hpp"

Display4x7* display;
RtcApprox* rtc_approx;

constexpr bool time_dots[4] = {false, true, false,
                               false};  // Dots for time display

ISR(TIMER0_OVF_vect) {
  // Change to next digit
  display->update();
  TCNT0 = UINT8_MAX - (F_CPU / 1024 / 1000);  // Set timer for 1ms
}

ISR(TIMER1_OVF_vect) {
  // Update RTC every second
  rtc_approx->update();
  char cur_time[4] = {rtc_approx->getHoursCharL(), rtc_approx->getHoursCharR(),
                      rtc_approx->getMinutesCharL(),
                      rtc_approx->getMinutesCharR()};
  display->display(cur_time, time_dots);
  TCNT1 = UINT16_MAX - (F_CPU / 1024);  // Set timer for 1 sec
}

int main() {
  // Timer0 Setup for display refresh
  TCCR0B = (0x1 << CS10) | (0x1 << CS12);     // Prescaler 1024
  TCCR0A = 0x0;                               // Normal mode - overflow timer
  TCNT0 = UINT8_MAX - (F_CPU / 1024 / 1000);  // Set timer for 1ms
  TIMSK0 = (0x1 << TOIE0);                    // Enable interrupt

  // Timer1 Setup for approximate RTC
  TCCR1B = (0x1 << CS10) | (0x1 << CS12);  // Prescaler 1024
  TCCR1A = 0x0;                            // Normal mode - overflow timer
  TCNT1 = UINT16_MAX - (F_CPU / 1024);     // Set timer for 1 sec
  TIMSK1 = (0x1 << TOIE1);                 // Enable interrupt

  sei();  // Enable global interrupts

  rtc_approx = new RtcApprox();

  struct PortsPins_Display4x7 ports_pins = {
      .dig_ports = {&PORTB, &PORTB, &PORTD, &PORTD},
      .dig_ddr_ports = {&DDRB, &DDRB, &DDRD, &DDRD},
      .dig_pins = {PB1, PB0, PD7, PD5},
      .rck_port = &PORTB,
      .rck_ddr_port = &DDRB,
      .rck_pin = PB2,
      .seg_pos = {4, 6, 1, 3, 2, 5, 7, 0}};

  display = new Display4x7(&ports_pins);
  display->init();
  bool dots[4] = {true, false, true, false};
  char chars[4] = {'1', '2', '3', '4'};
  display->display(chars, dots);

  for (;;)
    ;
}
