/**
 * @file: 	onewire_hal.c
 * @brief:	ONEWIRE low level functions
 * @date: 	9 paź 2014
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


#include <onewire_hal.h>
#include <avr/io.h>

#define ONEWIRE_PIN   (1<<1)
#define ONEWIRE_PORT  PORTB
#define ONEWIRE_DIR   DDRB
#define ONEWIRE_INP   PINB

/**
 * @brief Initialize ONEWIRE hardware
 */
void ONEWIRE_HAL_Init(void) {

  ONEWIRE_HAL_ReleaseBus();

}

/**
 * @brief Release the bus. Resistor will pull it up.
 */
void ONEWIRE_HAL_ReleaseBus(void) {

  ONEWIRE_DIR &= ~ONEWIRE_PIN; // input
  ONEWIRE_PORT &= ~ONEWIRE_PIN; // no pullup
}

/**
 * @brief Pull bus low.
 */
void ONEWIRE_HAL_BusLow(void) {

  ONEWIRE_DIR |= ONEWIRE_PIN; // set as output
  ONEWIRE_PORT &= ~ONEWIRE_PIN; // set pin low
}

/**
 * @brief Read the bus
 * @return Read bus state (high or low)
 */
uint8_t ONEWIRE_HAL_ReadBus(void) {

  if (ONEWIRE_INP & ONEWIRE_PIN) {
    return 1;
  } else {
    return 0;
  }
}
