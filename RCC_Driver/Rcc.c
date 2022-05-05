/*
 * Rcc.c
 *
 *  Created on: Mar 11, 2022
 *      Author: Yasmin Tarek
 */
#include "Std_types.h"
#include "Rcc.h"


// masks to get the selection
#define AHB1_MASK		0x00000000
#define AHB2_MASK		0x40000000
#define APB1_MASK		0x80000000
#define APB2_MASK		0xc0000000


#define CHECK_PERI_MASK			0xc0000000
#define CLEAR_SELECTION_BITS	0x3fffffff

typedef struct{
  volatile u32 RCC_CR;          // RCC clock control register
  volatile u32 RCC_PLLCFGR;			/* RCC PLL configuration register */
  volatile u32 RCC_CFGR;				/* RCC clock configuration register */
  volatile u32 RCC_CIR;				/* RCC clock interrupt register */
  volatile u32 RCC_AHB1RSTR;
  volatile u32 RCC_AHB2RSTR;
  volatile u32 RESERVED_1[2];
  volatile u32 RCC_APB1RSTR;
  volatile u32 RCC_APB2RSTR;
  volatile u32 RESERVED_2[2];
  volatile u32 RCC_AHB1ENR;
  volatile u32 RCC_AHB2ENR;
  volatile u32 RESERVED_3[2];
  volatile u32 RESERVED_4[2];
  volatile u32 RCC_APB1ENR;
  volatile u32 RCC_APB2ENR;
  volatile u32 RCC_AHB1LPENR;
  volatile u32 RCC_AHB2LPENR;
  volatile u32 RESERVED_5[2];
  volatile u32 RCC_APB1LPENR;
  volatile u32 RCC_APB2LPENR;
  volatile u32 RESERVED_6[2];
  volatile u32 RCC_BDCR;
  volatile u32 RCC_CSR;
  volatile u32 RESERVED_7[2];
  volatile u32 RCC_SSCGR;
  volatile u32 RCC_PLLI2SCFGR;
  volatile u32 RCC_RESERVED_8;
  volatile u32 RCC_DCKCFGR;
} Rcc_u32strRegisters;

#define RCC_BASE_ADD  0x40023800
#define RCC ((volatile Rcc_u32strRegisters*)(RCC_BASE_ADD))

Rcc_enuErrorStatus Rcc_enuSelectSysClk(u32 Copy_u8SysClk)
{
	Rcc_enuErrorStatus Loc_ErrorStatus;
	Loc_ErrorStatus = Rcc_enuOk;
	if(Copy_u8SysClk == RCC_SYSCLK_HSI ||Copy_u8SysClk == RCC_SYSCLK_HSE||Copy_u8SysClk == RCC_SYSCLK_PLL)
	{
		u32 tempVar = RCC->RCC_CFGR;
		tempVar &=~ RCC_SW_MASK;
		tempVar |= Copy_u8SysClk;
		RCC->RCC_CFGR = tempVar;
	}
	else
	{
		Loc_ErrorStatus = Rcc_enuSysClkSrcError;
	}
	return Loc_ErrorStatus;
}


Rcc_enuErrorStatus Rcc_enuPllConfig(u32 Copy_u8Vco, u8 Copy_u8PllQ , u8 Copy_u8PllP , u16 Copy_u16PllN ,u8 Copy_u8PllM )
{
	Rcc_enuErrorStatus Loc_ErrorStatus = Rcc_enuOk;
	if(Copy_u8Vco > 1)
	{
		Loc_ErrorStatus= Rcc_enuPllVcoError;
	}
	//Check q value between 2 and 15
	else if(Copy_u8PllQ >=2 && Copy_u8PllQ <=15)
	{
		Loc_ErrorStatus= Rcc_enuPllQError;
	}
	//check if the P value not from the following values: PLLP_2, PLLP_P4, LLP_6 and PLLP_8
	else if(Copy_u8PllP != PLLP_2 || Copy_u8PllP != PLLP_4 ||Copy_u8PllP != PLLP_6 || Copy_u8PllP != PLLP_8)
	{
		Loc_ErrorStatus =Rcc_enuPllPError;
	}
	//check if N value between 192 and 432
	else if(Copy_u16PllN >= 192 && Copy_u16PllN<= 432)
	{
		Loc_ErrorStatus = Rcc_enuPllNError;
	}
	//check that M value between 2 and 63
	else if(Copy_u8PllM >= 2 && Copy_u8PllM<= 63)
	{
		Loc_ErrorStatus =Rcc_enu_PllMError;

	}

	//if all parameters is valid set the values in pll configuration register
	else
	{
		RCC -> RCC_PLLCFGR= Copy_u8PllM | (Copy_u16PllN <<6) | (Copy_u8PllP<<16) | (Copy_u8Vco <<22) | (Copy_u8PllQ <<23);
	}
	return Loc_ErrorStatus;
}

