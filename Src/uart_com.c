/*
 * uart_com.c
 *
 *  Created on: 26.09.2020
 *      Author: M4gic
 */

#include "uart_com.h"


void send_char(char c)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&c, 1, HAL_MAX_DELAY);
}

int __io_putchar(int ch)
{
	send_char(ch);
	return ch;
}


int _write(int file, char *data, int len)
{
   HAL_StatusTypeDef status =
      HAL_UART_Transmit(&huart1, (uint8_t*)data, len, 1000);

   // return # of bytes written - as best we can tell
   return (status == HAL_OK ? len : 0);
}

