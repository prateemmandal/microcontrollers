// This program blinks the pins 2 and 7 and then pins 3 and 6 alternatively.
// Add LEDs with 220 ohm resistors to these pins at one ed and to GND pin.
#include <avr/io.h>
#include <util/delay.h>

int main() {
  // Setup
  // CAUTION: DO NOT set the last two pin direction. They are rx and tx pins
  // and used to program arduino.
  // Set pins 2 to 7 of bank D to output pins.
  DDRD = DDRD | 0b11111100;
  
  // Loop
  while(1) {
    PORTD = 0b10000100; // set pins 2 and 7 and reset others.
    _delay_ms(200);
    PORTD = 0b01001000; // set pins 3 and 6 and reset others.
    _delay_ms(200);
  }
  return 0;
}
