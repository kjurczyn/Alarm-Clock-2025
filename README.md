# Alarm Clock Project
This is the repository for the Microcontroller Systems 2025 homework 2.

## Description
The aim of the project is to create an alarm clock integrated with a thermometer. The time and other information is displayed on a 4x7 segment display multiplexed using a shift register at ~100Hz.  

## Repository structure
The source code for the execcutable is in `src/`. This project also includes 3 libraries under `lib/`:
 - `rtc_approx` for approxminating real-time using the MCU's onboard timers
 - `shr_4x7` for multiplexing a 4x7 digit display using a shift register
 - [TODO] `temp_adc` for measutring temperature using an analog sensor

```
ALARM_CLOCK
│   README
│   platformio.ini    
│   .gitignore
|   .clang-format   
|
└───src
│   │   main.cpp
│   │   main.h
|
└───lib
    │   
    └───rtc_approx
    |   rtc_approx.h
    |   rtc_approx.cpp
    │
    └───shr_4x7
    |   shr_4x7.cpp
    |   shr_4x7.hpp
```


## Functionalities
- The default display mode is time display mode. 
- [IP] Short pressing the left button displays the temperature, short pressing the right button displays the alarm clock time. 
- [TODO] Pressing both buttons together enters the clock into alarm time set mode, where the digits of the alarm time can be incremented using right button and set using the left button. Additionaly the letter 'N' can be set instead of a digit, which will switch off the alarm functionality.
- [TODO] Long pressing the left button enters the clock into time set mode, where digits of the current clock time can be set.

## Materials
| Name  | Amount | Documentation |
| ------------- | ------------- | -------- |
| MB-102 Breadboard  | 2 | - |
| Jumper wires  | -  | - |
| Pushbutton	| 2 | - |
| Passive Piezzo Buzzer | 1 | - |
| LED | 1 | - |
| 2SD965 NPN Transistor | 4 | [link](https://www.alldatasheet.com/datasheet-pdf/view/173371/UTC/2SD965AL-Q-AB3-B.html) |
| LM35 Temperature Sensor | 1 | - |
| 220Ω Resistor	| 10 | - |
| 4.7kΩ Resistor | 4 | - |
| Breadboard Power Supply | 1 | - |
| 74HC595 Shift Register | 1 | [link](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf)|
| 420564L 4x7 Digit CC Display | 1 |  [link](https://www.mantech.co.za/datasheets/products/sma420564l.pdf) |
| Seeeduino Nano Board (ATmega328p) | 1 | [board](https://wiki.seeedstudio.com/Seeeduino-Nano/), [MCU](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)|

## Schematic
![Schematic](/docs/Schematic_v2.png)

## Software Model
The software for the alarm clock was modeled as a state machine. States 3,4,5,6 and 8,9,10,11 each have only one transition triggered by a button press, therefore aren't shown separately.
![Diagram](/docs/State_diagram.png)

## Photo
![Photo](/docs/Photo.jpg)