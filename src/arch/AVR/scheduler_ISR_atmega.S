#include <avr/io.h>
#include "context_macros_atmega.S"


.extern attos_scheduler_timer_isr_handler

.section .text
.global TIMER0_COMPA_vect



TIMER0_COMPA_vect:
	SaveContext

	call attos_scheduler_timer_isr_handler

	RestoreContext

	reti