/*
 * WarningLED_Interface.h
 *
 *  Created on: Sep 27, 2020
 *      Author: Omar Fahmy
 */

#ifndef HAL_WARNING_LED_WARNINGLED_INTERFACE_H_
#define HAL_WARNING_LED_WARNINGLED_INTERFACE_H_

/************************************************************************************/
/* 								FUNCTIONS PROTOTYPE					 				*/
/************************************************************************************/

/************************************************************************************/
/* Description: initializes the LED used for warning		  						*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 WarningLED_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: turns the LED on		  											*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 WarningLED_U8On(void);
/************************************************************************************/

/************************************************************************************/
/* Description: turns the LED off		  											*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 WarningLED_U8Off(void);
/************************************************************************************/


#endif /* HAL_WARNING_LED_WARNINGLED_INTERFACE_H_ */
