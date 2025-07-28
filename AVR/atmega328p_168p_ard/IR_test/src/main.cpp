
#include <Arduino.h>



void setup() {
  // pinMode(13, OUTPUT);
  DDRB |= 1 << PB5;
}

void loop() {
  PORTB ^= 1 << PB5;
}