Rcc_enuErrorStatus Rcc_InitHse_Src(u8 Copy_u8HseSrc)
{
  Rcc_enuErrorStatus Loc_ErrorStatus;
  if(Copy_u8HseSrc>1)
  {
    Loc_ErrorStatus=Rcc_enuHseSrcError;
  }
  else
  {
    if(Copy_u8HseSrc == HSE_NOTBYPASS)
    {
    	RCC -> RCC_CR &=~ HSEBYP;
      //CLR_BIT(RCC.RCC_CR ,HSBYP );
    }
    else
    {
    	RCC -> RCC_CR |= HSEBYP;
      //SET_BIT(RCC.RCC_CR , HSEBYP);
    }
    Loc_ErrorStatus = Rcc_enuOk;
  }
  return Loc_ErrorStatus;
}
Rcc_enuErrorStatus Rcc_enuAHBPrescaler(RCC_tenuAHB_Pre Copy_enuAHBPre)
{
	Rcc_enuErrorStatus Loc_ErrorStatus;
	//check if the passed value within the range
	if(Copy_enuAHBPre< AHB_Pre_0 || Copy_enuAHBPre> AHB_Pre_512)
	{
		// if it is out of the range return error
		Loc_ErrorStatus = Rcc_enuAHBPrescalerError;
	}
	else
	{
		Loc_ErrorStatus =Rcc_enuOk;
		switch(Copy_enuAHBPre)
		{
		case AHB_Pre_0:
			RCC->RCC_CFGR &= RCC_AHB_PRE0_MASK;
			break;
		case AHB_Pre_2:
			RCC ->RCC_CFGR |= RCC_AHB_PRE2_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE2_CLEAR_MASK;
			break;
		case AHB_Pre_4:
			RCC ->RCC_CFGR |= RCC_AHB_PRE4_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE4_CLEAR_MASK;
			break;
		case AHB_Pre_8:
			RCC ->RCC_CFGR |= RCC_AHB_PRE8_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE8_CLEAR_MASK;
			break;
		case AHB_Pre_16:
			RCC ->RCC_CFGR |= RCC_AHB_PRE16_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE16_CLEAR_MASK;
			break;
		case AHB_Pre_64:
			RCC ->RCC_CFGR |= RCC_AHB_PRE64_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE64_CLEAR_MASK;
			break;
		case AHB_Pre_128:
			RCC ->RCC_CFGR |= RCC_AHB_PRE128_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE128_CLEAR_MASK;
			break;
		case AHB_Pre_256:
			RCC ->RCC_CFGR |= RCC_AHB_PRE256_SET_MASK;
			RCC ->RCC_CFGR &= RCC_AHB_PRE256_CLEAR_MASK;
			break;
		case AHB_Pre_512:
			RCC ->RCC_CFGR |= RCC_AHB_PRE512_SET_MASK;
			break;
		}
	}
	return Loc_ErrorStatus;

}
Rcc_enuErrorStatus Rcc_enuEnableHse(void)
{
	Rcc_enuErrorStatus Loc_ErrorStatus= Rcc_enuEnableHseError;
	u8 timeOut = 50;
	u32 rdy = 0;
	// enable HSE
	RCC -> RCC_CR |=(1<<HSEON);
	//SET_BIT(RCC.RCC_CR ,HSEON );
	//wait until flag is 1
	while(timeOut && rdy)
	{
		timeOut--;
		volatile rdy = RCC -> RCC_CR & (1<<HSEON);
		Loc_ErrorStatus =Rcc_enuOk;
	}
	return Loc_ErrorStatus;
	/*
  //Clear HSE ready flag.
  SET_BIT(RCC.RCC_CIR, HSERDYC);
  //Select HSE as system clock.
  //where HSE --> 01
  SET_BIT(RCC.RCC_CFGR, SW0);
  CLEAR_BIT(RCC.RCC_CFGR, SW1);
	*/

}

