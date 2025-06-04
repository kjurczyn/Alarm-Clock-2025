
#include "../lib/rtc_approx/rtc_approx.hpp"
#include "../lib/shr_4x7/shr_4x7.hpp"
#include "../lib/temp_adc/temp_adc.hpp"
#include "main.hpp"

Display4x7* display;
RtcApprox* rtc_approx;
AdcThermo* adc_thermo;

uint8_t clock_state = 3;
uint8_t set_value = 0;
uint8_t setting_digit = 0;

uint8_t left_button_prev_state = 0x0;
uint32_t prev_left_button_press_time = 0;
uint8_t right_button_prev_state = 0x0;
uint32_t prev_right_button_press_time = 0;

constexpr char empty_disp[4] = {' ', ' ', ' ', ' '};
constexpr bool empty_dots[4] = {0};

bool last_shown = true;

// TODO: Refactor to use bits

bool time_dots[4] = {false, true, false, false};  // Dots for time display

ISR(TIMER0_OVF_vect) {
  // Change to next digit
  display->update();
  TCNT0 = UINT8_MAX - (F_CPU / 1024 / 1000);  // Set timer for 1ms
  rtc_approx->update();                       // Update RTC every millisecond
}

ISR(TIMER1_OVF_vect) {
  // Update clock display every second
  const char* cur_time;
  time_dots[1] = !time_dots[1];  // Toggle dot
  if ((clock_state == 3 || clock_state == 4 || clock_state == 5 ||
       clock_state == 6) &&
      !time_dots[1]) {
    cur_time = empty_disp;
    display->display(cur_time, empty_dots);
  } else if (clock_state == 2) {
    char temp[4] = {' ', ' ', ' ', ' '};
    adc_thermo->getTempChars(temp);
    display->display(temp, empty_dots);
  } else {
    cur_time = rtc_approx->getChars();
    display->display(cur_time, time_dots);
  }

  TCNT1 = UINT16_MAX - (F_CPU / 1024);  // Set timer for 1 sec
}

ISR(PCINT1_vect) {
  PIND |= (0x1 << PD4);
  if (BUTTON_RIGHT_GROUP & (0x1 << BUTTON_RIGHT_PIN)) {
    switch (clock_state) {
      case 1:
        clock_state = 2;
        break;
      case 2:
        clock_state = 1;
        break;
      default:
        break;
    }
  }

  if (BUTTON_LEFT_GROUP & (0x1 << BUTTON_LEFT_PIN)) {
    switch (clock_state) {
      case 1:
        clock_state = 3;
        break;
      case 3:
        clock_state = 1;
        break;
      default:
        break;
    }
  }
}

void delay_ms(uint32_t ms_delay) {
  uint32_t start = rtc_approx->getMillis();
  while (rtc_approx->getMillis() - start < ms_delay)
    ;
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

  // Pin change interrupt setup for buttons
  PCMSK1 = (0x1 << PCINT12) |  // Enable pin change interrupts on PB4 and PB5,
           (0x1 << PCINT13);   // disable on other pins
  PCICR |= (0x1 << PCIE1);     // Enable pin change interrupt group 1
  DDRC &= ~((0x1 << BUTTON_LEFT_PIN) |
            (0x1 << BUTTON_RIGHT_PIN));  // Set input on PC4 and PC5

  sei();  // Enable global interrupts

  // LED pin setup
  DDRD |= (0x1 << PD4);
  PORTD |= (0x1 << PD4);

  rtc_approx = new RtcApprox();

  adc_thermo = new AdcThermo();

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

  for (;;) {
  };
}
