/****************************************************************************************************/
/*			@FileName		:	TK_TIMERCONTROLLER.h																											   	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__TK_TIMERCONTROLLER_H__
#define	__TK_TIMERCONTROLLER_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif



	
void TK_TimerController( void *pvParameters );
void TimerDetection(void);

	
	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__TK_TIMERCONTROLLER_H__*/	

