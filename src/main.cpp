
#include "../lib/tpic_4x7/tpic_4x7.hpp"
#include "main.hpp"

Display4x7* display;

ISR(TIMER1_OVF_vect) {
  // Change to next digit
  display->update();
  TCNT1 = UINT16_MAX - (F_CPU / 1024 / 1000);  // Set timer for 1ms
}

int main() {
  // Timer0 Setup for display refresh
  TCNT1 = UINT16_MAX - (F_CPU / 1024 / 1000);  // Reset Timer0 counter
  TCCR1B = (0x1 << CS10) | (0x1 << CS12);      // Prescaler 1024
  TCCR1A = 0x0;                                // Normal mode - overflow timer
  TIMSK1 = (0x1 << TOIE1);
  sei();  // Enable global interrupts

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
