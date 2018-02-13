#include <avr/io.h>

#ifndef F_CPU
#warning "F_CPU was not defined, defaulting to 16MHz"
#define F_CPU 16000000UL  // must be unsigned long
#endif
#define BAUD 31250UL
#include <util/setbaud.h>

void init () {
  DDRB = 0xFF;  // all outputs
  PORTB = 0x00; // all low
}

int main (void) {
  init ();
  return 0;
}
