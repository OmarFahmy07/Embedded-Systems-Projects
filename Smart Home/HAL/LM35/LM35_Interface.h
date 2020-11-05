/*
 * LM35_Interface.h
 *
 *  Created on: Sep 26, 2020
 *      Author: Omar Fahmy
 */

#ifndef HAL_LM35_LM35_INTERFACE_H_
#define HAL_LM35_LM35_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/************************************************************************************/
/* 								FUNCTIONS PROTOTYPE					 				*/
/************************************************************************************/

/************************************************************************************/
/* Description: initializes LM35 by enabling ADC				  					*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LM35_U8Init(void);

/************************************************************************************/
/* Description: gets the temperature sensed by the LM35 in degrees celsius			*/
/* Input      : pointer to a variable to receive the value in                       */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LM35_U8GetTemperature(f32* LOC_U8Temp);
/************************************************************************************/


#endif /* HAL_LM35_LM35_INTERFACE_H_ */
