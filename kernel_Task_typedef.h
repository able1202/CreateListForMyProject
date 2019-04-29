
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
		uint8_t				uc_TaskID;					//���Ȫ�id
		Task_typedef	uc_TaskMode;				//�ثe���Ȫ��Ҧ�
		uint16_t 			usi_Timers_Mode;					//���_�ɶ��Ҹ�
		void					(*func)(void);			//�@��j�骺����
		void 					(*isrfunc)(void);		//���_�j�骺�@��
	}typedef_MainTaskJob;
	
	
	
	typedef enum{
		CMD_Job_Idel = 0,		//�L���O���A
		CMD_Job_Start = 1,	//���O���檬�A
		CMD_Job_Insert = 98,//�i���J���O���A
		CMD_Job_Close	=99		//�������A		
	}Tasl_typedef;	
	
	typedef struct {
		uint8_t				uc_TaskID;					//���Ȫ�id
		uint8_t				uc_TaskProcess;				
		uint32_t 			usi_Timers;					//���Ȫ��ɶ��p��	
	}typedef_CMD_Task_Data;
	
	typedef struct {
		typedef_CMD_Task_Data				Task;					//���Ȫ�id
		void					(*func)(typedef_CMD_Task_Data *Task);			//�@��j�骺����
	}typedef_CMD_Task;
#endif
