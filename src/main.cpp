#include <avr/io.h>

#include <avr8-stubs-utilities.h>


#include <attos.h>


int main(void)
{
  INIT_DEBUGGER();

  BREAKPOINT;

  DEBUG_MESSAGE("Calling 'attos_scheduler_init(20)'");
  attos_scheduler_init(20);

  for (;;) {}
}