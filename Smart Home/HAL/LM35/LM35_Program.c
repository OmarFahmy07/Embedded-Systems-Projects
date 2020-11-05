/*
 * LM35_Program.c
 *
 *  Created on: Sep 26, 2020
 *      Author: Omar Fahmy
 */

#ifndef HAL_LM35_LM35_PROGRAM_C_
#define HAL_LM35_LM35_PROGRAM_C_

/* LIB LAYER */
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* HAL LAYER */
#include "LM35_Configure.h"
#include "LM35_Private.h"
/* MCAL LAYER */
#include "../../MCAL/ADC/ADC_Interface.h"

u8 LM35_U8Init(void)
{
	ADC_U8Init();
	ADC_U8EnableADC();
	return NO_ERROR;
}

u8 LM35_U8GetTemperature(f32* LOC_U32Temp)
{
	if (LOC_U32Temp != NULL)
	{
		u16 LOC_U16Value;
		ADC_U8SelectChannel(CHANNEL);
		ADC_U8StartConversion();
		ADC_U8PollingOnFlag();
		ADC_U8Read10BitDigitalValue(&LOC_U16Value);
		*LOC_U32Temp = UNIT_CONVERSION * LOC_U16Value * VREF / (f32)RESOLUTION;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

#endif /* HAL_LM35_LM35_PROGRAM_C_ */
