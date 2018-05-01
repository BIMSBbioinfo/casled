#include <avr/io.h>
#include <util/delay.h>

/* LED program instructions */
#define LOOP 0x7F
#define HALT 0xFF

/* Instructions to turn the LED on/off for 1 to 127 units. */
#define LED_ON(n)  ((0x80 | ((n) - 1)))
#define LED_OFF(n) ((0x7F & ((n) - 1)))

/*
NOTE: programs cannot begin with LOOP.  All programs must end with
either LOOP or HALT.
*/

/* This program ensures that the LED stays off. */
uint8_t progOff[] = { LED_OFF(10), LOOP };

/* This program ensures that the LED stays lit. */
uint8_t progOn[]  = { LED_ON(1), HALT };

/* This program lets an LED blink 50/50. */
uint8_t progBlink[] = { LED_ON(1), LED_OFF(1), LOOP };

/* This program lets an LED blink 50/50, but starts in the Off state. */
uint8_t progBlinkOff[] = { LED_OFF(1), LED_ON(1), LOOP };

/* Constant blink for Magnet photo dimer */
uint8_t progMagnetBlink[] = { LED_ON(3), LED_OFF(7), LOOP };

/* Blink, then lock ON for Magnet photo dimer */
uint8_t progMagnetBlinkLockOn[] = {
  LED_ON(3),   /* 1 */
  LED_OFF(7),
  LED_ON(3),   /* 2 */
  LED_OFF(7),
  LED_ON(3),   /* 3 */
  LED_OFF(7),
  LED_ON(3),   /* 4 */
  LED_OFF(7),
  LED_ON(3),   /* 5 */
  LED_OFF(7),
  LED_ON(3),   /* 6 */
  LED_OFF(7),
  LED_ON(3),   /* 7 */
  LED_OFF(7),
  LED_ON(3),   /* 8 */
  LED_OFF(7),
  LED_ON(3),   /* 9 */
  LED_OFF(7),
  LED_ON(3),   /* 10 */
  LED_OFF(7),
  LED_ON(3),   /* 11 */
  LED_OFF(7),
  LED_ON(3),   /* 12 */
  LED_OFF(7),
  LED_ON(3),   /* 13 */
  LED_OFF(7),
  LED_ON(3),   /* 14 */
  LED_OFF(7),
  LED_ON(3),   /* 15 */
  LED_OFF(7),
  LED_ON(3),   /* 16 */
  LED_OFF(7),
  LED_ON(3),   /* 17 */
  LED_OFF(7),
  LED_ON(3),   /* 18 */
  LED_OFF(7),
  LED_ON(3),   /* 19 */
  LED_OFF(7),
  LED_ON(3),   /* 20 */
  LED_OFF(7),

  LED_ON(120),
  LOOP
};

/* Blink, then lock OFF for Magnet photo dimer */
uint8_t progMagnetBlinkLockOff[] = {
  LED_ON(3),   /* 1 */
  LED_OFF(7),
  LED_ON(3),   /* 2 */
  LED_OFF(7),
  LED_ON(3),   /* 3 */
  LED_OFF(7),
  LED_ON(3),   /* 4 */
  LED_OFF(7),
  LED_ON(3),   /* 5 */
  LED_OFF(7),
  LED_ON(3),   /* 6 */
  LED_OFF(7),
  LED_ON(3),   /* 7 */
  LED_OFF(7),
  LED_ON(3),   /* 8 */
  LED_OFF(7),
  LED_ON(3),   /* 9 */
  LED_OFF(7),
  LED_ON(3),   /* 10 */
  LED_OFF(7),
  LED_ON(3),   /* 11 */
  LED_OFF(7),
  LED_ON(3),   /* 12 */
  LED_OFF(7),
  LED_ON(3),   /* 13 */
  LED_OFF(7),
  LED_ON(3),   /* 14 */
  LED_OFF(7),
  LED_ON(3),   /* 15 */
  LED_OFF(7),
  LED_ON(3),   /* 16 */
  LED_OFF(7),
  LED_ON(3),   /* 17 */
  LED_OFF(7),
  LED_ON(3),   /* 18 */
  LED_OFF(7),
  LED_ON(3),   /* 19 */
  LED_OFF(7),
  LED_ON(3),   /* 20 */
  LED_OFF(7),

  LED_OFF(120),
  LOOP
};


/*
Toggle LED on/off for three times, then leave off for 10 mins, then
restart the program.
*/
uint8_t progExample[] = {
  LED_ON(1),
  LED_OFF(1),
  LED_ON(1),
  LED_OFF(1),
  LED_ON(1),
  LED_OFF(127),
  LED_OFF(127),
  LED_OFF(127),
  LED_OFF(127),
  LED_OFF(92),  // 10 mins off
  LOOP // programs MUST end on either LOOP or HALT
};



#define BROKEN progOff

#define A1  progOn
#define A2  progOn
#define A3  progOn
#define A4  progOn
#define A5  progOn
#define A6  progOn
#define A7  progOn
#define A8  progOn
#define A9  progOn
#define A10 progOn
#define A11 progOn
#define A12 progOn

#define B1  progOn
#define B2  progOn
#define B3  progOn
#define B4  progOn
#define B5  BROKEN
#define B6  progOn
#define B7  progOn
#define B8  progOn
#define B9  progOn
#define B10 BROKEN
#define B11 BROKEN
#define B12 BROKEN

#define C1  progOn
#define C2  progOn
#define C3  progOn
#define C4  BROKEN
#define C5  progOn
#define C6  progOn
#define C7  progOn
#define C8  progOn
#define C9  progOn
#define C10 progOn
#define C11 progOn
#define C12 progOn

#define D1  progOn
#define D2  progOn
#define D3  BROKEN
#define D4  progOn
#define D5  BROKEN
#define D6  progOn //BROKEN?
#define D7  progOn
#define D8  progOn
#define D9  progOn
#define D10 BROKEN
#define D11 BROKEN
#define D12 progOn

#define E1  BROKEN
#define E2  progOn
#define E3  progOn
#define E4  progOn
#define E5  progOn
#define E6  progOn
#define E7  progOn
#define E8  progOn
#define E9  progOn
#define E10 progOn
#define E11 progOn
#define E12 progOn

#define F1  progMagnetBlinkLockOff
#define F2  progOff
#define F3  progOn
#define F4  progOn
#define F5  progOn
#define F6  progOn
#define F7  progOn
#define F8  progOn
#define F9  progOn
#define F10 progOn
#define F11 progOn
#define F12 progOn

#define G1  progMagnetBlinkLockOff
#define G2  progOff
#define G3  BROKEN
#define G4  progOn
#define G5  progOn
#define G6  progOn
#define G7  progOn
#define G8  progOn
#define G9  progOn
#define G10 progOn
#define G11 progOn
#define G12 progOn

#define H1  progMagnetBlinkLockOff
#define H2  progOff
#define H3  progOn
#define H4  progOn
#define H5  progOn
#define H6  progOn
#define H7  progOn
#define H8  progOn
#define H9  progOn
#define H10 progOn
#define H11 progOn
#define H12 progOn //BROKEN?
