/*
 * Systick.c
 *
 *  Created on: Apr 28, 2022
 *      Author: Yasmin Tarek
 */
#include "Std_types.h"
#include "Systick.h"
#include "Systick_cfg.h"

		/*static functions */
static void Systick_vidStop(void);

		/* private macros and masks */
#define SYSTICK_CLK_SOURCE_AHB_DIV_8	0
#define SYSTICK_CLK_SOURCE_AHB			0x00000004
#define SYSTICK_DISABLE_EXEPTION		0
#define SYSTICK_ENABLE_EXEPTION			0x00000002
#define SYSTICK_DISABLE_COUNTER			0
#define SYSTICK_ENABLE_COUNTER			0x00000001
#define SYSTICK_u8SINGLE_SHOT_MODE		0
#define SYSTICK_u8MULTI_SHOT_MODE		1

#define NULL							(void*)(0x0000)
#define SYSTICK_32MAX_VALUE				0xFFFFFFFF
#define SYSTICK_CLR_REG					0x00000000

/* struct of the peripheral registers*/
typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}Systick_tstrRegisters;

#define SYSTICK_BASE_ADR 			(Systick_tstrRegisters* const)(0xE000E010)
static Systick_tstrRegisters* const Systick= SYSTICK_BASE_ADR;

/* global pointer to function to hold the passed func. from the app. in*/
static pCbf Systick_pfAppInterrupt;

void Systick_vidInit(void)
{
	/* create a local var to change value of control reg. */
	u32 Loc_u32TempReg;
	Loc_u32TempReg = Systick->STK_CTRL;
	Loc_u32TempReg =0;
	/* set the config. parameters in the variable */
	Loc_u32TempReg |= SYSTICK_EXEPTION;
	Loc_u32TempReg |= SYSTICK_CLK_SOURCE;
	/* put the value in the reg. */
	Systick->STK_CTRL=Loc_u32TempReg;

}
Systick_tenuErrorStatus Systick_enuSetTime(u32 Copy_u32Time_ms)
{
	Systick_tenuErrorStatus Loc_enuStatusError = Systick_enuOk;
	u32 Loc_u32CountTime_ms;
	u32 Loc_u32CountNum;
	/* check if the given value from user is within the range */
	if( Copy_u32Time_ms > SYSTICK_32MAX_VALUE )
	{
		Loc_enuStatusError =Systick_enuNok;
	}
	else
	{
					/* from configurations file  */
		/* calculete the tick time (1/sys. freq)
		 * 						or (1/(sys. freq/8)) in case of (AHB/8)
		 */
#if		SYSTICK_CLK_SOURCE == SYSTICK_CLK_SOURCE_AHB
		Loc_u32CountTime_ms =(1 / SYSTICK_SYS_CLK_FREQUENCY) * 1000;
#elif	SYSTICK_CLK_SOURCE == SYSTICK_CLK_SOURCE_AHB_DIV_8
		Loc_u32CountTime_ms =(1 / (SYSTICK_SYS_CLK_FREQUENCY /8)) * 1000;
#endif
		/* calculate no. of ticks by divide the given time over the tick time */
		Loc_u32CountNum = Copy_u32Time_ms/Loc_u32CountTime_ms;
#if 	SYSTICK_MODE == SYSTICK_u8MULTI_SHOT_MODE
		Systick->STK_LOAD = (Loc_u32CountNum-1);

#elif	SYSTICK_MODE == SYSTICK_u8SINGLE_SHOT_MODE
		Systick -> STK_LOAD = Loc_u32CountNum;
#endif


	}
	/*return the error status*/
	return Loc_enuStatusError;
}

void Systick_vidStart(void)
{
	/*ENBLE the systick timer from control reg*/
	Systick -> STK_CTRL |= SYSTICK_ENABLE_COUNTER;
}
Systick_tenuErrorStatus Systick_vidRegCbf(pCbf Add_pfFuncName)
{
	Systick_tenuErrorStatus Loc_enuErrorStatus = Systick_enuOk;
	if(Add_pfFuncName == NULL)
	{
		Loc_enuErrorStatus = Systick_enuNok;
	}
	else
	{
		Systick_pfAppInterrupt = Add_pfFuncName;
	}

	return Loc_enuErrorStatus;
}
void __attribute__ ((section(".after_vectors"),weak))
Systick_Handler(void)
{
	if(Systick_pfAppInterrupt != NULL)
	{
#if		SYSTICK_MODE == SYSTICK_u8SINGLE_SHOT_MODE
		Systick_pfAppInterrupt();
		Systick_vidStop();
#elif	SYSTICK_MODE == SYSTICK_u8MULTI_SHOT_MODE
		Systick_pfAppInterrupt();

#endif

	}
}

void Systick_vidStop(void)
{
	/* clear enable bit to disable the systick */
	Systick-> STK_CTRL &= ~SYSTICK_ENABLE_COUNTER;
}
