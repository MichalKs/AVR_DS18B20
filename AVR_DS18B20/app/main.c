/**
 * @file: 	main.c
 * @brief:	LED test
 * @date: 	9 kwi 2014
 * @author: Michal Ksiezopolski
 *
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <led.h>
#include <timers.h>
#include <comm.h>
#include <printf_setup.h>
#include <onewire.h>
#include <ds18b20.h>

#define SYSTICK_FREQ 1000 ///< Frequency of the SysTick set at 1kHz.
#define COMM_BAUD_RATE 115200UL ///< Baud rate for communication with PC

void softTimerCallback(void);

#define DEBUG

#ifdef DEBUG
#define print(str, args...) printf("MAIN--> "str"%s",##args,"\r")
#define println(str, args...) printf("MAIN--> "str"%s",##args,"\r\n")
#else
#define print(str, args...) (void)0
#define println(str, args...) (void)0
#endif

/**
 * @brief Main function
 * @return
 */
int main(void) {

  COMM_Init(COMM_BAUD_RATE);

  printfSetup();

  println("Starting program");

  TIMER_Init(SYSTICK_FREQ); // Initialize timer

  // Add a soft timer with callback running every 1000ms
  int8_t timerID = TIMER_AddSoftTimer(1000, softTimerCallback);
  TIMER_StartSoftTimer(timerID);

	LED_Init(LED0); // Add an LED
	LED_Init(LED1); // Add an LED
	LED_Init(LED2); // Add an LED
	LED_ChangeState(LED2, LED_ON);

  ONEWIRE_Init(); // initialize ONEWIRE bus
  DS18B20_Init(); // initialize DS18B20 on the bus

	while (1) {

	  TIMER_SoftTimersUpdate(); // run timers
	}
}

/**
 * @brief Callback function called on every soft timer overflow
 */
void softTimerCallback(void) {

  LED_Toggle(LED1);
  LED_Toggle(LED0);

  static uint8_t counter;
  double temp;
  char buf[10];

  // get temperature every 2 seconds
  switch (counter % 2) {
  case 0:
    DS18B20_ConversionStart();
    break;

  case 1:
    temp = DS18B20_ReadTemp();
    dtostrf(temp,3,2,buf);
    println("Temperature = %s", buf);
    break;

  }

  counter++;

}
