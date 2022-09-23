#if DEBUG
  #include <avr/interrupt.h>

  #define AVR8_GDB_STUB

  // For Mega which has multiple UARTs, select the number
  // ATmega328 only ahs one UART
  //#define AVR8_UART_NUMBER (1)

  // #define AVR8_BREAKPOINT_MODE (1)
  // #define AVR8_SWINT_SOURCE 

  #include "avr8-stub.h"
  #include "app_api.h"

  #define BREAKPOINT breakpoint();
  #define DEBUG_MESSAGE(__msg) debug_message(__msg);
  #define INIT_DEBUGGER() { debug_init(); sei(); }

#else
  #define BREAKPOINT
  #define DEBUG_MESSAGE(__msg)
  #define INIT_DEBUGGER()
#endif