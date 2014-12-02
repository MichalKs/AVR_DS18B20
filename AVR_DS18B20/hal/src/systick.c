/**
 * @file: 	systick.c
 * @brief:	Managing the SysTick
 * @date: 	25 sie 2014
 * @author: Michal Ksiezopolski
 * 
 * @verbatim
 * Copyright (c) 2014 Michal Ksiezopolski.
 * All rights reserved. This program and the 
 * accompanying materials are made available 
 * under the terms of the GNU Public License 
 * v3.0 which accompanies this distribution, 
 * and is available at 
 * http://www.gnu.org/licenses/gpl.html
 * @endverbatim
 */

#include <systick.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @defgroup  SYSTICK SYSTICK
 * @brief     SYSTICK control functions.
 */

/**
 * @addtogroup SYSTICK
 * @{
 */

static volatile uint32_t sysTicks;  ///< Delay timer.

/**
 * @brief Initialize the SysTick with a given frequency
 * @param freq SysTick frequency
 * TODO Set desired frequency
 * @retval 1 Clock initialization failure
 * @retval 0 Clock initialized properly
 */
uint8_t SYSTICK_Init(uint32_t freq) {

  // board is running at 16 MHz

  TCCR0 = (1<<CS01) | (1<<CS00); // prescaler 64
  TCCR0 |= (1<<WGM01); // Compare mode

  TIMSK = (1<<OCIE0); // enable overflow interrupt
  // 16 000 000/64/freq = OCR0
  OCR0 = 16000000UL/64/freq;
  sei(); // enable interrupts to start counting time

  return 0;
}
/**
 * @brief Get the system time
 * @return System time.
 */
uint32_t SYSTICK_GetTime(void) {
  return sysTicks;
}

/**
 * @brief Interrupt handler for SysTick.
 * @param TIMER0_OVF_vect
 */
ISR(TIMER0_COMP_vect) {

  sysTicks++; // Update system time

}

/**
 * @}
 */

