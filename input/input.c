#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

int main() {
  // CAUTION: DO NOT set the last two pin direction. They are rx
  // and tx pins and used to program arduino.
  // NOTE: DDR*|PORT*|PIN* returns value at the memory location or
  // the address to which these registers are mapped to and this
  // return is of type (*(volatile uint8_t *)(addr)) so can be
  // read from and written to and reads are not optimized away.

  // Setup
  // Set pins 2 to 7 of bank D to output pins except for pin 4
  // which is set as input pin for driving the program. And pullup
  // pin 4.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    DDRD = DDRD | 0b11101100;
    DDRD = DDRD & 0b11101111;
    PORTD = PORTD & 0b00010000;
  }
  long prevmillis = 0;
  
  // Loop
  while(1) {
    long interval = (PIND & 0b00010000) ? 200 : 1000;
    long currmillis = millis();
    if (currmillis >)
    PORTD = 0b10000100; // set pins 2 and 7 and reset others.
    _delay_ms(delay);
    PORTD = 0b01001000; // set pins 3 and 6 and reset others.
    _delay_ms(delay);
  }
  return 0;
}
