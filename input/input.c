// This program sets timer interrupt and pin 4 of bank D as input
// pin. The timer interrupt handler counts down to 100 interrupts
// or 20 interrupts corresponding to 1s or 0.2s and then checks in
// put pin 4's value and based on that sets the countdown to 20 in
// case pin 4 is high or 100 in case pin 4 is low and toggles
// 'ledset' state variable that determines which outout pins to
// switch on and off. Thus based on the input pin 4's value the
// interrupt service routine changes program state which has an
// effect on the program behavior as seen through output leds.
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

long cintr = 0;
long mintr = 100;
int ledset = 1;

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
  DDRD = DDRD | 0b11101100; // set pins 2,3,5,6,7 as out
  DDRD = DDRD & 0b11101111; // set pin 4 as in
  PORTD = PORTD & 0b00010000; // pull up pin 4
  // Set the timer
  TCCR0A = (1 << WGM01); // set CTC bit.
  OCR0A = 195; // set comparator register value
  TIMSK0 = (1 << OCIE0A); // enable timer step 1: enable timer
  sei(); // enable timer step 2: enable interrupts
  TCCR0B = (1 << CS02) | (1 << CS00); // start timer: set prescalar to 1024
  
  // Loop
  // Keep polling ledset every 1ms and set pins accordingly
  while(1) {
    if (ledset)
      PORTD = 0b10000100; // set pins 2 and 7 and reset others.
    else
      PORTD = 0b01001000; // set pins 3 and 6 and reset others.
    _delay_ms(1);
  }
  return 0;
}

// There is 1 timer interrupt every 10ms so after maxintr timer
// interrupts i.e. after 0.2s or 1s depending on what the input
// pin 4 value is, toggle ledset.
ISR(TIMER0_COMPA_vect) {
  cintr++;
  if (cintr > mintr) {
    ledset = (ledset == 0)? 1 : 0;
    mintr = (PIND & 0b00010000) ? 50 : 100;
    cintr = 0;
  }
}
