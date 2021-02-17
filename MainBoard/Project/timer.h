/****************************************************************************************************/
/*			@FileName		:	TIMER.h																																		   	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__TIMER_H__
#define	__TIMER_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif


void SysTick_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__BSP_H__*/	


