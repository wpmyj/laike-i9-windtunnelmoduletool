/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "maindef.h"
#include "apiLib.h"


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
//void SVC_Handler(void)
//{
//}
 
void DebugMon_Handler(void)
{
}
 
//void PendSV_Handler(void)
//{
//}
 
//void SysTick_Handler(void)
//{
//}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
// void EXTI9_5_IRQHandler(void)
// {
// 	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
// 	{
// 		if(mMaininf.mWork.mWorkGuideReceiveFlag == 1)
// 		{
// 			if(mMaininf.mWork.mWorkGuideFirstReceiveFlag == 0)
// 			{
// 				mMaininf.mSystem.mGuideReceiveTime = api_GetCurrentSystemTime();
// 				mMaininf.mWork.mWorkGuideFirstReceiveFlag = 1;
// 			}
// 			else
// 			{
// 				if((api_GetSystemTimePeriod(mMaininf.mSystem.mGuideReceiveTime) >= 8) && 
// 				   (api_GetSystemTimePeriod(mMaininf.mSystem.mGuideReceiveTime) <= 12))
// 				{
// 					mMaininf.mWork.mWorkGuideReceiveSuccessFlag = 1;
// 				}
// 				
// 				mMaininf.mSystem.mGuideReceiveTime = api_GetCurrentSystemTime();
// 			}
// 		}

// 		/* Clear the  EXTI line 9 pending bit */
// 		EXTI_ClearITPendingBit(EXTI_Line9);
// 	}
// 	
// 	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
// 	{
// 		if(mMaininf.mWork.mWorkGuideReceiveFlag == 2)
// 		{
// 			if(mMaininf.mWork.mWorkGuideFirstReceiveFlag == 0)
// 			{
// 				mMaininf.mSystem.mGuideReceiveTime = api_GetCurrentSystemTime();
// 				mMaininf.mWork.mWorkGuideFirstReceiveFlag = 1;
// 			}
// 			else
// 			{
// 				if((api_GetSystemTimePeriod(mMaininf.mSystem.mGuideReceiveTime) >= 8) && 
// 				   (api_GetSystemTimePeriod(mMaininf.mSystem.mGuideReceiveTime) <= 12))
// 				{
// 					mMaininf.mWork.mWorkGuideReceiveSuccessFlag = 1;
// 				}
// 				
// 				mMaininf.mSystem.mGuideReceiveTime = api_GetCurrentSystemTime();
// 			}
// 		}

// 		/* Clear the  EXTI line 8 pending bit */
// 		EXTI_ClearITPendingBit(EXTI_Line8);
// 	}
// }

void TIM2_IRQHandler(void)        //1ms interrupt
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		/*        用于生成1ms滴答定时器          */
		mMaininf.mSystem.mSystemTick ++;
		if(mMaininf.mSystem.mSystemTick >= SYSTEMTIMEMAX) mMaininf.mSystem.mSystemTick = 0;
		
 		//引导发射
		if(mMaininf.mWork.mWorkGuideSendFlag == 1)
		{
			mMaininf.mWork.mWorkGuideSendCont ++;
			
			if(mMaininf.mWork.mWorkGuideSendCont == 1)
			{
				TIM_SetCompare1(TIM1,13);
			}
			else if(mMaininf.mWork.mWorkGuideSendCont >= 2)
			{
				TIM_SetCompare1(TIM1,0);
				mMaininf.mWork.mWorkGuideSendCont = 0;
			}
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void TIM3_IRQHandler(void)        //200us interrupt
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		mMaininf.mSystem.mSystem200usTick ++;
		if(mMaininf.mSystem.mSystem200usTick >= SYSTEMTIMEMAX) mMaininf.mSystem.mSystem200usTick = 0;
		

		
	}
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

void TIM4_IRQHandler(void)        //10us interrupt
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{

	}
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}

