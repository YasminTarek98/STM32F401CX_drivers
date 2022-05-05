/*
 * Rcc.h
 *
 *  Created on: Mar 11, 2022
 *      Author: Yasmin Tarek
 */

#ifndef RCC_H_
#define RCC_H_


typedef enum{
  Rcc_enuOk,
  Rcc_enuSysClkSrcError,
  Rcc_enuHseSrcError,
  Rcc_enuPllVcoError,
  Rcc_enuPllQError,
  Rcc_enuPllPError,
  Rcc_enuPllNError,
  Rcc_enu_PllMError,
  Rcc_enuEnableHseError,
  Rcc_enuEnableHsiError,
  Rcc_enuEnablePllError,
  Rcc_enuAHBPrescalerError,
  Rcc_enuPeriStateError,
  Rcc_enuPeriNumError,
  Rcc_enuNullPointerError

}Rcc_enuErrorStatus;

typedef enum
{
	AHB_Pre_0,
	AHB_Pre_2,
	AHB_Pre_4,
	AHB_Pre_8,
	AHB_Pre_16,
	AHB_Pre_64,
	AHB_Pre_128,
	AHB_Pre_256,
	AHB_Pre_512,
}RCC_tenuAHB_Pre;


//Pins of RCC_CR
enum{
  HSION,
  HSIRDY,
  HSITRIM0 =3,
  HSITRIM1,
  HSITRIM2,
  HSITRIM3,
  HSITRIM4,
  HSICAL0,
  HSICAL1,
  HSICAL2,
  HSICAL3,
  HSICAL4,
  HSICAL5,
  HSICAL6,
  HSICAL7,
  HSEON,
  HSERDY,
  HSEBYP,
  CSSON,
  PLLON = 24,
  PLLRDY,
  PLLI2SON,
  PLLI2SRDY,
};

enum{
  PLLM0,
  PLLM1,
  PLLM2,
  PLLM3,
  PLLM4,
  PLLM5,
  PLLN0,
  PLLN1,
  PLLN2,
  PLLN3,
  PLLN4,
  PLLN5,
  PLLN6,
  PLLN7,
  PLLN8,
  PLLP0 = 16,
  PLLP1,
  PLLSRC = 22,
  PLLQ0 = 24,
  PLLQ1,
  PLLQ2,
  PLLQ3,

};
//RCC_CFGR
enum{
  SW0,
  SW1,
  SWS0,
  SWS1,
  HPRE0,
  HPRE1,
  HPRE2,
  HPRE3,
  PPRE10 = 10,
  PPRE11,
  PPRE12,
  PPRE20,
  PPRE21,
  PPRE22,
  RTCPRE0,
  RTCPRE1,
  RTCPRE2,
  RTCPRE3,
  RTCPRE4,
  //DON'T KNOW
  MCO10,
  MCO11,
  //DON'T KNOW
  I2SSCR,
  MCO1PRE0,
  MCO1PRE1,
  MCO1PRE2,
  MCO2PRE0,
  MCO2PRE1,
  MCO2PRE2,
  MCO20,
  MCO21,

};
enum{
  LSIRDYF,
  LSERDYF,
  HSIRDYF,
  HSERDYF,
  PLLRDYF,
  PLLI2SRDYF,
  CSSF = 7,
  LSIRDYIE,
  LSERDYIE,
  HSIRDYIE,
  HSERDYIE,
  PLLRDYIE,
  PLLI2SRDYIE,
  LSIRDYC =16,
  LSERDYC,
  HSIRDYC,
  HSERDYC,
  PLLRDYC,
  PLLI2SRDYC,
  CSSC = 23,

};

//AHB1ENR
enum{
	GPIOA_EN,
	GPIOB_EN,
	GPIOC_EN,
	GPIOD_EN,
	GPIOE_EN,
	GPIOH_EN = 7,
	CRC_EN = 12,
	DMA1_EN = 21,
	DMA2_EN,
};

//AHB2ENR
#define OTGFSEN 	7

