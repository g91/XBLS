
/*
Teirs 360 Research

 There are 3 ppe cores and 2 threads per core. These threads are numbered as 0-5 in this document.
 Even threads are refered to the cores themselves or 'hardware threads'. (threads 0, 2, 4)
 Odd threads are refered to as the previous core's virtual thread
  - Thread 1 is the virtual thread of thread 0
  - Thread 3 is the virtual thread of thread 2
  - Thread 5 is the virtual thread of thread 4
 So the processor can be organized like this:
 	________________________________________________________________
 	|							  XCPU							   |
 	|______________________________________________________________|
 	|		 Core 0 	 |		  Core 1	  |		   Core 2	   |
 	|____________________|____________________|____________________|
 	| hwThread | vThread | hwThread | vThread | hwThread | vThread |
 	|__________|_________|__________|_________|__________|_________|
 	| Thread 0 | Thread 1| Thread 2 | Thread 3| Thread 4 | Thread 5|
 	|__________|_________|__________|_________|__________|_________|

 When something needs to change a cpu management register the system first has to Quiesce threads 1-5.

 The Quiesce process works as follows:
  - Start a thread on thread 0, Have that thread start threads on threads 1-5 and call HvxQuiesceProcessor
    on those threads. DO NOT CALL HvxQuiesceProcessor ON THREAD 0.
  - Threads 1-5 will call HvpSaveThread and will wait until thread 0 starts saving.
  - On thread 0, call HvpSaveThread. Thread 0 will then check if the other threads are waiting to continue,
    if they are not ready, it will hang until they are.
  - Thread 0 will save the cpu/thread management registers to memory
  - Thread 0 will then make sure all threads were Quiesced for the same reason, if not it's considered a
    system error and hangs the processor.
  - Thread 0 then notifies the other threads to continue saving and waits until they're done.
  - Threads 1-5 will set their IRQ register to 0x7C (I think this is to disable interrupts for the thread)
  - Threads 1-5 will save their DEC register to memory and set it to 0x7FFFFFFF
  - Hardware threads will wait until their virtual threads are done and sleeping, then they save their HDEC
    register to memory and set it to 0x7FFFFFFF
  - Threads 1-5 update their flags in the TSCR register and then update their state, notifying thread 0
    that they are done saving.
  - Thread 0 then flushes the L2 cachelines and syncs all thread_states areas to memory.
  - Thread 0 saves it's DEC and HDEC registers to memory and sets them to 0x7FFFFFFF
  - Thread 0 updates it's flags in the TSCR register and then updates its state.

 Now thread 0 can change what ever it needs to while all other threads are asleep. When thread 0 is done,
 it much wake up the other threads by calling HvpRestoreThread.

 The Restoration process works as follows:
  - HvpRestoreThread makes sure each thread calling it was saved before, if they weren't its considered an
    error and just hanges.
  - Thread 0 restores the general irql registers and HDEC from the saved values in memory.
  - Thread 0 generates a RESET interrupt on thread 1 and waits for it to be ready
  - Thread 1 goes to the RESET handler which verifies the interrupt was not an error
  - Thread 1 calls HvpRestoreThread and sets it IRQ register to 0 and restores its DEC register
  - Thread 1 notifies thread 0 that it is ready to continue and waits for restoration to complete
  - Thread 0 sets its IRQ register to 0 and restores its DEC register
  - Thread 0 generates a RESET interrupt on thread 2 and waits for it to be ready
  - Thread 2 goes to the RESET handler which verifies the interrupt was not an error
  - Thread 2 calls HvpRestoreThread and restores its HDEC register from memory
  - Thread 2 generates a RESET interrupt on thread 3 and waits for it to be ready
  - Thread 3 goes to the RESET handler which verifies the interrupt was not an error
  - Thread 3 calls HvpRestoreThread and sets it IRQ register to 0 and restores its DEC register
  - Thread 3 notifies thread 2 that it is ready to continue and waits for restoration to complete
  - Thread 2 sets its IRQ register to 0 and restores its DEC register
  - Thread 2 notifies thread 0 that it is ready to continue and waits for restoration to complete
  - Thread 0 generates a RESET interrupt on thread 4 and waits for it to be ready
  - Thread 4 goes to the RESET handler which verifies the interrupt was not an error
  - Thread 4 calls HvpRestoreThread and restores its HDEC register from memory
  - Thread 4 generates a RESET interrupt on thread 5 and waits for it to be ready
  - Thread 5 goes to the RESET handler which verifies the interrupt was not an error
  - Thread 5 calls HvpRestoreThread and sets it IRQ register to 0 and restores its DEC register
  - Thread 5 notifies thread 4 that it is ready to continue and waits for restoration to complete
  - Thread 4 sets its IRQ register to 0 and restores its DEC register
  - Thread 4 notifies thread 0 that it is ready to continue and waits for restoration to complete
  - Thread 0 notifies all threads that restoration is complete
  - All threads return from their syscall interrupt

picture of the above incase github screws up the formatting: https://i.imgur.com/Voh7Dvn.png
*/

