/*
 * GPIO.c
 *
 *  Created on: Mar 26, 2022
 *      Author: Yasmin Tarek
 */
#include "Std_types.h"
#include "GPIO.h"

#define NULL 									 (void*)0x00
#define GPIO_PINMODE_MASK			     	     0x00000003
#define GPIO_PIN_OUTPUT_TYPE_CFG_MASK	         0x00000010
#define GPIO_PIN_OUTPUT_TYPE_PIN_MASK		 	 0x00000001
#define GPIO_OUTPUTPIN_SPEED_MASK			     0x00000003
#define GPIO_OUTPUT_MODE_MASK					 0x00000001
#define GPIO_AF_MODE_MASK						 0x00000002
#define GPIO_MODE_VALIDATION_MASK			  	 0b11000000
#define GPIO_SPEED_VALIDATION_MASK			  	 0b01000000
#define GPIO_PIN_PULLUP_PULLDOWN_PIN_MASK		 0x00000003
#define GPIO_PIN_PULLUP_PULLDOWN_CFG_MASK        0x0000000C
#define GPIO_PULLUP_PULLDOWN_CFG_OFFSET	         2
#define GPIO_MODER_PIN_WIDTH					 2
#define GPIO_PUPDR_PIN_WIDTH					 2
#define GPIO_SPEEDR_PIN_WIDTH					 2
#define GPIO_AFR_PIN_WIDTH						 4
#define AFRH_STARTING_PIN_OFFSET				 8
#define GPIO_OUTPUT_TYPE_CFG_OFFSET	         	 4
#define GPIO_PORT_PINS_NUM						 16
#define GPIO_AF_MASK							 0x0000000F
typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;

}GPIO_u32strRegisters;
static volatile GPIO_u32strRegisters* GPIO_penuRegs;
// functions implementation\\

GPIO_enutErrorStatus GPIO_enuInit(GPIO_Init_Config *Add_strGPIO_Config)
{
	GPIO_enutErrorStatus Loc_ErrorStatus = GPIO_enuOk;
	u32 Loc_u32Tempvar;
	u8 Loc_u8NumOfShifts;
	u8 Loc_u8RealCfg;
	u8 Loc_u8PUPDCfg;
	u8 Loc_u8OPTypeCfg;
	u8 Loc_u8OSpeedCfg;

	if(Add_strGPIO_Config == NULL)
	{
		Loc_ErrorStatus = GPIO_enuNOK;
	}
	else if((Add_strGPIO_Config ->pin) >GPIO_PIN_15)
	{
		Loc_ErrorStatus = GPIO_enuNOK;
	}
	else if ((((Add_strGPIO_Config ->mode)& GPIO_PINMODE_MASK) == GPIO_AF_MODE_MASK) && ((Add_strGPIO_Config ->AF_Num)> GPIO_AF_NUM_15))
	{
		Loc_ErrorStatus = GPIO_enuNOK;
	}
	else if ((((Add_strGPIO_Config -> mode)&GPIO_PINMODE_MASK)== GPIO_OUTPUT_MODE_MASK ) &&(((Add_strGPIO_Config -> speed)& GPIO_SPEED_VALIDATION_MASK) != GPIO_SPEED_VALIDATION_MASK) )
	{
		Loc_ErrorStatus = GPIO_enuNOK;
	}
	else if(((Add_strGPIO_Config->mode)&GPIO_MODE_VALIDATION_MASK) != GPIO_MODE_VALIDATION_MASK)
	{
		Loc_ErrorStatus = GPIO_enuNOK;
	}
	else
	{
		GPIO_penuRegs = (volatile GPIO_u32strRegisters*)(Add_strGPIO_Config ->port);
		Loc_u8RealCfg = (Add_strGPIO_Config ->mode) & ~(GPIO_MODE_VALIDATION_MASK);

		Loc_u32Tempvar = GPIO_penuRegs->MODER;
		Loc_u8NumOfShifts = ((Add_strGPIO_Config ->pin)* GPIO_MODER_PIN_WIDTH);
		Loc_u32Tempvar &= ~ (GPIO_PINMODE_MASK<< Loc_u8NumOfShifts);
		Loc_u32Tempvar |= ( ( (u32)Loc_u8RealCfg ) & GPIO_PINMODE_MASK ) << Loc_u8NumOfShifts;
		GPIO_penuRegs -> MODER = Loc_u32Tempvar;
		/******Setting PULLUP PULLDOWN Values******/
		Loc_u32Tempvar = GPIO_penuRegs -> PUPDR;
		Loc_u8NumOfShifts = ( (Add_strGPIO_Config -> pin) * GPIO_PUPDR_PIN_WIDTH );
		Loc_u8PUPDCfg = ( ( ( (u32)Loc_u8RealCfg ) & GPIO_PIN_PULLUP_PULLDOWN_CFG_MASK ) >> GPIO_PULLUP_PULLDOWN_CFG_OFFSET );
		Loc_u32Tempvar &= ~( GPIO_PIN_PULLUP_PULLDOWN_PIN_MASK << Loc_u8NumOfShifts );
		Loc_u32Tempvar |= Loc_u8PUPDCfg << Loc_u8NumOfShifts;
		GPIO_penuRegs -> PUPDR = Loc_u32Tempvar;
		/******Setting OP type******/
		Loc_u32Tempvar = GPIO_penuRegs -> OTYPER;
		Loc_u8NumOfShifts = (Add_strGPIO_Config -> pin);
		Loc_u8OPTypeCfg = ( ( (u32)Loc_u8RealCfg ) & GPIO_PIN_OUTPUT_TYPE_CFG_MASK ) >> GPIO_OUTPUT_TYPE_CFG_OFFSET;
		Loc_u32Tempvar &= ~( GPIO_PIN_OUTPUT_TYPE_PIN_MASK << Loc_u8NumOfShifts );
		Loc_u32Tempvar |= ( (u32)Loc_u8OPTypeCfg ) << Loc_u8NumOfShifts;
		GPIO_penuRegs -> OTYPER = Loc_u32Tempvar;
		/*****Setting Output pin's speed******/
		if( ( ( Add_strGPIO_Config -> mode ) & GPIO_PINMODE_MASK ) == GPIO_OUTPUT_MODE_MASK\
				|| ( ( Add_strGPIO_Config -> mode ) & GPIO_PINMODE_MASK ) == GPIO_AF_MODE_MASK )
		{
			Loc_u32Tempvar = GPIO_penuRegs -> OSPEEDR;
			Loc_u8NumOfShifts = ( (Add_strGPIO_Config -> pin) * GPIO_SPEEDR_PIN_WIDTH );
			Loc_u32Tempvar &= ~( GPIO_OUTPUTPIN_SPEED_MASK << Loc_u8NumOfShifts );
			Loc_u8OSpeedCfg = Add_strGPIO_Config -> speed;
			Loc_u32Tempvar |= ( (u32)Loc_u8OSpeedCfg ) << Loc_u8NumOfShifts;
			GPIO_penuRegs -> OSPEEDR = Loc_u32Tempvar;
		}
		/******Setting AF Configuration*******/
		if( ( ( Add_strGPIO_Config -> mode ) & GPIO_PINMODE_MASK ) == GPIO_AF_MODE_MASK )
		{
			if( ( Add_strGPIO_Config -> pin) <= GPIO_PIN_7 )
			{
				Loc_u32Tempvar = GPIO_penuRegs -> AFRL;
				Loc_u8NumOfShifts = ( (Add_strGPIO_Config -> pin) * GPIO_AFR_PIN_WIDTH );
				Loc_u32Tempvar &= ~(GPIO_AF_MASK << Loc_u8NumOfShifts);
				Loc_u32Tempvar |= ( (u32)(Add_strGPIO_Config -> AF_Num) << Loc_u8NumOfShifts );
				GPIO_penuRegs -> AFRL = Loc_u32Tempvar;
			}
			else
			{
				Loc_u32Tempvar = GPIO_penuRegs -> AFRH;
				Loc_u8NumOfShifts = ( ( (Add_strGPIO_Config ->pin) - AFRH_STARTING_PIN_OFFSET ) * GPIO_AFR_PIN_WIDTH );
				Loc_u32Tempvar &= ~( GPIO_AF_MASK << Loc_u8NumOfShifts );
				Loc_u32Tempvar |= (u32)( (Add_strGPIO_Config ->AF_Num) << Loc_u8NumOfShifts );
				GPIO_penuRegs -> AFRH = Loc_u32Tempvar;
			}
		}
	}
	return Loc_ErrorStatus;
}

