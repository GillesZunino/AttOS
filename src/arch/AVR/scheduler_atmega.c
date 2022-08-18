#include <avr/io.h>
#include <avr/interrupt.h>


#include <attos.h>


#define CLOCK_TICKS_PER_BURST 1000


unsigned int get_timer0b_prescaler(unsigned int iTicks);
void set_timer0b_prescaler(unsigned int preScaler);



// (1/20)*milliseconds length of interval. I.e. 20 is 1 millisecond.
/*
* Notes: See Atmega328P manual 19.9.x
*        This function performs all actions necessary to start receiving
*        interrupts from timer 0. The maximum timer
*        cycle time is about 12 milliseconds (240 'bursts').
*        This is because the prescaler divides by about 1000 at most, meaning
*        1000*256 gives the longest delay time. (1024 is the actual number)
*/
void attos_scheduler_init(unsigned int aiBursts)
{
   // Ensure we can satisfy the requested burst rate
   unsigned int iTicks = CLOCK_TICKS_PER_BURST * aiBursts;
   if ((iTicks / 1024) < 256) {
      cli();

      // Sets the interrupt Compare Flag Interrupt Enable Bit.
      TIMSK0 |= (1 << OCIE0A);

      // Set timer to CTC Mode. See atmel manual 19.9.1
      TCCR0A &= (0xFC);
      TCCR0A |= (0x1 << WGM01);

      // Clear the Pre-Scaler bits. See atmel manual 19.9.2
      TCCR0B &= (0xF8);
      
      unsigned int prescaler = get_timer0b_prescaler(iTicks);
      set_timer0b_prescaler(prescaler);

      // Set the compare value for timer 0 to aiTicks
      // See manual 19.9.6
      OCR0A =  (iTicks / prescaler) & 0xFF;

      sei();
   } else {
      // Unable to configure the timer - Throw an error
   }
}

unsigned int get_timer0b_prescaler(unsigned int iTicks)
{
   if (iTicks < 256)
   {
      // Set Pre-scaler to 1
      return 1;
   }
   else if (iTicks / 8 < 256)
   {
      // Set Pre-scaler to 8
      return 8;
   }
   else if (iTicks / 64 < 256)
   {
      // Set Pre-scaler to 64
      return 64;
   }
   else if (iTicks / 256 < 256)
   {
      // Set Pre-scaler to 256
      return 256;
   }
   else if (iTicks / 1024 < 256)
   {
      // Set Pre-scaler to 1024
      return 1024;
   }
}

void set_timer0b_prescaler(unsigned int preScaler)
{
   switch (preScaler)
   {
   case 1:
      TCCR0B |= (1 << CS00);
      break;

   case 8:
      TCCR0B |= (1 << CS01);
      break;

   case 64:
      TCCR0B |= (1 << CS00);
      TCCR0B |= (1 << CS01);
      break;

   case 256:
      TCCR0B |= (1 << CS02);
      break;

   case 1024:
      TCCR0B |= (1 << CS00);
      TCCR0B |= (1 << CS02);
      break;

   default:
      // TODO: Return an aerror
      break;
   }
}
   




volatile char ledOn = 0;
volatile unsigned int hits = 0;
const unsigned int blinkModulo = 200;

void attos_scheduler_timer_isr_handler()
{
   // Count the number of hits, and if multiple of 1000 (every second ish), then toggle LED
   hits++;

  if (hits % blinkModulo == 0) {
    hits = 0;
    ledOn = !ledOn;

    if (ledOn) {
      // turn on
      PORTB |= (1 << PB5);
    } else {
      // turn off
      PORTB &= ~(1 << PB5);
    }
  }
}