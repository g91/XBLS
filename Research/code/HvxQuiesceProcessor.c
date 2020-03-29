
#define HSPRG1 mfspr(SPR_HSPRG1)

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
	_cctpm()

	return;
}

// sub_84E0
void HvpSaveThread(BYTE Reason)
{
	PTHREAD_STATE pThreadState = (PTHREAD_STATE)HSPRG1;
	if(pThreadState->STATE != 0
		|| Reason > 2)
		MACHINE_CHECK();

	pThreadState->REASON = Reason;

	// notify thread 0 that this thread is ready to continue
	pThreadState->STATE = 1;

	// thread 0 handles most of the saving
	if(pThreadState->PID == 0)
	{
		// wait until all threads are ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// virtual first
			while(pCPU->Core[CoreNum].vThread.STATE != 1)
				continue;

			// now hardware
			while(pCPU->Core[CoreNum].hThread.STATE != 1)
				continue;
		}

		_REG_611A0 = _REG_611A0 & 0xFEFF; // ei_is

		PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
		pqwIrqlState[0] = _REG_56000;
		pqwIrqlState[1] = _REG_56010;
		pqwIrqlState[2] = _REG_56020;
		pqwIrqlState[3] = _REG_56030;
		pqwIrqlState[4] = _REG_56040;

		_REG_56000 = 0; // ei
		_REG_56010 = 0; // ei
		_REG_56020 = 0; // ei
		_REG_56030 = 0; // ei
		_REG_56040 = 0; // ei_is

		pqwIrqlState[5] = _REG_611C8;
		_REG_611C8 = 0; // ei_is

		for(int i = 0;i < 3;i++)
		{
			int CoreNum = 2 - i;

			// first virtual threads
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].vThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].vThread.STATE = 2;

			// wait until thread finished save
			while(pCPU->Core[CoreNum].vThread.STATE != 3)
				continue;

			// hardware threads now
			// make sure all threads are being paused for the same reason
			if(pCPU->Core[CoreNum].hThread.REASON != pThreadState->REASON)
				MACHINE_CHECK();

			// notify thread to continue with save
			pCPU->Core[CoreNum].hThread.STATE = 2; // s

			// wait until thread finished save
			while(pCPU->Core[CoreNum].hThread.STATE != 3)
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
		while(pThreadState->STATE != 2)
			continue;
	}

	// set this thread's irql register to 0x7C
	QWORD IRQLRegs = __REG_50000 + (pThreadState->PID << 12);
	write64(IRQLRegs + 8, 0x7C); // ei_is

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
	DWORD TSCR = mfspr(SPR_TSCR); // s
	TSCR &= 0xFF8FFFFF;
	TSCR |= ((~pThreadState->PID) & 1) << 20;
	mtspr(SPR_TSCR, TSCR); // s_is

	// notify thread 0 that this thread has completed it's save
	pThreadState->STATE = 3; // s

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
	if(pThreadState->STATE != 3)
		MACHINE_CHECK();

	// update state
	pThreadState->STATE = 4;

	// check if this is a hardware thread
	if(pThreadState->PID & 1 == 0)
	{
		// if this is core 0/thread 0 restore the irql stuff
		if(pThreadState->PID == 0)
		{
			PQWORD pqwIrqlState = (PQWORD)0x2000161E0;
			_REG_56000 = pqwIrqlState[0]; // ei
			_REG_56010 = pqwIrqlState[1]; // ei
			_REG_56020 = pqwIrqlState[2]; // ei
			_REG_56030 = pqwIrqlState[3]; // ei
			_REG_56040 = pqwIrqlState[4]; // ei_is

			_REG_611C8 = pqwIrqlState[5]; // ei_is
		}

		// restore this core's HDEC register
		mtspr(SPR_HDEC, pThreadState->HDEC_SAVE);

		// wake up this core's virtual thread
		QWORD CTRL = mfspr(SPR_CTRL);
		CTRL |= 0xC00000;
		mtspr(SPR_CTRL, CTRL);

		// wait until the virtual thread wakes up
		PPPE_STATE pCore = (PPPE_STATE)pThreadState;
		while(pCore->vThread.STATE != 5)
			continue;
	}

	// restore this thread's DEC register
	mtspr(SPR_DEC, pThreadState->DEC_SAVE);

	// set this thread's irql register to 0
	QWORD IRQLRegs = __REG_50000 + (pThreadState->PID << 12);
	write64(IRQLRegs + 8, 0); // ei_is

	// if this is core 0/thread 0 then finish restores
	if(pThreadState->PID == 0)
	{
		// wake up core 1
		_REG_52008 = 0; // ei_is
		_REG_50010 = 0x40078; // ei

		// wait until core 1 is ready
		PCPU_STATE pCPU = (PCPU_STATE)pThreadState;
		while(pCPU->Core1.hThread.STATE != 5)
			continue;

		// wake up core 2
		_REG_54008 = 0; // ei_is
		_REG_50010 = 0x100078; // ei

		// wait until core 2 is ready
		while(pCPU->Core2.hThread.STATE != 5)
			continue;

		// unknown register
		_REG_611A0 |= 0x100; // ei_is

		// done restoring, notify all threads
		pCPU->Core0.hThread.STATE = 0;
		pCPU->Core0.vThread.STATE = 0;
		pCPU->Core1.hThread.STATE = 0;
		pCPU->Core1.vThread.STATE = 0;
		pCPU->Core2.hThread.STATE = 0;
		pCPU->Core2.vThread.STATE = 0;
		// s
	}
	else
	{
		// notify that this thread is awake
		pThreadState->STATE = 5; // s

		// wait until restore is done
		while(pThreadState->STATE != 0)
			continue;
	}

	// continue where thread left off
	return;
}