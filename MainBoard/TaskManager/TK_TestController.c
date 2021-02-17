/****************************************************************************************************/
/*			@FileName		:	TK_TestController.c												  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
#include "bsp.h"
#include "apiLib.h"
#include "TK_TestController.h"


/* Variable --------------------------------------------------------------------*/
/* Function --------------------------------------------------------------------*/
void TK_TestController( void *pvParameters );
void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status);
u8 api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime,u8 type,u8 num);
u8 iiiiiiiii;


/*****************************************************************************
 * @name       :void TK_TestController( void *pvParameters )
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :时间控制任务
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TK_TestController( void *pvParameters )
{
	//api_MachinePowerOn();
	for(;;)
	{
		IWDG_ReloadCounter();
				
		//api_Led_Status_Set(0,1);
		//api_Led_Status_Set(1,1);
		//api_Control_Motor(0,1);
// 		api_Control_Motor(1,1);
		
		if(mMaininf.mUart1.mReceiveFlag == 1)   //调试
		{
			mMaininf.mUart1.mReceiveFlag = 0;
			api_UART2_Display_SendCMDData(2,1,1);
 			vTaskDelay(1000);
			mMaininf.mWork.mWorkChecking = 1;
			PAout(12) = 1;
			PAout(15) = 1;
			PEout(1) = 0;
			vTaskDelay(10000);
			api_SendCMD_To_MainBoard(0,1,1,100,1,5);
			mMaininf.mWork.mWorkStep = mMaininf.mUart1.ReceiveBuf[2];
		}
		
		if(mMaininf.mWork.mWorkKeyPressFlag == 1)
		{
			mMaininf.mWork.mWorkKeyPressFlag = 0;
			mMaininf.mWork.mWorkKeyPressFlag1 = 0;
			//api_UART2_Display_SendCMDData(2,1,1);
			api_Led_Status_Set(0,0);
			api_Led_Status_Set(1,0);
 			vTaskDelay(100);
			mMaininf.mWork.mWorkChecking = 1;
			mMaininf.mWork.mWorkStep = TEST_DUST;
		}
		
		
		if(mMaininf.mWork.mWorkChecking == 1)
		{
			if(mMaininf.mWork.mWorkStep != mMaininf.mWork.mWorkStepOld)
			{
				mMaininf.mWork.mWorkStepOld = mMaininf.mWork.mWorkStep;
				
				switch(mMaininf.mWork.mWorkStep)
				{
					case TEST_DUST ://01
						if(api_Test_ADC(&ADCValue[2],250,250) == 1)
						{
							mMaininf.mWork.mWorkDustFlag  = 1;
// 							api_Control_Motor(0,1);
// 							vTaskDelay(2000);
// 							if(api_Test_ADC(&ADCValue[2],3288,808) == 1)
// 							{
// 								api_Led_Status_Set(0,1);
// 							}
// 							else
// 							{
// 								api_Led_Status_Set(0,2);
// 							}
						}
						else
						{
							api_Led_Status_Set(0,2);
						}
						
						if(api_ReadGpioInputStauts(GPIOD,GPIO_Pin_2,1,5) == 1)
						{
							mMaininf.mWork.mWorkDustBoxFlag = 1;
						}
						else
						{
							api_Led_Status_Set(1,2);
						}
						
						api_Control_Motor(0,1);
						api_Control_Motor(1,1);
						vTaskDelay(1000);
						
						if(mMaininf.mWork.mWorkDustFlag == 1)
						{
							if(api_Test_ADC(&ADCValue[2],3288,808) == 1)
							{
								api_Led_Status_Set(0,1);
							}
							else
							{
								api_Led_Status_Set(0,2);
							}
						}
						else
						{
							api_Led_Status_Set(0,2);
						}
						
						if(mMaininf.mWork.mWorkDustBoxFlag == 1)
						{	
							if(api_ReadGpioInputStauts(GPIOD,GPIO_Pin_2,0,5) == 1)
							{
								api_Led_Status_Set(1,1);
							}
							else
							{
								api_Led_Status_Set(1,2);
							}
						}
						else
						{
							api_Led_Status_Set(1,2);
						}
						
						api_Control_Motor(0,0);
						api_Control_Motor(1,0);
						mMaininf.mWork.mWorkStep = TEST_DUSTBOX;
						break;
					case TEST_DUSTBOX ://02
// 						if(api_ReadGpioInputStauts(GPIOD,GPIO_Pin_2,1,5) == 1)
// 						{
// 							api_Control_Motor(1,1);
// 							vTaskDelay(2000);
// 							if(api_ReadGpioInputStauts(GPIOD,GPIO_Pin_2,0,5) == 1)
// 							{
// 								api_Led_Status_Set(1,1);
// 							}
// 							else
// 							{
// 								api_Led_Status_Set(1,2);
// 							}
// 						}
// 						else
// 						{
// 							api_Led_Status_Set(1,2);
// 						}
// 						api_Control_Motor(1,0);
						mMaininf.mWork.mWorkStep = TEST_LAST;
						break;
					case TEST_LAST:
						mMaininf.mWork.mWorkChecking = 0;
						mMaininf.mWork.mWorkStep = 0;
						mMaininf.mWork.mWorkDustFlag = 0;
						mMaininf.mWork.mWorkDustBoxFlag = 0;
						break;
					default :
						break;
				}
			}
		}
// 		else
// 		{
// 			api_Control_Motor(14,0);
// 			api_Control_Motor(17,0);
// 			api_Control_Motor(18,0);
// 			api_Control_Motor(23,0);
// 		}
	
	}
}

/*****************************************************************************
 * @name       :void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status)
{
	u8 mCont = 0;
	u8 mStatus = 0;
	
	do
	{
		if(++mCont > 3)
		{
			return;
		}
		
		api_UART2_Display_SendCMDData(mode,cmd,status);
		vTaskDelay(1000);
		if((mMaininf.mUart2.mReceiveFlag == 1) && (mMaininf.mUart2.ReceiveBuf[0] == 1) && (mMaininf.mUart2.ReceiveBuf[1] == cmd) &&
		   (mMaininf.mUart2.ReceiveBuf[2] == 1))
		{
			mMaininf.mUart2.mReceiveFlag = 0;
			mStatus = 1;
		}
	}while(mStatus == 0);
	
}

/*****************************************************************************
 * @name       :void api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :发送命令到主板
 * @parameters :testtype : 0:读取数据   1:检测发射    2:检测接收   waittime:单次检查时间  
				type:类型0：状态  1：数据     num:重发次数
 * @retvalue   :0:主板无数据返回     1：主板有数据返回
******************************************************************************/
u8 api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime,u8 type,u8 num)
{
	u8 mCont = 0;
	
	mMaininf.mUart1.ReceiveBuf[4] = 0;
	
	if(type == 0)
	{
		do{
			if(++mCont > num) return 0;//未接收到数据
			api_UART1_MainBoard_SendCMDData(seq,mode,cmd);
			vTaskDelay(waittime);
		}while((mMaininf.mUart1.mReceiveFlag == 0) || ((mMaininf.mUart1.mReceiveFlag == 1) && (mMaininf.mUart1.ReceiveBuf[4] == 0)));
		
	}
	else
	{
		do{
			if(++mCont > num) return 0;//未接收到数据
			api_UART1_MainBoard_SendCMDData(seq,mode,cmd);
			vTaskDelay(waittime);
		}while(mMaininf.mUart1.mReceiveFlag == 0);
		
	}
	
	mMaininf.mUart1.mReceiveFlag = 0;
	
	return 1;//接收到数据
}

