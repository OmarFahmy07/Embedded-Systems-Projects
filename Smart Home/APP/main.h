/*
 * main.h
 *
 *  Created on: Sep 28, 2020
 *      Author: Omar Fahmy
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

/************************************************************************************/
/*							   MAIN APP DEFINITIONS								    */
/************************************************************************************/
#define USERCODE			111
#define USERCODE_LENGTH		3
#define PASSWORD			123
#define PASSWORD_LENGTH		3
#define NO_OF_TRIALS		3
#define TEMPERATURE			'1'
#define LDR					'2'
#define MOTOR				'3'
#define EXIT				'4'
#define MAX_TEMPERATURE		100
#define MINIMUM_INTENSITY	30
#define CLOCKWISE			'1'
#define ANTI_CLOCKWISE		'2'
#define HIGH				1
#define LOW					0
/************************************************************************************/


/************************************************************************************/
/*								 USART DEFINITIONS							    	*/
/************************************************************************************/
static u8 GLOB_U8CommunicationFlag = LOW;
static u16 GLOB_U16ReceivedData;
/************************************************************************************/


/************************************************************************************/
/*							  FUNCTIONS PROTOTYPE								    */
/************************************************************************************/
extern u8 intro(void);
extern u8 getUserCode(void);
extern u8 getPassword(void);
extern u8 promptForUser(void);
extern u8 promptForPassword(void);
extern u8 getInput(u8* const userInput, u8(*ptrToFun)(void) );
extern u8 processInput(u8* const userInput, u8(*ptrToFun)(void) );
extern u8 incorrectInput(void);
extern u8 noMoreAttempts (void);
extern u8 terminate(void);
extern u8 checkSensors(u8* const LOC_U8Flag);
extern u8 showMenu(void);
extern u8 motorRotation(void);
extern u8 motorMenu(void);
extern u8 showTemperature(void);
extern u8 printTempFrame(void);
extern u8 showIntensity(void);
extern u8 printIntensityFrame(void);
extern void RxISR(void);
/************************************************************************************/


#endif /* APP_MAIN_H_ */