#define HSPRG1 mfspr(SPR_HSPRG1)

#define STATE_ACTIVE 0
#define STATE_SAVE_STARTED 1
#define STATE_SAVE_CONTINUE 2
#define STATE_SAVE_COMPLETED 3
#define STATE_RESTORE_STARTED 4
#define STATE_RESTORE_COMPLETED 5

#define THREAD_SAVE_REASON_SETPOWERMODE 0
#define THREAD_SAVE_REASON_BLOWFUSES 1
#define THREAD_SAVE_REASON_SHADOWBOOT 2

typedef struct _THREAD_STATUS
{
	QWORD Reserved[0x10];
	BYTE PID;
	BYTE STATE;
	BYTE REASON; // i think
	BYTE SUSPENDED;
	DWORD dwUnk1;
	DWORD DEC_SAVE;
	DWORD HDEC_SAVE;
}THREAD_STATUS, *PTHREAD_STATE;

typedef struct _PPE_STATE
{
	THREAD_STATUS hThread;
	THREAD_STATUS vThread;
}PPE_STATE, *PPPE_STATE;

typedef struct _CPU_STATE
{
	PPE_STATE Core[3];
}CPU_STATE, *PCPU_STATE;

QWORD HvxQuiesceProcessor(BYTE Reason)
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// we cannot put thread 0 to sleep, how would we wake up?
	if(pThreadState->PID == 0)
		MACHINE_CHECK();

	HvpSaveThread(Reason);
	HvpSleepThread();
	HvpRestoreThread();

	return 0;
}

void _V_RESET()
{
	QWORD HID1 = mfspr(SPR_HID1);
	HID1 = (HID1 & 0xF3FFFFBFFFFFFFFF) | (3 << 58) | (1 << 38);
	// s
	mtspr(SPR_HID1, HID1);

	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// if HSPRG1 has not been set up, this is a Power On Reset
	if(!pThreadState)
		POR();

	// if HSPRG1 has been set up but the thread was not suspended, this reset is an error
	if(!pThreadState->SUSPENDED)
		MACHINE_CHECK();

	pThreadState->SUSPENDED = 0;

	// HvpSleepThread saves SRR0 and SRR1 to these registers
	mtspr(SPR_SRR0, r7);
	mtspr(SPR_SRR1, r8);
	_cctpm(); // thread priority: medium

	return;
}