//APB1ENR
enum{
	TIM2_EN,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	WWDG_EN = 11,
	SPI2_EN = 14,
	SPI3_EN,
	USART2_EN =17,
	I2C1_EN = 21,
	I2C2_EN,
	I2C3_EN,
	PWR_EN = 28
};

//APB2ENR
enum{
	TIM1_EN,
	USART1_EN =4,
	USART1_EN,
	ADC1_EN = 8,
	SDIO_EN = 11,
	SPI1_EN,
	SPI4_EN,
	SYSCFG_EN,
	TIM9_EN = 16,
	TIM10_EN,
	TIM11_EN,
};

//masks of peripherals AHB, APB
//hnsta5dem bit 31 &30 as selection
// AHB1 bus:
#define GPIOA_MASK					0x00000001
#define GPIOB_MASK					0x00000002
#define GPIOC_MASK					0x00000004
#define GPIOD_MASK					0x00000008
#define GPIOE_MASK					0x00000010
#define GPIOH_MASK					0x00000080
#define CRC_MASK					0x00001000
#define DMA1_MASK					0x00200000
#define DMA2_MASK					0x00400000

//AHB2 bus:
#define OTGFS_MASK					0x40000080

// APB1 bus:
#define TIMER2_MASK					0x80000001
#define TIMER3_MASK					0x80000002
#define TIMER4_MASK					0x80000004
#define TIMER5_MASK					0x80000008
#define WATCHDOG_MASK				0x80000800
#define SPI2_MASK					0x80004000
#define SPI3_MASK					0x80008000
#define USART2_MASK					0x80020000
#define I2C1_MASK					0x80200000
#define I2C2_MASK					0x80400000
#define I2C3_MASK					0x80800000
//bit on 28 bttkat3 m3 elarb3a bit elle bselect behoom
#define PWR_MASK 					0x90000000

//APB2 bus
#define TIMER1_MASK 				0xc0000001
#define USART1_MASK					0xC0000010
#define USART6_MASK					0xC0000020
#define ADC1_MASK					0xC0000100
#define SDIO_MASK					0xC0000800
#define SPI1_MASK					0xC0001000
#define SPI4_MASK					0xC0002000
#define SYSCFG_MASK					0xC0004000
#define TIMER9_MASK					0xC0010000
#define TIMER10_MASK				0xC0020000
#define TIMER11_MASK				0xC0040000


#define RCC_PERIPHERAL_ON		1
#define RCC_PERIPHERAL_OFF		0

#define RCC_SYSCLK_HSI 	((u32)0x00000000)
#define RCC_SYSCLK_HSE 	((u32)0x00000001)
#define RCC_SYSCLK_PLL 	((u32)0x00000002)

#define RCC_SW_MASK 	((u32)0x00000003)
//add ffff
#define	RCC_AHB_PRE0_MASK			((u32)0xffffff7f)
#define RCC_AHB_PRE2_SET_MASK		((u32)0x00000080)
#define RCC_AHB_PRE2_CLEAR_MASK		((u32)0xffffff8f)
#define RCC_AHB_PRE4_SET_MASK		((u32)0x00000090)
#define RCC_AHB_PRE4_CLEAR_MASK		((u32)0xffffff9f)
#define RCC_AHB_PRE8_SET_MASK		((u32)0x000000a0)
#define RCC_AHB_PRE8_CLEAR_MASK		((u32)0xffffffaf)
#define RCC_AHB_PRE16_SET_MASK		((u32)0x000000b0)
#define RCC_AHB_PRE16_CLEAR_MASK	((u32)0xffffffbf)
#define RCC_AHB_PRE64_SET_MASK		((u32)0x000000c0)
#define RCC_AHB_PRE64_CLEAR_MASK	((u32)0xffffffcf)
#define RCC_AHB_PRE128_SET_MASK		((u32)0x000000d0)
#define RCC_AHB_PRE128_CLEAR_MASK	((u32)0xffffffdf)
#define RCC_AHB_PRE256_SET_MASK		((u32)0x000000e0)
#define RCC_AHB_PRE256_CLEAR_MASK	((u32)0xffffffef)
#define RCC_AHB_PRE512_SET_MASK		((u32)0x000000f0)


