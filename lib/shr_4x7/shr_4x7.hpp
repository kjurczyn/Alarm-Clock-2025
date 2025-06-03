#ifndef tpic_4x7
#define tpic_4x7
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define CHAR_NUM 4
#define SEG_LIST_LEN 7

struct PortsPins_Display4x7 {
  volatile uint8_t* const dig_ports[4];
  volatile uint8_t* const dig_ddr_ports[4];
  const uint8_t dig_pins[4];

  volatile uint8_t* const rck_port;
  volatile uint8_t* const rck_ddr_port;
  const uint8_t rck_pin;

  const uint8_t seg_pos[8];  // A, B, C, D, E, F, G, dot
};

class Display4x7 {
 public:
  /**
   * @brief Constructor for the Display4x7 class.
   *
   * Initializes the 4-digit 7-segment display by assigning digit selection pins
   * and positions of segments connected to the TPIC shift register.
   *
   * @param dig_pins Pointer to array of the digit selection (1-4) pins (4
   * elements).
   * @param seg_pos Pointer to array of TPIC positions of segments (A, B, .., G,
   * dot) (8 elements).
   */
  Display4x7(const struct PortsPins_Display4x7* ports_pins)
      : dig_ports_{ports_pins->dig_ports[0], ports_pins->dig_ports[1],
                   ports_pins->dig_ports[2], ports_pins->dig_ports[3]},

        dig_ddr_ports_{
            ports_pins->dig_ddr_ports[0], ports_pins->dig_ddr_ports[1],
            ports_pins->dig_ddr_ports[2], ports_pins->dig_ddr_ports[3]},

        dig_pins_{ports_pins->dig_pins[0], ports_pins->dig_pins[1],
                  ports_pins->dig_pins[2], ports_pins->dig_pins[3]},

        rck_port_(ports_pins->rck_port),
        rck_ddr_port_(ports_pins->rck_ddr_port),
        rck_pin_(ports_pins->rck_pin),

        seg_pos_{ports_pins->seg_pos[0], ports_pins->seg_pos[1],
                 ports_pins->seg_pos[2], ports_pins->seg_pos[3],
                 ports_pins->seg_pos[4], ports_pins->seg_pos[5],
                 ports_pins->seg_pos[6], ports_pins->seg_pos[7]},
        digits_bin_{},
        cur_digit_{} {};

  void init();
  void display(const char chars[CHAR_NUM], const bool dots[CHAR_NUM]);
  void update();

 private:
  uint8_t digits_bin_[4];
  uint8_t cur_digit_;

  volatile uint8_t* const dig_ports_[4];
  volatile uint8_t* const dig_ddr_ports_[4];
  const uint8_t dig_pins_[4];

  volatile uint8_t* const rck_port_;
  volatile uint8_t* const rck_ddr_port_;
  const uint8_t rck_pin_;

  const uint8_t seg_pos_[8];  // A, B, C, D, E, F, G, dot

  uint8_t createShrVal_(const bool seg_list[SEG_LIST_LEN], bool dot);
};

#endif