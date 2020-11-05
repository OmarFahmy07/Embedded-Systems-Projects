/*
 * LDR_Program.c
 *
 *  Created on: Sep 26, 2020
 *      Author: Omar Fahmy
 */

#ifndef HAL_LDR_PROGRAM_C_
#define HAL_LDR_PROGRAM_C_

/* LIB LAYER */
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* HAL LAYER */
#include "LDR_Configure.h"
/* MCAL LAYER */
#include "../../MCAL/ADC/ADC_Interface.h"

u8 LDR_U8Init(void)
{
	ADC_U8Init();
	ADC_U8EnableADC();
	return NO_ERROR;
}

u8 LDR_U8GetIntensity(f32* LOC_F32Intensity)
{
	if (LOC_F32Intensity != NULL)
	{
		u16 LOC_U16Digital;
		f32 LOC_F32Analog;
		ADC_U8SelectChannel(CHANNEL);
		ADC_U8StartConversion();
		ADC_U8PollingOnFlag();
		ADC_U8Read10BitDigitalValue(&LOC_U16Digital);
		LOC_F32Analog = LOC_U16Digital * VREF / (f32)RESOLUTION;
		*LOC_F32Intensity = (5 - LOC_F32Analog) / 5 * 100;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

#endif /* HAL_LDR_PROGRAM_C_ */
