#include "main.hpp"
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  if(digitalRead(2) == HIGH || digitalRead(3) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}