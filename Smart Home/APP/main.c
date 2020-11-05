/*
 * main.c
 *
 *  Created on: Sep 26, 2020
 *      Author: Omar Fahmy
 */

/*LIB LAYER */
#include "../LIB/STD_TYPES.h"
#include "../LIB/COMMON_MACROS.h"
/* APP LAYER */
#include "main.h"
/* HAL LAYER */
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"
#include "../HAL/Warning LED/WarningLED_Interface.h"
#include "../HAL/Buzzer/Buzzer_Interface.h"
#include "../HAL/DC Motor/DC_Interface.h"
#include "../HAL/LDR/LDR_Interface.h"
#include "../HAL/Light LED/LightLED_Interface.h"
/* MCAL LAYER */
#include "../MCAL/USART/USART_Interface.h"
#include "../MCAL/Global Interrupt/GI_Interface.h"

#include <util/delay.h>

int main (void)
{
	USART_U8Init();
	LCD_U8Init();
	LM35_U8Init();
	Buzzer_U8Init();
	WarningLED_U8Init();
	DC_U8Init();
	LDR_U8Init();
	LightLED_U8Init();

	USART_U8EnableReceiver();
	USART_U8EnableRxInterrupt();
	USART_U8RxSetCallBack(RxISR);
	GI_U8Disable();

	intro();
	getUserCode();
	getPassword();
	showMenu();
	u8 choice;

	while (1)
	{
		getInput(&choice, showMenu);
		switch (choice)
		{
		case TEMPERATURE:
			showTemperature();
			break;
		case LDR:
			showIntensity();
			break;
		case MOTOR:
			motorRotation();
			break;
		case EXIT:
			LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
			LCD_U8SendString("Thank You!");
			_delay_ms(2000);
			terminate();
			break;
		}
		showMenu();
	}

	return 0;
}

u8 intro(void)
{
	LCD_U8SetPosition(LCD_FIRST_ROW, LCD_FOURTH_COLUMN);
	LCD_U8SendString("SMART HOME");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_SIXTH_COLUMN);
	LCD_U8SendString("SYSTEM");
	_delay_ms(2000);
	return NO_ERROR;
}

u8 getUserCode(void)
{
	u8 enteredUserCode = 0, attempts = 1;
	promptForUser();

	for (u8 counter = 0; counter < USERCODE_LENGTH; counter++)
	{
		processInput(&enteredUserCode, promptForUser);
	}

	while (enteredUserCode != USERCODE && attempts < NO_OF_TRIALS)
	{
		enteredUserCode = 0;
		incorrectInput();

		for (u8 counter = 0; counter < USERCODE_LENGTH; counter++)
		{
			processInput(&enteredUserCode, promptForUser);
		}

		attempts++;
	}

	if (enteredUserCode != USERCODE)
	{
		noMoreAttempts();
		terminate();
	}
	return NO_ERROR;
}

u8 promptForUser(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Enter user code: ");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	return NO_ERROR;
}

u8 getPassword(void)
{
	u8 enteredPassword = 0, attempts = 1;
	promptForPassword();

	for (u8 counter = 0; counter < PASSWORD_LENGTH; counter++)
	{
		processInput(&enteredPassword, promptForPassword);
	}

	while (enteredPassword != PASSWORD && attempts < NO_OF_TRIALS)
	{
		enteredPassword = 0;
		incorrectInput();

		for (u8 counter = 0; counter < PASSWORD_LENGTH; counter++)
		{
			processInput(&enteredPassword, promptForPassword);
		}

		attempts++;
	}

	if (enteredPassword != PASSWORD)
	{
		noMoreAttempts();
		terminate();
	}
	return NO_ERROR;
}

u8 promptForPassword(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Enter Password: ");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	return NO_ERROR;
}

