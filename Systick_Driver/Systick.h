/*
 * Systick.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Yasmin Tarek
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


typedef enum{
	Systick_enuOk,
	Systick_enuNok,

}Systick_tenuErrorStatus;
/* pointer to function type to create call back function */
typedef void(*pCbf)(void);

/*************************************functions prototype*****************************************/
/*************************************************************************************************
 * function: Systick_vidInit
 * I/P Arguments: void:	nothing to pass
 * Return value	: void:	nothing to return
 * description: This function is used to init the systick timer
 **************************************************************************************************/
extern void Systick_vidInit(void);

/*************************************************************************************************
 * function: Systick_enuSetTime
 * I/P Arguments: u32 Copy_u32Time_ms:
 * 						you should pass the needed time in  m.seconds
 * Return value	: Systick_tenuErrorStatus:
 * 						return the status:
 * 						1- Systick_enuOk:  means that the function is done well
 * 						2- Systick_enuNok: means that there are an error
 * description: This function is used to set the wanted time of the systick
 **************************************************************************************************/
extern Systick_tenuErrorStatus Systick_enuSetTime(u32 Copy_u32Time_ms);

/*************************************************************************************************
 * function: Systick_vidInit
 * I/P Arguments: void:	nothing to pass
 * Return value	: void:	nothing to return
 * description: This function is used to enable the systick timer
 **************************************************************************************************/
extern void Systick_vidStart(void);

/*************************************************************************************************
 * function: Systick_vidRegCbf
 * I/P Arguments: pCbf Add_pfFuncName:
 * 						pointer to function (of the function that you want to call when interrupt fired)
 * Return value	: Systick_tenuErrorStatus:
 * 						return the status:
 * 						1- Systick_enuOk:  means that the function is done well
 * 						2- Systick_enuNok: means that there are an error
 * description: This function is used to make the Driver able to call a function from the application layer
 * 			by passing the required function through this call back function
 **************************************************************************************************/
extern Systick_tenuErrorStatus Systick_vidRegCbf(pCbf Add_pfFuncName);


#endif /* SYSTICK_H_ */
