
#include "kernel_Task.h"
#include <string.h>
#define		On	1 gdfsgdfsg
#define		Off	0

typedef_MainTaskJob 	*TaskJob_ptr;
//單一功能執行
typedef_CMD_Task	CMDJob_prt;

////////////////////////////
/*	任務初使化							*/
////////////////////////////
void CMD_TaskInit(void)
{
	memset(&CMDJob_prt,0,sizeof(CMDJob_prt));
}

////////////////////////////
/*	輸入任務							*/
////////////////////////////
uint8_t CMD_TaskInsert(uint8_t ID,void	(*funcTemp)(typedef_CMD_Task_Data *Task))
{
	if((CMDJob_prt.Task.uc_TaskProcess==CMD_Job_Idel)||(CMDJob_prt.Task.uc_TaskProcess==CMD_Job_Insert))
	{
		if(CMDJob_prt.Task.uc_TaskProcess==CMD_Job_Insert)
		{
			CMDJob_prt.Task.usi_Timers=0;
			CMDJob_prt.func(&CMDJob_prt.Task);
		}
		CMDJob_prt.Task.uc_TaskID=ID;
		CMDJob_prt.Task.uc_TaskProcess=CMD_Job_Start;
		CMDJob_prt.Task.usi_Timers=0;
		CMDJob_prt.func=funcTemp;
		return TaskIdel;
	}
		return TaskBusy;
}

////////////////////////////
/*	任務觸發							*/
////////////////////////////
void CMD_TaskProcess(void)
{
	if(CMDJob_prt.Task.uc_TaskProcess==CMD_Job_Close)
	{
		CMDJob_prt.Task.uc_TaskProcess=CMD_Job_Idel;
	}else if(CMDJob_prt.Task.uc_TaskProcess==CMD_Job_Insert)
	{
		CMDJob_prt.func(&CMDJob_prt.Task);
	}else	if(CMDJob_prt.Task.uc_TaskProcess!=CMD_Job_Idel)
	{
		CMDJob_prt.func(&CMDJob_prt.Task);
	}
}

////////////////////////////
/*	Busy check						*/
////////////////////////////
uint8_t CMD_BusyCheck(void)
{
	if(CMDJob_prt.Task.uc_TaskProcess!=CMD_Job_Idel)
	{
		return TaskBusy;
	}
		return TaskIdel;
}
////////////////////////////
/*	任務觸發							*/
////////////////////////////
void CMD_TaskNVIC(void)
{
	if(CMDJob_prt.Task.uc_TaskProcess!=CMD_Job_Idel)
	{
		if(CMDJob_prt.Task.usi_Timers!=0)
		{
			CMDJob_prt.Task.usi_Timers--;
		}
	}
}

////////////////////////////
/*	輸入任務							*/
////////////////////////////
void Kernel_TaskInsert(typedef_MainTaskJob *cmd_temp)
{
	TaskJob_ptr=cmd_temp;
}


////////////////////////////
/*	任務觸發							*/
////////////////////////////
void Kernel_TaskEnable(uint8_t ID)
{
	typedef_MainTaskJob *JobTemp;
	JobTemp=TaskJob_ptr;
	while(JobTemp->uc_TaskID!=0)
	{
		if(JobTemp->uc_TaskID==ID)
		{
			JobTemp->uc_TaskMode=Task_Process;
		}
		JobTemp++;
	}
}

////////////////////////////
/*	一般任務執行					*/
////////////////////////////
void Kernel_Taskfun(void)
{
	typedef_MainTaskJob *JobTemp;
	JobTemp=TaskJob_ptr;
	while(JobTemp->uc_TaskID!=0)
	{
		if(JobTemp->uc_TaskMode==Task_Process)
		{
			if(JobTemp->func!=0)
			{
					JobTemp->func();
			}
		}			
		JobTemp++;
	}
}
////////////////////////////
/*	中斷任務執行					*/
////////////////////////////
uint16_t TimerCount=0;
void Kernel_isrTaskfun(void)
{
	typedef_MainTaskJob *JobTemp;
	JobTemp=TaskJob_ptr;
	TimerCount++;
	if(TimerCount>T_1s)
	{
		TimerCount=1;
	}
	while(JobTemp->uc_TaskID!=0)
	{
		if(JobTemp->uc_TaskMode==Task_Process)
		{
			if(JobTemp->isrfunc!=0)
			{
				if((TimerCount%JobTemp->usi_Timers_Mode)==0)
				{
					JobTemp->isrfunc();
				}
			}
		}
		JobTemp++;
	}
}

////////////////////////////
/*	關閉任務							*/
////////////////////////////
void Kernel_TaskClose(uint8_t ID)
{
	typedef_MainTaskJob *JobTemp;
	JobTemp=TaskJob_ptr;
	while(JobTemp->uc_TaskID!=0)
	{
		if(JobTemp->uc_TaskID==ID)
		{
			JobTemp->uc_TaskMode=Task_Close;
		}
		JobTemp++;
	}
}