u8 processInput(u8* const userInput, u8(*ptrToFun)(void) )
{
	u8 LOC_U8ReceivedCharacter;
	if (userInput != NULL && ptrToFun != NULL)
	{
		getInput(&LOC_U8ReceivedCharacter, ptrToFun);
		LCD_U8SendData(LOC_U8ReceivedCharacter);
		_delay_ms(40);
		*userInput = (*userInput * 10) + (LOC_U8ReceivedCharacter - '0');
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 getInput(u8* const userInput, u8(*ptrToFun)(void) )
{
	if (userInput != NULL && ptrToFun != NULL)
	{
		u8 LOC_U8SensorsFlag = LOW;
		GI_U8Enable();

		while (GLOB_U8CommunicationFlag == LOW)
		{
			checkSensors(&LOC_U8SensorsFlag);
			if (LOC_U8SensorsFlag == HIGH)
			{
				(*ptrToFun)();
				LOC_U8SensorsFlag = LOW;
			}

		}

		GI_U8Disable();
		GLOB_U8CommunicationFlag = LOW;
		*userInput = GLOB_U16ReceivedData;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 checkSensors(u8* const LOC_U8Flag)
{
	f32 temperature, intensity;
	LDR_U8GetIntensity(&intensity);
	LM35_U8GetTemperature(&temperature);
	if (temperature >= MAX_TEMPERATURE)
	{
		*LOC_U8Flag = HIGH;
		LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
		LCD_U8SendString("  TEMPERATURE");
		LCD_U8SetPosition(LCD_SECOND_ROW, LCD_SIXTH_COLUMN);
		LCD_U8SendString("ALERT!");
		DC_U8StopRotation();
	}

	while (temperature >= MAX_TEMPERATURE)
	{
		_delay_ms(50);
		Buzzer_U8On();
		WarningLED_U8On();
		_delay_ms(50);
		Buzzer_U8Off();
		WarningLED_U8Off();
		LM35_U8GetTemperature(&temperature);
	}

	if (intensity <= MINIMUM_INTENSITY)
	{
		LightLED_U8On();
	}
	else
	{
		LightLED_U8Off();
	}

	return NO_ERROR;
}

u8 incorrectInput(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Incorrect!");
	_delay_ms(2000);
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Try again: ");
	return NO_ERROR;
}

u8 noMoreAttempts (void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Incorrect input");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("for 3 times!");
	_delay_ms(2000);
	return NO_ERROR;
}

u8 terminate(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Terminating");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("Program...");
	_delay_ms(2000);
	DC_U8StopRotation();
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);

	while (1)
	{

	}

	return NO_ERROR;
}

u8 showMenu(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("1. Temp  2. LDR");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("3. Motor 4. Exit");
	return NO_ERROR;
}

u8 motorRotation(void)
{
	u8 choice;
	motorMenu();
	getInput(&choice, motorMenu);
	switch (choice)
	{
	case CLOCKWISE:
		DC_U8RotateClockWise();
		break;
	case ANTI_CLOCKWISE:
		DC_U8RotateAntiClockWise();
		break;
	}
	return NO_ERROR;
}

u8 motorMenu(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("1. Rotate CW");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("2. Rotate ACW");
	return NO_ERROR;
}

u8 showTemperature(void)
{
	f32 LOC_F32Temperature;
	u8 LOC_U8SensorsFlag = LOW;
	printTempFrame();
	GI_U8Enable();

	while (GLOB_U8CommunicationFlag == LOW)
	{
		checkSensors(&LOC_U8SensorsFlag);
		if (LOC_U8SensorsFlag == HIGH)
		{
			printTempFrame();
			LOC_U8SensorsFlag = LOW;
		}
		LM35_U8GetTemperature(&LOC_F32Temperature);
		LCD_U8SetPosition(LCD_FIRST_ROW, LCD_SEVENTH_COLUMN);
		LCD_U8SendNumber(LOC_F32Temperature);
	}

	GI_U8Disable();
	GLOB_U8CommunicationFlag = LOW;
	return NO_ERROR;
}

u8 showIntensity(void)
{
	f32 LOC_F32Intensity;
	u8 LOC_U8SensorsFlag = LOW;
	printIntensityFrame();
	GI_U8Enable();

	while (GLOB_U8CommunicationFlag == LOW)
	{
		checkSensors(&LOC_U8SensorsFlag);
		if (LOC_U8SensorsFlag == HIGH)
		{
			printIntensityFrame();
			LOC_U8SensorsFlag = LOW;
		}
		LDR_U8GetIntensity(&LOC_F32Intensity);
		LCD_U8SetPosition(LCD_FIRST_ROW, LCD_TWELFTH_COLUMN);
		LCD_U8SendNumber(LOC_F32Intensity);
	}

	GI_U8Disable();
	GLOB_U8CommunicationFlag = LOW;
	return NO_ERROR;
}

u8 printTempFrame(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Temp: ");
	LCD_U8SetPosition(LCD_FIRST_ROW, LCD_FOURTEENTH_COLUMN);
	LCD_U8SendData('C');
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("Press Any Key...");
	return NO_ERROR;
}

u8 printIntensityFrame(void)
{
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Intensity: ");
	LCD_U8SetPosition(LCD_FIRST_ROW, LCD_SIXTEENTH_COLUMN);
	LCD_U8SendData('%');
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("Press Any Key...");
	return NO_ERROR;
}

void RxISR(void)
{
	USART_U8ReceiveData(&GLOB_U16ReceivedData);
	GLOB_U8CommunicationFlag = HIGH;
}
