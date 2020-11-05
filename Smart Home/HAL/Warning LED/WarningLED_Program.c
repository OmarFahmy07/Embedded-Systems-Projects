/*
 * WarningLED_Program.c
 *
 *  Created on: Sep 27, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
/* HAL LAYER */
#include "WarningLED_Configure.h"
/* MCAL LAYER */
#include "../../MCAL/DIO/DIO_Interface.h"

u8 WarningLED_U8Init(void)
{
	DIO_U8SetPinDirection(PORT, PIN, DIO_PIN_OUTPUT);
	return NO_ERROR;
}

u8 WarningLED_U8On(void)
{
	DIO_U8SetPinValue(PORT, PIN, DIO_PIN_HIGH);
	return NO_ERROR;
}

u8 WarningLED_U8Off(void)
{
	DIO_U8SetPinValue(PORT, PIN, DIO_PIN_LOW);
	return NO_ERROR;
}
