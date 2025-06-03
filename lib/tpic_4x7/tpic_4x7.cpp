#include "tpic_4x7.hpp"

constexpr int DOT_POS = 7;
// A B C D E F G DOT
constexpr bool char_0[SEG_LIST_LEN] = {true, true, true, true,
                                       true, true, false};
constexpr bool char_1[SEG_LIST_LEN] = {false, false, false, false,
                                       true,  true,  false};
constexpr bool char_2[SEG_LIST_LEN] = {true, true,  false, true,
                                       true, false, true};
constexpr bool char_3[SEG_LIST_LEN] = {true,  true,  true, true,
                                       false, false, true};
constexpr bool char_4[SEG_LIST_LEN] = {false, true, true, false,
                                       false, true, true};
constexpr bool char_5[SEG_LIST_LEN] = {true,  false, true, true,
                                       false, true,  true};
constexpr bool char_6[SEG_LIST_LEN] = {true, false, true, true,
                                       true, true,  true};
constexpr bool char_7[SEG_LIST_LEN] = {true,  true,  true, false,
                                       false, false, false};
constexpr bool char_8[SEG_LIST_LEN] = {true, true, true, true,
                                       true, true, true};
constexpr bool char_9[SEG_LIST_LEN] = {true,  true, true, false,
                                       false, true, true};
constexpr bool char_none[SEG_LIST_LEN] = {false, false, false, false,
                                          false, false, false};

uint8_t Display4x7::createShrVal_(const bool seg_list[SEG_LIST_LEN], bool dot) {
  uint8_t shr_val = 0x0;
  for (int i = 0; i < SEG_LIST_LEN; i++) {
    if (seg_list[i]) shr_val |= 0x1 << seg_pos_[i];
  }

  if (dot) shr_val |= 0x1 << seg_pos_[DOT_POS];

  return shr_val;
}

void Display4x7::init() {
  // Set MOSI and SCK output
  DDRB |= (0x1 << DDB3) | (0x1 << DDB5);
  // Set RCK and digit selection pins as output
  (*rck_ddr_port_) |= (0x1 << rck_pin_);  // Set RCK pin as output
  (*rck_port_) &= ~(0x1 << rck_pin_);     // Set RCK pin low

  for (int i = 0; i < CHAR_NUM; i++) {
    (*dig_ddr_ports_[i]) |=
        (0x1 << dig_pins_[i]);  // Set digit selection pins as output
    (*dig_ports_[i]) &= ~(0x1 << dig_pins_[i]);  // Set digit selection pins low
  }

  // Enable SPI, Master, set clock rate fck/16
  SPCR |= (0x1 << SPE) | (0x1 << MSTR) | (0x1 << SPR0);
}

void Display4x7::display(const char chars[CHAR_NUM],
                         const bool dots[CHAR_NUM]) {
  for (int i = 0; i < CHAR_NUM; i++) {
    switch (chars[i]) {
      case '0':
        digits_bin_[i] = createShrVal_(char_0, dots[i]);
        break;
      case '1':
        digits_bin_[i] = createShrVal_(char_1, dots[i]);
        break;
      case '2':
        digits_bin_[i] = createShrVal_(char_2, dots[i]);
        break;
      case '3':
        digits_bin_[i] = createShrVal_(char_3, dots[i]);
        break;
      case '4':
        digits_bin_[i] = createShrVal_(char_4, dots[i]);
        break;
      case '5':
        digits_bin_[i] = createShrVal_(char_5, dots[i]);
        break;
      case '6':
        digits_bin_[i] = createShrVal_(char_6, dots[i]);
        break;
      case '7':
        digits_bin_[i] = createShrVal_(char_7, dots[i]);
        break;
      case '8':
        digits_bin_[i] = createShrVal_(char_8, dots[i]);
        break;
      case '9':
        digits_bin_[i] = createShrVal_(char_9, dots[i]);
        break;
      case ' ':
        digits_bin_[i] = createShrVal_(char_none, dots[i]);
      default:
        break;
    }
  }
}

void Display4x7::update() {
  (*dig_ports_[cur_digit_]) &=
      ~(0x1 << dig_pins_[cur_digit_]);  // Set current digit selection pin low

  (*rck_port_) &= ~(0x1 << rck_pin_);  // Set RCK low

  cur_digit_ = (cur_digit_ + 1) % CHAR_NUM;  // Move to the next digit

  SPDR = digits_bin_[cur_digit_];  // Write data to SPI data register

  while (!(SPSR & (0x1 << SPIF)))
    ;  // Wait for transmission to complete

  (*dig_ports_[cur_digit_]) |=
      0x1 << dig_pins_[cur_digit_];  // Set next digit selection pin high

  (*rck_port_) |= 0x1 << rck_pin_;  // Set RCK high
}