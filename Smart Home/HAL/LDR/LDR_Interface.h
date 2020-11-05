/*
 * LDR_Interface.h
 *
 *  Created on: Sep 26, 2020
 *      Author: Omar Fahmy
 */

#ifndef HAL_LDR_INTERFACE_H_
#define HAL_LDR_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/************************************************************************************/
/* 								FUNCTIONS PROTOTYPE					 				*/
/************************************************************************************/

/************************************************************************************/
/* Description: initializes LDR by enabling ADC				  						*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LDR_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: gets the intensity percentage of the light falling on the LDR		*/
/* Input      : pointer to a variable to receive the value in                       */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LDR_U8GetIntensity(f32* LOC_U8Intensity);
/************************************************************************************/

#endif /* HAL_LDR_INTERFACE_H_ */
