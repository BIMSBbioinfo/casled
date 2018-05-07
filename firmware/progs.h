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

#define ON_TIME 10
#define OFF_TIME 20

/* Constant blink for Magnet photo dimer */
uint8_t progMagnetBlink[] = { LED_ON(ON_TIME), LED_OFF(OFF_TIME), LOOP };

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

#define A1  progOff
#define A2  progOff
#define A3  progOff
#define A4  progOff
#define A5  progOff
#define A6  progOff
#define A7  progMagnetBlink
#define A8  progMagnetBlink
#define A9  progMagnetBlink
#define A10 progMagnetBlink
#define A11 progMagnetBlink
#define A12 progMagnetBlink

#define B1  progOff
#define B2  progOff
#define B3  progOff
#define B4  progOff
#define B5  BROKEN
#define B6  progOff
#define B7  progMagnetBlink
#define B8  progMagnetBlink
#define B9  progMagnetBlink
#define B10 BROKEN
#define B11 BROKEN
#define B12 BROKEN

#define C1  progOff
#define C2  progOff
#define C3  progOff
#define C4  BROKEN
#define C5  progOff
#define C6  progOff
#define C7  progMagnetBlink
#define C8  progMagnetBlink
#define C9  progMagnetBlink
#define C10 progOff
#define C11 progOff
#define C12 progOff

#define D1  progOff
#define D2  progOff
#define D3  BROKEN
#define D4  progOff
#define D5  BROKEN
#define D6  progOff //BROKEN?
#define D7  progOff
#define D8  progOff
#define D9  progOff
#define D10 BROKEN
#define D11 BROKEN
#define D12 progMagnetBlink

#define E1  BROKEN
#define E2  progOff
#define E3  progOff
#define E4  progOn
#define E5  progOn
#define E6  progOn
#define E7  progOff
#define E8  progOff
#define E9  progOff
#define E10 progMagnetBlink
#define E11 progMagnetBlink
#define E12 progMagnetBlink

#define F1  progOff
#define F2  progOff
#define F3  progOff
#define F4  progOn
#define F5  progOn
#define F6  progOn
#define F7  progOff
#define F8  progOff
#define F9  progOff
#define F10 progMagnetBlink
#define F11 progMagnetBlink
#define F12 progMagnetBlink

#define G1  progOff
#define G2  progOff
#define G3  BROKEN
#define G4  progOn
#define G5  progOn
#define G6  progOn
#define G7  progOff
#define G8  progOff
#define G9  progOff
#define G10 progMagnetBlink
#define G11 progMagnetBlink
#define G12 progMagnetBlink

#define H1  progOff
#define H2  progOff
#define H3  progOff
#define H4  progOn
#define H5  progOn
#define H6  progOn
#define H7  progOff
#define H8  progOff
#define H9  progOff
#define H10 progMagnetBlink
#define H11 progMagnetBlink
#define H12 BROKEN
