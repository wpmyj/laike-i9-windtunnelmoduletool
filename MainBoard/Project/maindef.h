/****************************************************************************************************/
/*			@FileName		:	MAINDEF.h																																	  	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__MAINDEF_H__
#define	__MAINDEF_H__

#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f10x.h"


/*		struct congig		*/



#ifdef __cplusplus
extern "C" {
#endif
	
	
#define m_Ok 1                         //真
#define m_NoOk 0                       //假
	
#define BURN_TIMEOUT 300               //烧录步骤500ms超时	
	
#define mePRINT_QUEUE_SIZE	(5)
#define meBURN_QUEUE_SIZE	(5)
#define mDELAY100msTick		( pdMS_TO_TICKS( ( TickType_t ) 100 ) )	
#define mDELAY200msTick		( pdMS_TO_TICKS( ( TickType_t ) 200 ) )	
#define mDELAY500msTick		( pdMS_TO_TICKS( ( TickType_t ) 500 ) )
	
	
/* Task priorities. */
//#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
//#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
//#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
//#define mainCREATOR_TASK_PRIORITY           ( tskIDLE_PRIORITY + 3 )
//#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainCOM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainINTEGER_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define mainTIMER_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainTEST_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
// #define mainCHECKKEY_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
// #define mainCHECKSD_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
// #define mainPRINT_TASK_PRIORITY          (tskIDLE_PRIORITY + 2 )
// #define mainBURN_TASK_PRIORITY          (tskIDLE_PRIORITY + 2 )
// #define mainVERSIONCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 2 )


/* Task Stack. */
#define mainTIMER_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
#define mainTEST_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainCHECKKEY_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainCHECKSD_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainVERSIONCHECK_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainPRINT_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainBURN_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 128 )



/*--------------------------------------------------------------------------

        自定义结构体

---------------------------------------------------------------------------*/	


/*   	 自定义			*/
#define SYSTEMTIMEMAX                86400000               /*   System timing maximum 24 hours  */

/* timeout time define */

#define TIMEOUT_0ms           (0)               /*   0ms超时      */
#define TIMEOUT_5ms           (5)               /*   5ms超时      */
#define TIMEOUT_10ms          (10)              /*   10ms超时     */
#define TIMEOUT_50ms          (50)              /*   50ms超时     */
#define TIMEOUT_100ms         (100)             /*   100ms超时    */
#define TIMEOUT_300ms         (300)             /*   300ms超时    */
#define TIMEOUT_500ms         (500)             /*   500ms超时    */
#define TIMEOUT_1000ms        (1000)            /*   1000ms超时   */
#define TIMEOUT_3500ms        (3500)            /*   3500ms超时   */
#define TIMEOUT_5000ms        (5000)            /*   5000ms超时   */

/*   	 结构体声明			*/
typedef enum {
	ST_MAIN_0xAA = 0x01,
	ST_MAIN_0xDD,
	ST_MAIN_SEQ,
	ST_MAIN_MODE,
	ST_MAIN_CMD,
	ST_MAIN_LEN,
	ST_MAIN_DATA,
	ST_MAIN_BCC,
} UART1_RECEIVE_STEP;

typedef enum {
	ST_0x55 = 0x01,
	ST_0xAA,
	ST_MODE,
	ST_CMD,
	ST_STA,
	ST_BCC
} UART5_RECEIVE_STEP;

// typedef enum
// {
// 	TEST_START_VERSION = 0x01,        //01读取版本号
// 	TEST_TOF_POWER,                   //02TOF供电
//     TEST_TOF_COMMUNICATION,           //03TOF通讯
//     TEST_TOF_RESET,                   //04TOF复位
// 	TEST_WIFI,                        //05测试wifi
// 	TEST_SIDE_A_SEND,                 //06沿边A信号发射
//     TEST_SIDE_B_SEND,                 //07沿边B信号发射
// 	TEST_LEFT_SIDE_REC,               //08左沿边接收
// 	TEST_RIGHT_SIDE_REC,              //09右沿边接收
// 	TEST_LEFT_GUIDE,                  //10左引导接收
// 	TEST_RIGHT_GUIDE,                 //11右引导接收
// 	TEST_TOP_GUIDE,                   //12上引导接收
// 	TEST_FRONT_GUIDE,                 //13前引导接收
// 	TEST_LATE_GUIDE,                  //14后引导接收
// 	TEST_GUIDE_POWER,
// 	TEST_AVOIDBUMP_A_SEND,            //15免碰撞A发射
//     TEST_AVOIDBUMP_B_SEND,            //16免碰撞B发射
// 	TEST_LEFT_AVOIDBUMP_REC,          //17左免碰撞接收
// 	TEST_RIGHT_AVOIDBUMP_REC,         //18右免碰撞接收
// 	TEST_FRONT_AVOIDBUMP_REC,         //19前免碰撞接收
// 	TEST_PATHPLAN_UART,               //20大核串口
// 	TEST_GYRO,                        //21测试陀螺仪
// 	TEST_KEY1,                        //22按键1
//     TEST_KEY2,                        //23按键2
//     TEST_KEY3,                        //24按键3
// 	TEST_DROP_SEND_LEFT,              //25下视发射
// 	TEST_DROP_SEND_RIGHT,
// 	TEST_DROP_SEND_FRONT,
// 	TEST_DROP_SEND_LATE,
// 	TEST_LEFT_DROP_REC,               //26左下视接收
// 	TEST_RIGHT_DROP_REC,              //27右下视接收
// 	TEST_FRONT_DROP_REC,              //28前下视接收
// 	TEST_LATE_DROP_REC,               //29后下视接收
// 	TEST_LEFT_BUMP,                   //30左碰撞接收
// 	TEST_LEFT_BUMP_POWER,
// 	TEST_RIGHT_BUMP,                  //31右碰撞接收
// 	TEST_RIGHT_BUMP_POWER,
// 	TEST_LEFT_LEAVELAND,              //32左离地接收
//     TEST_RIGHT_LEAVELAND,             //33右离地接收
// 	TEST_LEFT_WHEEL_FEEDBACK,         //34左大轮反馈
// 	TEST_LEFT_WHEEL_FEEDBACK_POWER,
//     TEST_RIGHT_WHEEL_FEEDBACK,        //35右大轮反馈
// 	TEST_RIGHT_WHEEL_FEEDBACK_POWER,                             //右码盘供电
// 	TEST_LEFT_WHEEL,                  //36左大轮发射
//     TEST_RIGHT_WHEEL,                 //37右大轮发射
// 	TEST_ROLLBURSH_CUR_FEEDBACK,      //38滚刷电流反馈
// 	TEST_VACUUM_FEEDBACK,             //39吸尘电机反馈
// 	TEST_VACUUM_CONTROL,              //40吸尘电机控制
// 	TEST_DISCHARGE_CUR_FEEDBACK,      //41电池放电电流反馈
// 	TEST_POWER_NTC,                   //42检测NTC
// 	TEST_POWER_POWER,                                            //电池供电脚
//     TEST_CHARGE,                      //43检测充电
// 	TEST_OPEN_KEY,                    //44开机键
// 	TEST_DUST_REC,                    //45灰尘接收
// 	TEST_DUST_POWER,
// 	TEST_DUSTCUP_REC,                 //46尘杯接收
// 	TEST_DUSTCUP_POWER,
// 	TEST_WATERTANK,                   //47测试水箱
// 	TEST_POSITION_CAMERA,             //48检测定位摄像头
// 	TEST_POSITION_CAMERA_POWER,
// 	TEST_DC5V,
// 	

// 	
// 	TEST_FILE,                        //49测试FILE
// 	TEST_OK                           //50测试OK
// 	
// }enum_TEST_CMD;

// typedef enum
// {
// 	TEST_START = 0x01,                //01开始
// 	TEST_UART,
// 	TEST_SYSPWR,
// 	TEST_GUIDE1,
// 	TEST_GUIDE2,
// 	TEST_GUIDE3,
// 	TEST_GUIDE4,
// 	TEST_AVOID_BUMP1,
// 	TEST_AVOID_BUMP2,
// 	TEST_AVOID_BUMP3,
// 	TEST_TOF_VSEL4V6,
// 	TEST_TOF_CSI_AVDD,
// 	TEST_TOF_CSI_DVDD,
// 	TEST_TOF,
// 	TEST_POWER_DC5V,
// 	TEST_POWER_VCC3V3,
// 	TEST_POWER_VCC1V8,
// 	TEST_POWER_VCC1V3,
// 	TEST_POWER_DC3V3,
// 	
// 	TEST_FILE,                        //49测试FILE
// 	TEST_OK                           //50测试OK
// 	
// }enum_TEST_CMD;

#define LED_B0           0
#define LED_B1           1
#define LED_B2           2
#define LED_B3           3
#define LED_B4           4
#define LED_B5           5
#define LED_ALL          11

typedef enum
{
	TEST_DUST = 0x01,                        //02灰尘检测
	TEST_DUSTBOX,                            //02尘盒检测
	TEST_LAST
	
}enum_TEST_CMD;


typedef struct _ST_SYSTEM_MANAGER{
	u32 mSystemTick ;                /*  1ms 模拟滴答计数器   */
	u32 mPowerOnStartTime ;
	
	u32 mGuideReceiveTime ;
	u32 mGuideCheckTime ;
	
	u32 mSystem200usTick;
}_ST_SYSTEM_MANAGER;

typedef struct _ST_USART_MANAGER{
	u8 TxBuffer[64];
	u8 RxBuffer[64];
	u8 SendBuf[64];
	u8 ReceiveBuf[64];
	
	u16 mSendSize;
	u16 mSendCont;
	
	u8 mReceiveStep : 4;
	u8 mReceiveLen;
	u8 mReceiveBCC;
	u16 mReceiveSize;
	u16 mReceiveCont;
	u16 mReceiveTimeOut;
	
	u8 mReceiveFlag : 1;
	
}_ST_USART_MANAGER;

typedef struct{
    u8 Flag;
    u8 Status;
} _FS;

typedef struct _ST_WORK_MANAGER{
	u8 mWorkInitFlag : 1;    //0:未初始化成功 1:初始化成功
	u8 mWorkChecking : 1;    //0:没有检测     1：正在检测中
	u8 mWorkCheckStatus : 2; //0:正在检测     1：检测成功     2：检测失败
	
	u8 mWorkStep;
	u8 mWorkStepOld;
	u8 mWorkFileStep;
	
	u8 mWorkTouchStep;
	
	u8 mWorkGuideSendFlag : 2;
	u8 mWorkGuideSendCont : 4;
	u8 mWorkGuideReceiveFlag : 2;          //0:未开始接收   1：开始接收guide top  2:开始接收guide front
	u8 mWorkGuideFirstReceiveFlag : 1;     //0:第一次检测   1：不是第一次检测
	u8 mWorkGuideReceiveSuccessFlag : 1;   //0:未接收成功   1：接收成功
	
 	u8 mWorkKeyPressFlag : 1;
	u8 mWorkKeyPressFlag1 : 1;
	u8 mWorkKeyCont;
	
	u32 mWorkThingHight;
	
	u8 mWorkSensorSendStep;
	u8 mWorkSensorSendDropFlag : 1;
	u8 mWorkSensorSendAlongSideFlag : 1;
	u8 mWorkSensorSendAvoidBumpFlag : 1;
	
	u8 mWorkSensorAvoidBumpCont;
	u16 mWorkSensorOnOffAverage[15][2];//位置   0:开  1:关
	u16 mWorkSensorOnAvl[15][4];
	u16 mWorkSensorOffAvl[15][4];
	u16 mWorkSensorDataAvl[15];
	
	
	u8 mWorkSensorError;
	
	u8 mWorkLedStatus[5];
	
	u8 mWorkLedFlag : 1;
	u8 mWorkLedTime : 4;
	u16 mWorkLedCont;
	
	u8 mWorkDustFlag : 1;
	u8 mWorkDustBoxFlag : 1;
}_ST_WORK_MANAGER;

// typedef struct _ST_WORK_MANAGER{
// 	u8 mWorkInitFlag : 1;    //0:未初始化成功 1:初始化成功
// 	u8 mWorkChecking : 1;    //0:没有检测     1：正在检测中
// 	u8 mWorkCheckStatus : 2; //0:正在检测     1：检测成功     2：检测失败
// 	
// 	u8 mWorkStep;
// 	u8 mWorkStepOld;
// 	u8 mWorkFileStep;
// 	
// 	u8 mWorkGuideSendFlag : 1;//0:不发射    1:发射
// 	u8 mWorkGuideSendStep;
// 	u16 mWorkGuideSendCont;
// 	_FS mWorkGuide[5];
// 	
// 	u8 mWorkKeyPressFlag : 1;
// 	u8 mWorkKeyPressFlag1 : 1;
// 	u8 mWorkKeyCont;
// 	
// 	u16 mWorkAlongSideReadVal;
// 	u16 mWorkAvoidBumpReadVal;
// 	u16 mWorkDropReadVal;
// 	u16 mWorkCodeReadVal;
// 	u16 mWorkDustReadVal;
// 	
// 	u8 mWorkCodeSendFlag : 1;      //0:不发    1:发
// 	u16 mWorkCodeSendCont;
// 	
// 	u8 mWorkDropSendFlag : 1;
// 	u16 mWorkDropSendCont;
// 	
// 	u8 mWorkBigUartFlag : 1;
// }_ST_WORK_MANAGER;


typedef struct _ST_MAINMANAGER{
	/*        文件内定义        */
	_ST_SYSTEM_MANAGER         mSystem;

	_ST_USART_MANAGER          mUart1;
	_ST_USART_MANAGER          mUart2;
//	_ST_USART_MANAGER          mUart4;
//	_ST_USART_MANAGER          mUart5;
	_ST_WORK_MANAGER           mWork;
}_ST_MAINMANAGER;
		
extern _ST_MAINMANAGER mMaininf;
extern __IO uint16_t ADCValue[8];
	
void prvSetupHardware(void);
void vCreateQueueAndSemphr(void);



	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__MAINDEF_H__*/	

