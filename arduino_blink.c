#include <avr/io.h>
#include <util/delay.h>

int main() {
  // setup
  // CAUTION: DO NOT set the last two pin direction. They are rx and tx pins and used to program arduino.
  DDRD = DDRD | 0b11111110;
  // loop
  while(1) {
    PORTD = 0b10000100;
    _delay_ms(200);
    PORTD = 0b01001000;
    _delay_ms(200);
  }
  return 0;
}