// PLLQ with 2 ≤PLLQ ≤15
#define MIN_PLLQ_VAL	2
#define MAX_PLLQ_VAL	15

#define PLLP_2			0b00
#define PLLP_4			0b01
#define PLLP_6			0b10
#define PLLP_8			0b11


#define PLL_SRC_MASK 	1

#define HSE_NOTBYPASS 	0
#define HSE_EXTCLK		1

/*************************************************************************************************/
/*************************************functions prototype*****************************************/


 /*************************************************************************************************
 * I/P Arguments: u8 Copy_u8SysClk : choose the SysClk source:
 * 									 SYSCLK_HSE
 * 									 SYSCLK_HSI
 * 									 SYSCLK_PLLCLK
 * Return value	: Rcc_enuErrorStatus: refer to the type of error
 * description: This function is used to select the sysclk used.
 **************************************************************************************************/
Rcc_enuErrorStatus Rcc_enuSelectSysClk(u32 Copy_u8SysClk);
/**************************************************************************************************
* I/P Arguments:1) u8 Copy_u8Vco 	: choose the PLL source:
* 										0-->
* 										1-->
* 				2) u8 Copy_u8PllQ	: q with value between 2 and 15
* 				3) u8 Copy_u8PllP	: choose PLLP value:
* 										00-->PLLP_2
* 										01-->PLLP_4
* 										10-->PLLP_6
* 										11-->PLLP_8
* 				4) u16 Copy_u16PllN	: N with value between 192 and 432
* 				5) u8 Copy_u8PllM	: M is value between 2 and 63
* Return value	: Rcc_enuErrorStatus: refer to the type of error
* description: This function is used to .
**************************************************************************************************/
Rcc_enuErrorStatus Rcc_enuPllConfig(u32 Copy_u8Vco, u8 Copy_u8PllQ , u8 Copy_u8PllP , u16 Copy_u16PllN ,u8 Copy_u8PllM );

/*************************************************************************************************
 * I/P Arguments: void
 * Return value	: Rcc_enuErrorStatus: refer to the type of error
 *
 * description: This function is used to enable HSE and check that enabling is done.
 **************************************************************************************************/
Rcc_enuErrorStatus Rcc_enuEnableHse(void);
/*************************************************************************************************
* I/P Arguments: u8 Copy_u8HseSrc : choose the HSE source:
* 									 1) HSE oscillator not bypassed:					 HSE_NOTBYPASS
* 									 2)  HSE oscillator bypassed with an external clock: HSE_EXTCLK
* Return value	: Rcc_enuErrorStatus: refer to the type of error
* description: This function is used to select the sysclk used.
* * Notice: this feature can be enabled only if the HSE oscillator is disabled.
**************************************************************************************************/
Rcc_enuErrorStatus Rcc_InitHse_Src(u8 Copy_u8HseSrc);
/*************************************************************************************************
 * I/P Arguments: void
 * Return value	: Rcc_enuErrorStatus: refer to the type of error
 *					if ok: 	   Rcc_enuOk
 *					if not ok: Rcc_enuEnableHsiError
 * description: This function is used to enable HSI and check that enabling is done.
 **************************************************************************************************/
Rcc_enuErrorStatus Rcc_enuEnableHsi(void);


Rcc_enuErrorStatus Rcc_enuAHBPrescaler(RCC_tenuAHB_Pre Copy_enuAHBPre);
/*************************************************************************************************
 * function: Rcc_enuEnablePll
 * I/P Arguments: void
 * Return value	: Rcc_enuErrorStatus: refer to the type of error
 *					if ok: 	   Rcc_enuOk
 *					if not ok: Rcc_enuEnablePllError
 * description: This function is used to enable Pll and check that enabling is done.
 **************************************************************************************************/
Rcc_enuErrorStatus Rcc_enuEnablePll(void);

Rcc_enuErrorStatus Rcc_enuGetSysClk(u8* Add_pu8SelectedSysClk);

Rcc_enuErrorStatus Rcc_enuEnablePeri(u32 Copy_u32SelectedPeri ,u8 Copy_u8State_ON_OFF );
#endif /* RCC_H_ */
