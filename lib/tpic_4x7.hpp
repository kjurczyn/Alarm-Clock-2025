#ifndef tpic_4x7
#define tpic_4x7
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

namespace tpic_4x7 {
struct SegPos {  // segment pin locations on tpic
  uint8_t A;
  uint8_t B;
  uint8_t C;
  uint8_t D;
  uint8_t E;
  uint8_t F;
  uint8_t G;
  uint8_t dot;
};

class Display4x7 {
 public:
  Display4x7(const uint8_t* dig_pins[4], const struct SegPos* seg_pos)
      : dig_pins_({*dig_pins[0], *dig_pins[1], *dig_pins[2], *dig_pins[3]}),
        seg_pos_(*seg_pos),
        digits_({0, 0, 0, 0}),
        dots_({false, false, false, false}),
        cur_digit_(0){};

  void display(uint8_t digits[4]);
  void update();

 private:
  const uint8_t dig_pins_[4];
  const struct SegPos seg_pos_;

  uint8_t digits_[4];
  bool dots_[4];
  uint8_t cur_digit_;
};

}  // namespace tpic_4x7

#endif