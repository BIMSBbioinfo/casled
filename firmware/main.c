#ifndef F_CPU
#warning "F_CPU was not defined, defaulting to 16MHz"
#define F_CPU 16000000UL  // must be unsigned long
#endif
#define BAUD 31250UL

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>

/* Time between program steps in milliseconds */
#define INTERVAL 1000.0

/*
Click the speaker and toggle the on-board indicator LEDs to indicate
the passing of time.
*/
#define TICK PORTD ^= 1<<PD7; PORTC++;

/* Pins used for serial interface */
#define DD_SCK    PB7 // clock (blue)
#define DD_MOSI   PB5 // data (red)
#define DDR_SPI   DDRB

/*
"Load enable" is connected to the LE pin of the LED drivers.  The
internal state of the shift registers of the driver chips is pushed to
the LED outputs on a falling edge (APPLY).
*/
#define LOAD_PIN PD0 // load enable (green)
#define APPLY (PORTD &= ~(1<<LOAD_PIN))
#define LOAD  (PORTD |= (1<<LOAD_PIN))

/*
There are 6 LED driver chips with 16 outputs each, so we need to
transmit 12 bytes over SPI.
*/
#define LED_BYTES 12

#include "progs.h"


#define LEDS 96

/*
Pointers to the current instruction in the program.  This is read and
updated.
*/
uint8_t* P_COUNTER[LEDS];

/*
LED state and counter.

The most significant bit is 0 for OFF and 1 for ON; the remaining bits
encode the remaining time.  When the remaining time is zero we move on
to the next instruction unless the instruction is HALT.
*/
uint8_t LED_STATE[LEDS];

/*
Pointers to LED blink programs.

This array always points to the first instruction of a program.  It is
needed in order to be able to loop back to the beginning of the
program with the LOOP instruction.  The contents of this array are
named according to the identifiers on the well plate (A-H, 1-12).

The order is all messy because the LEDs are not wired up sequentially
and we're fixing a hardware annoyance in software.  Don't judge.
*/

uint8_t* PROGRAMS[LEDS] = {
  G2, H2, E2, F2,
  G1, H1, E1, F1,

  F3, E3, H3, G3,
  F4, E4, H4, G4,

  G6, H6, E6, F6,
  G5, H5, E5, F5,

  F7, E7, H7, G7,
  F8, E8, H8, G8,

  G10, H10, E10, F10,
  G9, H9, E9, F9,

  F11, E11, H11, G11,
  F12, E12, H12, G12,

  B2, A2, D2, C2,
  B1, A1, D1, C1,

  C3, D3, A3, B3,
  C4, D4, A4, B4,

  B6, A6, D6, C6,
  B5, A5, D5, C5,

  C7, D7, A7, B7,
  C8, D8, A8, B8,

  B10, A10, D10, C10,
  B9, A9, D9, C9,

  C11, D11, A11, BROKEN,
  C12, D12, A12, BROKEN
};

/* Initialize SPI interface. */
void spi_init () {
  // Latch, MOSI, and SCK are outputs, all others are inputs
  DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
  // Enable SPI as Master, clock rate is fck/128
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}

/* Send a byte over SPI and wait for completion. */
void spi_transmit (uint8_t data) {
  SPDR = data;
  uint8_t timeout = 255;
  // Wait for transmission completion
  while (!(SPSR & (1<<SPIF)) && (timeout > 0))
    timeout--;
}

/*
Evaluate the current instruction for all LED programs.

This either leads to a delay counter to be decremented or the next
instruction to be selected.
*/
void prog_eval () {
  // LED states to be sent over serial connection.
  uint8_t bytes[LED_BYTES] = {0};

  for (uint8_t i=0; i < LEDS; i++)
    {
      /*
        Are we still waiting for an ON/OFF instruction to be
        completed?
      */
      if (LED_STATE[i] & 0x7F) {
        // Yes, so just count down.
        LED_STATE[i]--;
      } else {
        /*
          Reset and evaluate the next instruction on LOOP.  The first
          instruction cannot be LOOP.
        */
        if (LOOP == *(P_COUNTER[i]))
          P_COUNTER[i] = PROGRAMS[i];

        if (HALT != *(P_COUNTER[i])) {
          // initialize count down
          LED_STATE[i] = *(P_COUNTER[i]);
          // advance program
          P_COUNTER[i]++;
        }
      }

      /* Set LED on or off in byte message array */
      uint8_t new_state = (LED_STATE[i] >> 7);
      if (new_state) {
        // set bit
        bytes[i / 8] |= (1 << (i % 8));
      } else {
        // clear bit
        bytes[i / 8] &= ~(1 << (i % 8));
      }
    }

  /* Transmit new state for all LEDs */
  LOAD;
  for (uint8_t n = 0; n < LED_BYTES; n++)
    spi_transmit (bytes[n]);
  APPLY;
  TICK;
}

void init (void) {
  spi_init ();
  DDRD = 0xFF;  // all outputs (for speaker and "load enable")
  DDRC = 0xFF;  // all outputs
  PORTC = 0x00; // all activity indicator LEDs on

  /* Turn all external LEDs off initially */
  LOAD;
  for (uint8_t n = 0; n < LED_BYTES; n++)
    spi_transmit (0x00);
  APPLY;

  /* Initialize LED programs and associated state */
  for (uint8_t i = 0; i < LEDS; i++)
    {
      P_COUNTER[i] = PROGRAMS[i];
      LED_STATE[i] = 0x00;
    }
}

int main (void) {
  init ();

  _delay_ms(1000.0);
  while (1) {
    prog_eval ();
    _delay_ms(INTERVAL);
  }

  // This will never happen.
  return 0;
}