void TIM5_IRQHandler(void)        //250us interrupt
{
	float temp;
	
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET)
	{
		mMaininf.mWork.mWorkSensorSendStep ++;
		
		switch(mMaininf.mWork.mWorkSensorSendStep)
		{
			case 1:
				if(mMaininf.mWork.mWorkSensorSendAlongSideFlag == 1)
				{
					PAout(1) = 1;
				}
				if(mMaininf.mWork.mWorkSensorSendAvoidBumpFlag == 1)
				{
					PAout(7) = 1;
				}
				break;
			case 2:
				break;
			case 3:
				if(mMaininf.mWork.mWorkSensorAvoidBumpCont >= 4)
				{
					mMaininf.mWork.mWorkSensorAvoidBumpCont = 0;
				}
				mMaininf.mWork.mWorkSensorOnAvl[0][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[1];//左沿边   远
				mMaininf.mWork.mWorkSensorOnAvl[1][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[0];//右沿边   远
				mMaininf.mWork.mWorkSensorOnAvl[2][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[2];//左免碰撞接收
				mMaininf.mWork.mWorkSensorOnAvl[3][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[3];//右免碰撞接收
				mMaininf.mWork.mWorkSensorOnAvl[4][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[4];//前免碰撞接收
				
				mMaininf.mWork.mWorkSensorOnOffAverage[0][0] = mMaininf.mWork.mWorkSensorOnAvl[0][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[0][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[0][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[0][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[1][0] = mMaininf.mWork.mWorkSensorOnAvl[1][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[1][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[1][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[1][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[2][0] = mMaininf.mWork.mWorkSensorOnAvl[2][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[2][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[2][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[2][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[3][0] = mMaininf.mWork.mWorkSensorOnAvl[3][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[3][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[3][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[3][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[4][0] = mMaininf.mWork.mWorkSensorOnAvl[4][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[4][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[4][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[4][3];
																
				
				PAout(7) = 0;
				PAout(1) = 0;
				if(mMaininf.mWork.mWorkSensorSendAlongSideFlag == 1)
				{
					PAout(0) = 1;
				}
				
				mMaininf.mWork.mWorkSensorAvoidBumpCont ++;
				break;
			case 4:
				break;
			case 5:
				mMaininf.mWork.mWorkSensorOnAvl[6][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[1];//左沿边   近
				mMaininf.mWork.mWorkSensorOnAvl[7][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[0];//右沿边   近
				
				mMaininf.mWork.mWorkSensorOnOffAverage[6][0] = mMaininf.mWork.mWorkSensorOnAvl[6][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[6][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[6][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[6][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[7][0] = mMaininf.mWork.mWorkSensorOnAvl[7][0] + 
																mMaininf.mWork.mWorkSensorOnAvl[7][1] + 
																mMaininf.mWork.mWorkSensorOnAvl[7][2] + 
																mMaininf.mWork.mWorkSensorOnAvl[7][3];
				PAout(0) = 0;
				break;
			case 6:
				break;
			case 7:
				mMaininf.mWork.mWorkSensorOffAvl[2][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[2];//左免碰撞接收
				mMaininf.mWork.mWorkSensorOffAvl[3][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[3];//右免碰撞接收
				mMaininf.mWork.mWorkSensorOffAvl[4][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[4];//前免碰撞接收
				
				mMaininf.mWork.mWorkSensorOnOffAverage[2][1] = mMaininf.mWork.mWorkSensorOffAvl[2][0] + 
																mMaininf.mWork.mWorkSensorOffAvl[2][1] + 
																mMaininf.mWork.mWorkSensorOffAvl[2][2] + 
																mMaininf.mWork.mWorkSensorOffAvl[2][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[3][1] = mMaininf.mWork.mWorkSensorOffAvl[3][0] + 
																mMaininf.mWork.mWorkSensorOffAvl[3][1] + 
																mMaininf.mWork.mWorkSensorOffAvl[3][2] + 
																mMaininf.mWork.mWorkSensorOffAvl[3][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[4][1] = mMaininf.mWork.mWorkSensorOffAvl[4][0] + 
																mMaininf.mWork.mWorkSensorOffAvl[4][1] + 
																mMaininf.mWork.mWorkSensorOffAvl[4][2] + 
																mMaininf.mWork.mWorkSensorOffAvl[4][3];
				break;
			case 8:
				mMaininf.mWork.mWorkSensorOffAvl[0][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[1];//左沿边   远
				mMaininf.mWork.mWorkSensorOffAvl[1][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[0];//右沿边   远
// 				mMaininf.mWork.mWorkSensorOffAvl[6][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[1];//左沿边   近
// 				mMaininf.mWork.mWorkSensorOffAvl[7][mMaininf.mWork.mWorkSensorAvoidBumpCont] = ADCValue[0];//右沿边   近
			
				mMaininf.mWork.mWorkSensorOnOffAverage[0][1] = mMaininf.mWork.mWorkSensorOffAvl[0][0] + 
																mMaininf.mWork.mWorkSensorOffAvl[0][1] + 
																mMaininf.mWork.mWorkSensorOffAvl[0][2] + 
																mMaininf.mWork.mWorkSensorOffAvl[0][3];
				mMaininf.mWork.mWorkSensorOnOffAverage[1][1] = mMaininf.mWork.mWorkSensorOffAvl[1][0] + 
																mMaininf.mWork.mWorkSensorOffAvl[1][1] + 
																mMaininf.mWork.mWorkSensorOffAvl[1][2] + 
																mMaininf.mWork.mWorkSensorOffAvl[1][3];
// 				mMaininf.mWork.mWorkSensorOnOffAverage[6][1] = mMaininf.mWork.mWorkSensorOffAvl[6][0] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[6][1] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[6][2] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[6][3];
// 				mMaininf.mWork.mWorkSensorOnOffAverage[7][1] = mMaininf.mWork.mWorkSensorOffAvl[7][0] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[7][1] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[7][2] + 
// 																mMaininf.mWork.mWorkSensorOffAvl[7][3];
																
				mMaininf.mWork.mWorkSensorDataAvl[2] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[2][1] - mMaininf.mWork.mWorkSensorOnOffAverage[2][0]);
				mMaininf.mWork.mWorkSensorDataAvl[3] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[3][1] - mMaininf.mWork.mWorkSensorOnOffAverage[3][0]);
				mMaininf.mWork.mWorkSensorDataAvl[4] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[4][1] - mMaininf.mWork.mWorkSensorOnOffAverage[4][0]);
				
				mMaininf.mWork.mWorkSensorDataAvl[0] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[0][1] - mMaininf.mWork.mWorkSensorOnOffAverage[0][0]);
				mMaininf.mWork.mWorkSensorDataAvl[1] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[1][1] - mMaininf.mWork.mWorkSensorOnOffAverage[1][0]);
				mMaininf.mWork.mWorkSensorDataAvl[6] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[6][1] - mMaininf.mWork.mWorkSensorOnOffAverage[0][0])/4;
				mMaininf.mWork.mWorkSensorDataAvl[7] = abs(mMaininf.mWork.mWorkSensorOnOffAverage[7][1] - mMaininf.mWork.mWorkSensorOnOffAverage[1][0])/4;
				
				temp = (float)mMaininf.mWork.mWorkSensorDataAvl[0] / mMaininf.mWork.mWorkSensorDataAvl[6];
				mMaininf.mWork.mWorkSensorDataAvl[8] = (u16)(temp * 100);
				temp = (float)mMaininf.mWork.mWorkSensorDataAvl[1] / mMaininf.mWork.mWorkSensorDataAvl[7];
				mMaininf.mWork.mWorkSensorDataAvl[9] = (u16)(temp * 100);
				
				mMaininf.mWork.mWorkSensorSendStep = 0;
				break;
			default :
				break;
		}
	}
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
}

// void USART1_IRQHandler(void)
// {
// 	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)     /*   接收数据   */
// 	{
// 		api_UART1_ReceiveData(USART_ReceiveData(USART1));
// 		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
// 	}
// 	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)      /*   发送数据   */
// 	{
// 		if(mMaininf.mUart1.mSendSize > 0)
// 		{
// 			USART_SendData(USART1,mMaininf.mUart1.TxBuffer[mMaininf.mUart1.mSendCont ++]);
// 			if(mMaininf.mUart1.mSendCont == mMaininf.mUart1.mSendSize)
// 			{
// 				mMaininf.mUart1.mSendSize = 0;
// 				mMaininf.mUart1.mSendCont = 0;
// 				USART_ITConfig(USART1,USART_IT_TC,DISABLE);
// 				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
// 			}
// 		}
// 		else
// 		{
// 			mMaininf.mUart1.mSendSize = 0;
// 			mMaininf.mUart1.mSendCont = 0;
// 			USART_ITConfig(USART1,USART_IT_TC,DISABLE);
// 			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
// 		}
// 		USART_ClearITPendingBit(USART1,USART_IT_TC);
// 	}
// }

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		api_UART1_ReceiveData(USART_ReceiveData(USART1));
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		if(mMaininf.mUart1.mSendSize > 0)
		{
			USART_SendData(USART1,mMaininf.mUart1.TxBuffer[mMaininf.mUart1.mSendCont ++]);
			if(mMaininf.mUart1.mSendCont == mMaininf.mUart1.mSendSize)
			{
				mMaininf.mUart1.mSendSize = 0;
				mMaininf.mUart1.mSendCont = 0;
				USART_ITConfig(USART1,USART_IT_TC,DISABLE);
				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
			}
		}
		else
		{
			mMaininf.mUart1.mSendSize = 0;
			mMaininf.mUart1.mSendCont = 0;
			USART_ITConfig(USART1,USART_IT_TC,DISABLE);
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		}
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		api_UART2_ReceiveData(USART_ReceiveData(USART2));
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART2,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		if(mMaininf.mUart2.mSendSize > 0)
		{
			USART_SendData(USART2,mMaininf.mUart2.TxBuffer[mMaininf.mUart2.mSendCont ++]);
			if(mMaininf.mUart2.mSendCont == mMaininf.mUart2.mSendSize)
			{
				mMaininf.mUart2.mSendSize = 0;
				mMaininf.mUart2.mSendCont = 0;
				USART_ITConfig(USART2,USART_IT_TC,DISABLE);
				USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
			}
		}
		else
		{
			mMaininf.mUart2.mSendSize = 0;
			mMaininf.mUart2.mSendCont = 0;
			USART_ITConfig(USART2,USART_IT_TC,DISABLE);
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
		USART_ClearITPendingBit(USART2,USART_IT_TC);
	}
}

// void USART3_IRQHandler(void)
// {
// 	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)     /*   接收数据   */
// 	{
// 		//mMaininf.mWork.mWorkBigUartFlag = 1;
// 		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
// 	}
// 	if(USART_GetITStatus(USART3,USART_IT_TC)!=RESET)      /*   发送数据   */
// 	{
// 		USART_ClearITPendingBit(USART1,USART_IT_TC);
// 	}
// }

// void UART4_IRQHandler(void)
// {
// 	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)     /*   接收数据   */
// 	{
// 		api_UART4_ReceiveData(USART_ReceiveData(UART4));
// 		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
// 	}
// 	if(USART_GetITStatus(UART4,USART_IT_TC)!=RESET)      /*   发送数据   */
// 	{
// 		if(mMaininf.mUart4.mSendSize > 0)
// 		{
// 			USART_SendData(UART4,mMaininf.mUart4.TxBuffer[mMaininf.mUart4.mSendCont ++]);
// 			if(mMaininf.mUart4.mSendCont == mMaininf.mUart4.mSendSize)
// 			{
// 				mMaininf.mUart4.mSendSize = 0;
// 				mMaininf.mUart4.mSendCont = 0;
// 				USART_ITConfig(UART4,USART_IT_TC,DISABLE);
// 				USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
// 			}
// 		}
// 		else
// 		{
// 			mMaininf.mUart4.mSendSize = 0;
// 			mMaininf.mUart4.mSendCont = 0;
// 			USART_ITConfig(UART4,USART_IT_TC,DISABLE);
// 			USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
// 		}
// 		USART_ClearITPendingBit(UART4,USART_IT_TC);
// 	}
// }

// void UART5_IRQHandler(void)
// {
// 	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)     /*   接收数据   */
// 	{
// 		api_UART5_ReceiveData(USART_ReceiveData(UART5));
// 		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
// 	}
// 	if(USART_GetITStatus(UART5,USART_IT_TC)!=RESET)      /*   发送数据   */
// 	{
// 		if(mMaininf.mUart5.mSendSize > 0)
// 		{
// 			USART_SendData(UART5,mMaininf.mUart5.TxBuffer[mMaininf.mUart5.mSendCont ++]);
// 			if(mMaininf.mUart5.mSendCont == mMaininf.mUart5.mSendSize)
// 			{
// 				mMaininf.mUart5.mSendSize = 0;
// 				mMaininf.mUart5.mSendCont = 0;
// 				USART_ITConfig(UART5,USART_IT_TC,DISABLE);
// 				USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
// 			}
// 		}
// 		else
// 		{
// 			mMaininf.mUart5.mSendSize = 0;
// 			mMaininf.mUart5.mSendCont = 0;
// 			USART_ITConfig(UART5,USART_IT_TC,DISABLE);
// 			USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
// 		}
// 		USART_ClearITPendingBit(UART5,USART_IT_TC);
// 	}
// }

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