Rcc_enuErrorStatus Rcc_enuEnableHsi(void)
{
	Rcc_enuErrorStatus Loc_ErrorStatus=Rcc_enuEnableHsiError;
	u8 timeout = 50;
	u32 rdy=0;
	//enable HSI
	RCC -> RCC_CR |= (1<<HSION);
	//check if the HSI flag is 1 until 50 iterations
	while(timeout && rdy)
		{
			timeout--;
			volatile rdy = RCC -> RCC_CR & (1<<HSION);
			Loc_ErrorStatus =Rcc_enuOk;
		}
	return Loc_ErrorStatus;
}

Rcc_enuErrorStatus Rcc_enuEnablePll(void)
{
	Rcc_enuErrorStatus Loc_ErrorStatus= Rcc_enuEnablePllError;
	u8 timeout = 50;
		u32 rdy=0;
		//enable PLL
		RCC -> RCC_CR |= (1<<PLLON);
		//check if the PLL flag is 1 until 50 iterations
		while(timeout && rdy)
			{
				timeout--;
				volatile rdy = RCC -> RCC_CR & (1<<PLLON);
				Loc_ErrorStatus =Rcc_enuOk;
			}
		return Loc_ErrorStatus;

}


//enable peris:

Rcc_enuErrorStatus Rcc_enuEnablePeri(u32 Copy_u32SelectedPeri ,u8 Copy_u8State_ON_OFF )
{
	Rcc_enuErrorStatus Loc_ErrorStatus= Rcc_enuOk;
	u32 Loc_u32Temp;
	Loc_u32Temp = Copy_u32SelectedPeri;
	// clear the bits of selection
	Copy_u32SelectedPeri &= CLEAR_SELECTION_BITS;
	//get the 2 bits of selection from register
	Loc_u32Temp &= CHECK_PERI_MASK;
	if(Copy_u8State_ON_OFF == RCC_PERIPHERAL_ON)
	{
		switch(Loc_u32Temp)
		{
		case AHB1_MASK:
			RCC->RCC_AHB1ENR |= Copy_u32SelectedPeri;
			break;
		case AHB2_MASK:
			RCC->RCC_AHB2ENR |= Copy_u32SelectedPeri;
			break;
		case APB1_MASK:
			RCC->RCC_APB1ENR |= Copy_u32SelectedPeri;
			break;
		case APB2_MASK:
			RCC->RCC_APB2ENR |= Copy_u32SelectedPeri;
			break;
		default:
			Loc_ErrorStatus =Rcc_enuPeriNumError;
			break;
		}
	}
		else if(Copy_u8State_ON_OFF == RCC_PERIPHERAL_OFF)
		{
			switch(Loc_u32Temp)
				{
				case AHB1_MASK:
					RCC->RCC_AHB1ENR &=~ Copy_u32SelectedPeri;
					break;
				case AHB2_MASK:
					RCC->RCC_AHB2ENR &=~ Copy_u32SelectedPeri;
					break;
				case APB1_MASK:
					RCC->RCC_APB1ENR &=~ Copy_u32SelectedPeri;
					break;
				case APB2_MASK:
					RCC->RCC_APB2ENR &=~ Copy_u32SelectedPeri;
					break;
				default:
					Loc_ErrorStatus =Rcc_enuPeriNumError;
					break;
				}
		}
		else
		{
			Loc_ErrorStatus = Rcc_enuPeriStateError;
		}

	return Loc_ErrorStatus;
}

Rcc_enuErrorStatus Rcc_enuGetSysClk(u8* Add_pu8SelectedSysClk)
{
	u32 Loc_u32TempVar;
	Rcc_enuErrorStatus Loc_enuErrorStatus= Rcc_enuOk;
	// check the pointer (not NULL)
	if(Add_pu8SelectedSysClk == '\0')
	{
		Loc_enuErrorStatus = Rcc_enuNullPointerError;
	}
	else
	{
		Loc_u32TempVar = (RCC->RCC_CFGR >>2);
		switch(Loc_u32TempVar)
		{
		case RCC_SYSCLK_HSI:
			Add_pu8SelectedSysClk = (u8)RCC_SYSCLK_HSI;
			break;
		case RCC_SYSCLK_HSE:
			Add_pu8SelectedSysClk = (u8)RCC_SYSCLK_HSE;
			break;
		case RCC_SYSCLK_PLL:
			Add_pu8SelectedSysClk = (u8)RCC_SYSCLK_PLL;
			break;
		default:
			Loc_enuErrorStatus = Rcc_enuSysClkSrcError;
			break;
		}
	}

	return Loc_enuErrorStatus;
}