// sub_84E0
void HvpSaveThread(BYTE Reason)
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;
	if(pThreadState->STATE != STATE_ACTIVE
		|| Reason > 2)
		MACHINE_CHECK();

	pThreadState->REASON = Reason;

	// notify thread 0 that this thread is ready to continue
	pThreadState->STATE = STATE_SAVE_STARTED;

	// thread 0 handles most of the saving
	if(pThreadState->PID == 0)
	{
		// wait until all threads are ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// virtual first
			while(pCPU->Core[CoreNum].vThread.STATE != STATE_SAVE_STARTED)
				continue;

			// now hardware
			while(pCPU->Core[CoreNum].hThread.STATE != STATE_SAVE_STARTED)
				continue;
		}

		// disable the timebase
		PRV_TIMEBASE_CONTROL uqwTBControl = SoC->PRV.TimebaseControl; // _REG_611A0
		uqwTBControl.TimebaseEnable = 0;
		SoC->PRV.TimebaseControl = uqwTBControl; // ei_is

		PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
		pqwIrqlState[0] = SoC->Interrupts.MiscellaneousInterruptGeneration0;
		pqwIrqlState[1] = SoC->Interrupts.MiscellaneousInterruptGeneration1;
		pqwIrqlState[2] = SoC->Interrupts.MiscellaneousInterruptGeneration2;
		pqwIrqlState[3] = SoC->Interrupts.MiscellaneousInterruptGeneration3;
		pqwIrqlState[4] = SoC->Interrupts.MiscellaneousInterruptGeneration4;

		SoC->Interrupts.MiscellaneousInterruptGeneration0 = 0; // ei
		SoC->Interrupts.MiscellaneousInterruptGeneration1 = 0; // ei
		SoC->Interrupts.MiscellaneousInterruptGeneration2 = 0; // ei
		SoC->Interrupts.MiscellaneousInterruptGeneration3 = 0; // ei
		SoC->Interrupts.MiscellaneousInterruptGeneration4 = 0; // ei_is

		pqwIrqlState[5] = SoC->PRV.PFMStatus;
		SoC->PRV.PFMStatus = 0; // _REG_611C8 - ei_is

		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// first virtual threads
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].vThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].vThread.STATE = STATE_SAVE_CONTINUE;

			// wait until thread finished save
			while(pCPU->Core[CoreNum].vThread.STATE != STATE_SAVE_COMPLETED)
				continue;

			// hardware threads now
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].hThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].hThread.STATE = STATE_SAVE_CONTINUE; // s

			// wait until thread finished save
			while(pCPU->Core[CoreNum].hThread.STATE != STATE_SAVE_COMPLETED)
				continue;
		}

		// flush out the cache without cache flush instructions? might be for the security engine?
		PBYTE pbCurPage = HvpGetCurrentPage();
		QWORD inc = 0;
		for(int i = 0;i < 0x200;i++)
			inc += pbCurPage[i * 0x80];
		// is

		// same thing as above but with the thread states
		pbCurPage = HSPRG1;
		inc = 0;
		for(int i = 0;i < 0x180;i++)
			inc += pbCurPage[i * 0x80];
		// is
	}
	else
	{
		// wait until thread 0 has saved the IRQL stuff
		while(pThreadState->STATE != STATE_SAVE_CONTINUE)
			continue;
	}

	// set this thread's irql register to 0x7C
	SoC->Interrupts.ProcessorBlock[pThreadState->PID].InterruptTaskPriority = 0x7C;

	// save this thread's DEC register
	pThreadState->DEC_SAVE = mfspr(SPR_DEC);
	mtspr(SPR_DEC, 0x7FFFFFFF);

	// only cores save the HDEC (cores are even, virtual hw threads are odd)
	if(pThreadState->PID & 1 == 0)
	{
		// wait until this core's virtual thread is asleep ?
		while(mfspr(SPR_CTRL) & 0x400000)
			continue;

		// save the HDEC
		pThreadState->HDEC_SAVE = mfspr(SPR_HDEC);
		mtspr(SPR_HDEC, 0x7FFFFFFF);
	}

	// update this thread's flags in the thread control register
	SPR_S_TSCR TSCR = mfspr(SPR_TSCR); // s
	//TSCR &= 0xFF8FFFFF;
	//TSCR |= ((~pThreadState->PID) & 1) << 20;
	TSCR.DecrementorWakeupThread0 = 0;
	TSCR.DecrementorWakeupThread1 = 0;
	TSCR.ExternalWakeup = ((~pThreadState->PID) & 1);
	mtspr(SPR_TSCR, TSCR); // s_is

	// notify thread 0 that this thread has completed it's save
	pThreadState->STATE = STATE_SAVE_COMPLETED; // s

	return;
}

// sub_150
void HvpSleepThread()
{
	// save some context
	QWORD PIR = mfspr(SPR_PIR);
	QWORD SRR0 = mfspr(SPR_SRR0);
	QWORD SRR1 = mfspr(SPR_SRR1);
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)mfspr(HSPRG1);

	// set the state
	pThreadState->SUSPENDED = 1;

	PIR = PIR & 1;
	if(!PIR)
	{
		QWORD HID1 = mfspr(SPR_HID1);
		HID1 = (HID1 & 0xF3FFFFFFFFFFFFFF) | ((PIR & 3) << 58); 
		// s
		mtspr(SPR_HID1, HID1); // s_is
	}

	// wait until sys reset to resume
	for(;;)
		mtspr(SPR_CTRL, 0);
}

