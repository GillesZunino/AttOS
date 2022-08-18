#include <avr/io.h>

#include <attos.h>


int main(void)
{
  attos_scheduler_init(20);

  for (;;) {}
}