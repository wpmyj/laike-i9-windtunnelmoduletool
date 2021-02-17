/****************************************************************************************************/
/*			@FileName		:	BSP.h																																		    	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__BSP_H__
#define	__BSP_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

	
/*-----------------------------------------------------------------------*/
/*    中断优先级                                                         */
/*-----------------------------------------------------------------------*/
	
#define TIM2_TIME_PRIORITY                        2     //定时器2
#define TIM3_TIME_PRIORITY                        7     //定时器3
#define TIM4_TIME_PRIORITY                        8     //定时器4
#define TIM5_TIME_PRIORITY                        3     //定时器5
#define UART1_MAINBOARD_PRIORITY                  4     //主板UART1
#define UART3_BIGBOARD_PRIORITY                   6     //大核UART3
#define UART4_DEBUG_PRIORITY                      9     //调试UART4
#define UART5_DISPLAY_PRIORITY                    5     //显示UART5
//#define WIFI_UART_DMA_PRIORITY                    6
	
	
/*-----------------------------------------------------------------------*/
/*    端口定义                                                           */
/*-----------------------------------------------------------------------*/

/* UART configuration ----------------------------------------------*/
	
// #define MAINBOARD_UART_GPIO                GPIOA               //      uart1
// #define MAINBOARD_UART_TX_PIN         	   GPIO_Pin_9
// #define MAINBOARD_UART_RX_PIN              GPIO_Pin_10


// #define DISPLAY_UART_GPIO             	   GPIOA               //      uart2
// #define DISPLAY_UART_TX_PIN                GPIO_Pin_2
// #define DISPLAY_UART_RX_PIN                GPIO_Pin_3	
	
	
	
	
	
	
static volatile ErrorStatus HSEStartUpStatus = SUCCESS;	

void prvSetupHardware(void);
void TIM1_PWM_Configure(u16 arr,u16 pre);
void TIM5_PWM_Configure(u16 arr,u16 pre);


	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__BSP_H__*/	

