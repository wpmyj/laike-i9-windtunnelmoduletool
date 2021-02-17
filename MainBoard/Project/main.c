/****************************************************************************************************/
/*			@FileName		:	MAIN.c															  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/* FreeRTOS --------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOSConfig.h"
//#include "death.h"
#include "semphr.h"
#include "projdefs.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
#include "bsp.h"
#include "gpioredef.h"
#include "apiLib.h"

#include "TK_TimerController.h"
#include "TK_TestController.h"
#include "TK_DisplayController.h"



/* Variable --------------------------------------------------------------------*/
_ST_MAINMANAGER mMaininf;
__IO uint16_t ADCValue[8];
//ST_MAINMANAGER mMainManager;
//SemaphoreHandle_t InitSD_Semaphore;
TaskHandle_t xTaskTimer,xTaskTest;

/* Function --------------------------------------------------------------------*/
void vCreateQueueAndSemphr(void);
void vCreateTaskManager(void);





int main(void)
{
	prvSetupHardware();
	
/*     Create QueueAndSemphr.    */
	vCreateQueueAndSemphr();
	
/*     Create Task.              */
	vCreateTaskManager();

/*     Start the scheduler.      */
	vTaskStartScheduler();

	return 0;
}


void vCreateQueueAndSemphr(void)
{	
// 	Burn_Semaphore=xSemaphoreCreateBinary();
// 	Version_Semaphore = xSemaphoreCreateBinary();
// 	if(Burn_Semaphore == NULL)
// 	{
// 		/*堆栈内存不足，进行相应相应处理*/
// //		iossf = 0;
// 	}
// 	{
// 		/*信号量创建成功，前为信号量句柄，在这里调用API函数xSemaphoreTake()来获取信号量必然失败，因为创建的信号量的初始值为空*/
// //		iossf = 1;
// 	}
}

void vCreateTaskManager(void)
{
	xTaskCreate( TK_TimerController, "TimerTask", mainTIMER_TASK_STACK_SIZE, NULL, mainTIMER_TASK_PRIORITY, &xTaskTimer );
	xTaskCreate( TK_TestController, "TestTask", mainTEST_TASK_STACK_SIZE, NULL, mainTEST_TASK_PRIORITY, &xTaskTest );
//	xTaskCreate( TK_CheckKeyTask, "CheckKeyTask", mainCHECKKEY_TASK_STACK_SIZE, NULL, mainCHECKKEY_TASK_PRIORITY, &xTaskKeyCheck );
//	xTaskCreate( TK_CheckSDTask, "CheckSDTask", mainCHECKSD_TASK_STACK_SIZE, NULL, mainCHECKSD_TASK_PRIORITY, &xTaskSDCheck );
//	xTaskCreate( TK_VersionCheckTask, "VersionCheckTask", mainVERSIONCHECK_TASK_STACK_SIZE, NULL, mainVERSIONCHECK_TASK_PRIORITY, &xTaskVersionCheck );
//	xTaskCreate( TK_PrintTask, "PrintTask", mainPRINT_TASK_STACK_SIZE, NULL, mainPRINT_TASK_PRIORITY, &xTaskPrint );
//	xTaskCreate( TK_BurnTask, "BurnTask", mainBURN_TASK_STACK_SIZE, NULL, mainBURN_TASK_PRIORITY, &xTaskBurn );
//	
//	vTaskSuspend(xTaskPrint);
}



void vApplicationTickHook(void)
{
	mMaininf.mWork.mWorkLedCont ++;
	
	if(mMaininf.mWork.mWorkLedCont >= 500)
	{
		mMaininf.mWork.mWorkLedFlag = ~mMaininf.mWork.mWorkLedFlag;
		
		for(mMaininf.mWork.mWorkLedTime = 0;mMaininf.mWork.mWorkLedTime < 5;mMaininf.mWork.mWorkLedTime ++)
		{
			api_Led_Control(mMaininf.mWork.mWorkLedTime,mMaininf.mWork.mWorkLedStatus[mMaininf.mWork.mWorkLedTime]);
			
		}
		
		mMaininf.mWork.mWorkLedCont = 0;
	}
}

































