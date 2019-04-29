
#ifndef Tasktypedef
	#define Tasktypedef		
			/* exact-width signed integer types */
	typedef   signed          char int8_t;
	typedef   signed short     int int16_t;
	typedef   signed           int int32_t;
	typedef   signed       __int64 int64_t;

			/* exact-width unsigned integer types */
	typedef unsigned          char uint8_t;
	typedef unsigned short     int uint16_t;
	typedef unsigned           int uint32_t;
	typedef unsigned       __int64 uint64_t;

			/* 7.18.1.2 */

			/* smallest type of at least n bits */
			/* minimum-width signed integer types */
	typedef   signed          char int_least8_t;
	typedef   signed short     int int_least16_t;
	typedef   signed           int int_least32_t;
	typedef   signed       __int64 int_least64_t;

			/* minimum-width unsigned integer types */
	typedef unsigned          char uint_least8_t;
	typedef unsigned short     int uint_least16_t;
	typedef unsigned           int uint_least32_t;
	typedef unsigned       __int64 uint_least64_t;

	#define		T_200us			1	//200us*50
	#define		T_1ms				5
	#define		T_5ms				25
	#define		T_10ms			50
	#define		T_100ms			500
	#define		T_500ms		  2500	
	#define		T_750ms		  3750	
	#define		T_1s				5000

	typedef enum{
		Task_Idel = 0,	
		Task_Process ,
		Task_Close					
	}Task_typedef;	
	
	typedef enum{
		TaskIdel = 0,	
		TaskBusy ,			
	}TaskBusy_typedef;	
	
	typedef struct {
		uint8_t				uc_TaskID;					//任務的id
		Task_typedef	uc_TaskMode;				//目前任務的模式
		uint16_t 			usi_Timers_Mode;					//中斷時間模試
		void					(*func)(void);			//一般迴圈的任務
		void 					(*isrfunc)(void);		//中斷迴圈的作務
	}typedef_MainTaskJob;
	
	
	
	typedef enum{
		CMD_Job_Idel = 0,		//無指令狀態
		CMD_Job_Start = 1,	//指令執行狀態
		CMD_Job_Insert = 98,//可插入指令狀態
		CMD_Job_Close	=99		//結束狀態		
	}Tasl_typedef;	
	
	typedef struct {
		uint8_t				uc_TaskID;					//任務的id
		uint8_t				uc_TaskProcess;				
		uint32_t 			usi_Timers;					//任務的時間計數	
	}typedef_CMD_Task_Data;
	
	typedef struct {
		typedef_CMD_Task_Data				Task;					//任務的id
		void					(*func)(typedef_CMD_Task_Data *Task);			//一般迴圈的任務
	}typedef_CMD_Task;
#endif
