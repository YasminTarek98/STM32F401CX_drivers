/*
 * Systick_cfg.h
 *
 *  Created on: May 4, 2022
 *      Author: hp
 */

#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_

/*
 * add the your system frequency source
 */
#define SYSTICK_SYS_CLK_FREQUENCY		16000000
/*
 * choose from the following:
 * SYSTICK_CLK_SOURCE_AHB
 * SYSTICK_CLK_SOURCE_AHB_DIV_8
 */
# define SYSTICK_CLK_SOURCE		SYSTICK_CLK_SOURCE_AHB

/*
 * choose from the following:
 * SYSTICK_DISABLE_EXEPTION
 * SYSTICK_ENABLE_EXEPTION
 */
#define SYSTICK_EXEPTION		SYSTICK_DISABLE_EXEPTION

/*
 * choose from the following:
 * SYSTICK_u8MULTI_SHOT_MODE
 * SYSTICK_u8SINGLE_SHOT_MODE
 */
#define SYSTICK_MODE			SYSTICK_u8MULTI_SHOT_MODE
#endif /* SYSTICK_CFG_H_ */
