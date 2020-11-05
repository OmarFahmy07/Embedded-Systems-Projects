/*
 * DC_Program.c
 *
 *  Created on: Sep 24, 2020
 *      Author: Omar Fahmy
 */
/* LIB LAYER */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
/* HAL LAYER */
#include "../DC Motor/DC_Configure.h"
/* MCAL LAYER */
#include "../../MCAL/DIO/DIO_Interface.h"

/***********************************************************************************/
/* 							PUBLIC FUNCTIONS IMPLEMENTATION						   */
/***********************************************************************************/

u8 DC_U8Init(void)
{
#if TERMINAL1_PORT >= DIO_PORTA && TERMINAL1_PORT <= DIO_PORTD
#if TERMINAL1_PIN >= DIO_PIN0 && TERMINAL1_PIN <= DIO_PIN7
#if TERMINAL2_PORT >= DIO_PORTA && TERMINAL2_PORT <= DIO_PORTD
#if TERMINAL2_PIN >= DIO_PIN0 && TERMINAL2_PIN <= DIO_PIN7
	DIO_U8SetPinDirection(TERMINAL1_PORT, TERMINAL1_PIN, DIO_PIN_OUTPUT);
	DIO_U8SetPinDirection(TERMINAL2_PORT, TERMINAL2_PIN, DIO_PIN_OUTPUT);
#else
#error "Incorrect terminal 2 pin"
#endif
#else
#error "Incorrect terminal 2 port"
#endif
#else
#error "Incorrect terminal 1 pin"
#endif
#else
#error "Incorrect terminal 1 port"
#endif
	return NO_ERROR;
}

u8 DC_U8RotateClockWise(void)
{
#if TERMINAL1_PORT >= DIO_PORTA && TERMINAL1_PORT <= DIO_PORTD
#if TERMINAL1_PIN >= DIO_PIN0 && TERMINAL1_PIN <= DIO_PIN7
#if TERMINAL2_PORT >= DIO_PORTA && TERMINAL2_PORT <= DIO_PORTD
#if TERMINAL2_PIN >= DIO_PIN0 && TERMINAL2_PIN <= DIO_PIN7
	DIO_U8SetPinValue(TERMINAL1_PORT, TERMINAL1_PIN, DIO_PIN_HIGH);
	DIO_U8SetPinValue(TERMINAL2_PORT, TERMINAL2_PIN, DIO_PIN_LOW);
#else
#error "Incorrect terminal 2 pin"
#endif
#else
#error "Incorrect terminal 2 port"
#endif
#else
#error "Incorrect terminal 1 pin"
#endif
#else
#error "Incorrect terminal 1 port"
#endif
	return NO_ERROR;
}

u8 DC_U8RotateAntiClockWise(void)
{
#if TERMINAL1_PORT >= DIO_PORTA && TERMINAL1_PORT <= DIO_PORTD
#if TERMINAL1_PIN >= DIO_PIN0 && TERMINAL1_PIN <= DIO_PIN7
#if TERMINAL2_PORT >= DIO_PORTA && TERMINAL2_PORT <= DIO_PORTD
#if TERMINAL2_PIN >= DIO_PIN0 && TERMINAL2_PIN <= DIO_PIN7
	DIO_U8SetPinValue(TERMINAL1_PORT, TERMINAL1_PIN, DIO_PIN_LOW);
	DIO_U8SetPinValue(TERMINAL2_PORT, TERMINAL2_PIN, DIO_PIN_HIGH);
#else
#error "Incorrect terminal 2 pin"
#endif
#else
#error "Incorrect terminal 2 port"
#endif
#else
#error "Incorrect terminal 1 pin"
#endif
#else
#error "Incorrect terminal 1 port"
#endif
	return NO_ERROR;
}

u8 DC_U8StopRotation(void)
{
#if TERMINAL1_PORT >= DIO_PORTA && TERMINAL1_PORT <= DIO_PORTD
#if TERMINAL1_PIN >= DIO_PIN0 && TERMINAL1_PIN <= DIO_PIN7
#if TERMINAL2_PORT >= DIO_PORTA && TERMINAL2_PORT <= DIO_PORTD
#if TERMINAL2_PIN >= DIO_PIN0 && TERMINAL2_PIN <= DIO_PIN7
	DIO_U8SetPinValue(TERMINAL1_PORT, TERMINAL1_PIN, DIO_PIN_HIGH);
	DIO_U8SetPinValue(TERMINAL2_PORT, TERMINAL2_PIN, DIO_PIN_HIGH);
#else
#error "Incorrect terminal 2 pin"
#endif
#else
#error "Incorrect terminal 2 port"
#endif
#else
#error "Incorrect terminal 1 pin"
#endif
#else
#error "Incorrect terminal 1 port"
#endif
	return NO_ERROR;
}

