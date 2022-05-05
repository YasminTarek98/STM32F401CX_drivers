/*
 * GPIO.h
 *
 *  Created on: Mar 26, 2022
 *      Author: Yasmin Tarek
 */

#ifndef GPIO_H_
#define GPIO_H_
// enum to return error
typedef enum{
	GPIO_enuOk,
	GPIO_enuNOK,

}GPIO_enutErrorStatus;


typedef struct{
	u32 port;
	u16 pin;
	u32 mode;
	u32 speed;
	u8 AF_Num;
}GPIO_Init_Config;

#define GPIO_PINVALUE_LOW		0
#define GPIO_PINVALUE_HIGH		1

#define GPIOA_BASE_ADDRESS 0x4002 0000
#define GPIOB_BASE_ADDRESS 0x4002 0400
#define GPIOC_BASE_ADDRESS 0x4002 0800
#define GPIOD_BASE_ADDRESS 0x4002 0C00
#define GPIOE_BASE_ADDRESS 0x4002 1000
#define GPIOH_BASE_ADDRESS 0x4002 1C00

#define GPIOA ((volatile void*)(GPIOA_BASE_ADDRESS))
#define GPIOB ((volatile void*)(GPIOB_BASE_ADDRESS))
#define GPIOC ((volatile void*)(GPIOC_BASE_ADDRESS))
#define GPIOD ((volatile void*)(GPIOD_BASE_ADDRESS))
#define GPIOE ((volatile void*)(GPIOE_BASE_ADDRESS))
#define GPIOH ((volatile void*)(GPIOH_BASE_ADDRESS))


#define GPIO_u16PIN_00		((u16)0x0001)
#define GPIO_u16PIN_01		((u16)0x0002)
#define GPIO_u16PIN_02		((u16)0x0004)
#define GPIO_u16PIN_03		((u16)0x0008)
#define GPIO_u16PIN_04		((u16)0x0010)
#define GPIO_u16PIN_05		((u16)0x0020)
#define GPIO_u16PIN_06		((u16)0x0040)
#define GPIO_u16PIN_07		((u16)0x0080)
#define GPIO_u16PIN_08		((u16)0x0100)
#define GPIO_u16PIN_09		((u16)0x0200)
#define GPIO_u16PIN_10		((u16)0x0400)
#define GPIO_u16PIN_11		((u16)0x0800)
#define GPIO_u16PIN_12		((u16)0x1000)
#define GPIO_u16PIN_13		((u16)0x2000)
#define GPIO_u16PIN_14		((u16)0x4000)
#define GPIO_u16PIN_15		((u16)0x8000)

#define GPIO_AF_NUM_0								0b00000000
#define GPIO_AF_NUM_1								0b00000001
#define GPIO_AF_NUM_2								0b00000010
#define GPIO_AF_NUM_3								0b00000011
#define GPIO_AF_NUM_4								0b00000100
#define GPIO_AF_NUM_5								0b00000101
#define GPIO_AF_NUM_6								0b00000110
#define GPIO_AF_NUM_7								0b00000111
#define GPIO_AF_NUM_8								0b00001000
#define GPIO_AF_NUM_9								0b00001001
#define GPIO_AF_NUM_10								0b00001010
#define GPIO_AF_NUM_11								0b00001011
#define GPIO_AF_NUM_12								0b00001100
#define GPIO_AF_NUM_13								0b00001101
#define GPIO_AF_NUM_14								0b00001110
#define GPIO_AF_NUM_15								0b00001111

#define GPIO_PIN_0								    0
#define GPIO_PIN_1								    1
#define GPIO_PIN_2								    2
#define GPIO_PIN_3								    3
#define GPIO_PIN_4								    4
#define GPIO_PIN_5								    5
#define GPIO_PIN_6								    6
#define GPIO_PIN_7								    7
#define GPIO_PIN_8								    8
#define GPIO_PIN_9								    9
#define GPIO_PIN_10								    10
#define GPIO_PIN_11								    11
#define GPIO_PIN_12								    12
#define GPIO_PIN_13								    13
#define GPIO_PIN_14								    14
#define GPIO_PIN_15								    15
// functions prototype \\

GPIO_enutErrorStatus GPIO_enuInit(GPIO_Init_Config *Add_strGPIO_Config);
GPIO_enutErrorStatus GPIO_enuGetPinValue(GPIO_Init_Config *Add_strGPIO_Config , u8* Add_pu8Value);
GPIO_enutErrorStatus GPIO_enuSetPinValue(GPIO_Init_Config *Add_strGPIO_Config , u8 Copy_u8Value);
//GPIO_enutErrorStatus GPIO_enuSetPinMode(u32 port , u16 pin , u8 value);

#endif /* GPIO_H_ */