// sub_87A8
void HvpRestoreThread()
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;

	// make sure the thread had saved
	if(pThreadState->STATE != STATE_SAVE_COMPLETED)
		MACHINE_CHECK();

	// update state
	pThreadState->STATE = STATE_RESTORE_STARTED;

	// check if this is a hardware thread
	if(pThreadState->PID & 1 == 0)
	{
		// if this is core 0/thread 0 restore the irql stuff
		if(pThreadState->PID == 0)
		{
			PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
			SoC->Interrupts.MiscellaneousInterruptGeneration0 = pqwIrqlState[0]; // ei
			SoC->Interrupts.MiscellaneousInterruptGeneration1 = pqwIrqlState[1]; // ei
			SoC->Interrupts.MiscellaneousInterruptGeneration2 = pqwIrqlState[2]; // ei
			SoC->Interrupts.MiscellaneousInterruptGeneration3 = pqwIrqlState[3]; // ei
			SoC->Interrupts.MiscellaneousInterruptGeneration4 = pqwIrqlState[4]; // ei_is

			SoC->PRV.PFMStatus = pqwIrqlState[5]; // - ei_is
		}

		// restore this core's HDEC register
		mtspr(SPR_HDEC, pThreadState->HDEC_SAVE);

		// wake up this core's virtual thread
		QWORD CTRL = mfspr(SPR_CTRL);
		CTRL |= 0xC00000;
		mtspr(SPR_CTRL, CTRL);

		// wait until the virtual thread wakes up
		PPPE_STATE pCore = (PPPE_STATE)pThreadState;
		while(pCore->vThread.STATE != STATE_RESTORE_COMPLETED)
			continue;
	}

	// restore this thread's DEC register
	mtspr(SPR_DEC, pThreadState->DEC_SAVE);

	// set this thread's irql register to 0
	SoC->Interrupts.ProcessorBlock[pThreadState->PID] = 0; // ei_is

	// if this is core 0/thread 0 then wake up the threads
	if(pThreadState->PID == 0)
	{
		// wake up core 1
		SoC->Interrupts.ProcessorBlock[2].InterruptTaskPriority = 0; // ei_is
		SoC->Interrupts.ProcessorBlock[0].IpiGeneration = 0x40078 // ei

		// wait until core 1 is ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		while(pCPU->Core[1].hThread.STATE != STATE_RESTORE_COMPLETED)
			continue;

		// wake up core 2
		SoC->Interrupts.ProcessorBlock[4].InterruptTaskPriority = 0; // ei_is
		SoC->Interrupts.ProcessorBlock[0].IpiGeneration = 0x100078; // ei

		// wait until core 2 is ready
		while(pCPU->Core[2].hThread.STATE != STATE_RESTORE_COMPLETED)
			continue;

		// enable the timebase
		PRV_TIMEBASE_CONTROL uqwTBControl = SoC->PRV.TimebaseControl; // _REG_611A0
		uqwTBControl.TimebaseEnable = 1;
		SoC->PRV.TimebaseControl = uqwTBControl; // ei_is

		// done restoring, notify all threads
		pCPU->Core[0].hThread.STATE = STATE_ACTIVE;
		pCPU->Core[0].vThread.STATE = STATE_ACTIVE;
		pCPU->Core[1].hThread.STATE = STATE_ACTIVE;
		pCPU->Core[1].vThread.STATE = STATE_ACTIVE;
		pCPU->Core[2].hThread.STATE = STATE_ACTIVE;
		pCPU->Core[2].vThread.STATE = STATE_ACTIVE;
		// s
	}
	else
	{
		// notify that this thread is awake
		pThreadState->STATE = STATE_RESTORE_COMPLETED; // s

		// wait until restore is done
		while(pThreadState->STATE != STATE_ACTIVE)
			continue;
	}

	// continue where thread left off
	return;
}