GPIO_enutErrorStatus GPIO_enuSetPinValue(GPIO_Init_Config *Add_strGPIO_Config , u8 Copy_u8Value)
{
	GPIO_enutErrorStatus Loc_enuErrorStatus = GPIO_enuOk;
	if(Copy_u8Value!=GPIO_PINVALUE_HIGH && Copy_u8Value!=GPIO_PINVALUE_LOW)
	{
		Loc_enuErrorStatus =GPIO_enuNOK;
	}
	else if( Add_strGPIO_Config == '\0')
	{
		Loc_enuErrorStatus = GPIO_enuNOK;
	}
	else
	{
		if(Copy_u8Value == GPIO_PINVALUE_HIGH)
		{
			((GPIO_u32strRegisters *)Add_strGPIO_Config->port)->BSRR |= Add_strGPIO_Config->pin;

		}
		else
		{
			((GPIO_u32strRegisters *)Add_strGPIO_Config->port)->BSRR |= (Add_strGPIO_Config->pin<<16);
		}
	}

	return Loc_enuErrorStatus;
}
GPIO_enutErrorStatus GPIO_enuGetPinValue(GPIO_Init_Config *Add_strGPIO_Config , u16* Add_pu16Value)
{
	GPIO_enutErrorStatus Loc_enuErrorStatus = GPIO_enuOk;
	if(Add_pu16Value == '\0' || Add_strGPIO_Config == '\0')
	{
		Loc_enuErrorStatus = GPIO_enuNOK;
	}
	if((Add_strGPIO_Config->pin) &  ((GPIO_u32strRegisters *)Add_strGPIO_Config->port)->IDR )
	{
		*Add_pu16Value = GPIO_PINVALUE_HIGH;
	}
	else
	{
		*Add_pu16Value = GPIO_PINVALUE_LOW;
	}
	return Loc_enuErrorStatus;

}
