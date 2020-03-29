// kernelp.h
// THE ACCURACY OF THIS DATA IS UNDETERMINED!!
#ifndef _KERNELP_DEFINES_H
#define _KERNELP_DEFINES_H


// *********** PACKING STARTS HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS HERE **************//
typedef struct _OBJECT_HANDLE_TABLE{
	LONG HandleCount;
	DWORD FirstFreeTableOffset;
	DWORD TableAllocation;
	PVOID RootTable; // was VOID ***
	PVOID BuiltinRootTable[8];// was VOID **
	DWORD SpinLock;
	BYTE PoolType;
	BYTE Discriminant;
	BYTE Terminating;
} OBJECT_HANDLE_TABLE, *POBJECT_HANDLE_TABLE;

typedef struct _KAPC{
	short Type;
	BYTE ApcMode;
	BYTE Inserted;
	struct _KTHREAD * Thread;
	LIST_ENTRY ApcListEntry;
	void * KernelRoutine; // function ptr
	void * RundownRoutine; // function ptr
	void * NormalRoutine; // function ptr
	void * NormalContext;
	void * SystemArgument1;
	void * SystemArgument2;
} KAPC, *PKAPC; // 40

typedef struct _DISPATCHER_HEADER{
	BYTE Type;
	BYTE Absolute;
	BYTE ProcessType;
	BYTE Inserted;
	long SignalState;
	LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER, *PDISPATCHER_HEADER; // 16

typedef struct _KEVENT{
	DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT; // 16

typedef struct _KDPC{
	short Type;
	BYTE InsertedNumber;
	BYTE TargetNumber;
	LIST_ENTRY DpcListEntry;
	void  * DeferredRoutine; // function *
	void * DeferredContext;
	void * SystemArgument1;
	void * SystemArgument2;
} KDPC, *PKDPC; // 28

typedef struct _KWAIT_BLOCK{
	LIST_ENTRY WaitListEntry;
	struct _KTHREAD* Thread;
	void * Object;
	struct _KWAIT_BLOCK * NextWaitBlock;
	USHORT WaitKey;
	USHORT WaitType;
} KWAIT_BLOCK, *PKWAIT_BLOCK; // 24

typedef struct _KTIMER{
	DISPATCHER_HEADER Header;
	ULARGE_INTEGER DueTime;
	LIST_ENTRY TimerListEntry;
	PKDPC Dpc;
	long Period;
} KTIMER, *PKTIMER; // 40

typedef struct _KPROCESS{
	DWORD ThreadListLock;
	LIST_ENTRY ThreadListHead;
	long ThreadQuantum;
	DWORD DirectoryTableBase;
	DWORD ThreadCount;
	BYTE IdlePriorityClass;
	BYTE NormalPriorityClass;
	BYTE TimeCriticalPriorityClass;
	BYTE DisableQuantum;
	DWORD DefaultKernelStackSize;
	void * TlsStaticDataImage;
	DWORD SizeOfTlsStaticData;
	DWORD SizeOfTlsStaticDataImage;
	USHORT SizeOfTlsSlots;
	BYTE Terminating;
	BYTE ProcessType;
	DWORD TlsSlotBitmap[8];
	DWORD FileObjectListLock;
	LIST_ENTRY FileObjectListHead;
	void * Win32DefaultHeapHandle;
} KPROCESS, *PKPROCESS; // 96

typedef struct _KSEMAPHORE{
	DISPATCHER_HEADER Header;
	INT32 Limit;
} KSEMAPHORE, *PKSEMAPHORE; // 20

typedef struct _KQUEUE{
	DISPATCHER_HEADER Header;
	LIST_ENTRY EntryListHead;
	DWORD CurrentCount;
	DWORD MaximumCount;
	LIST_ENTRY ThreadListHead;
} KQUEUE, *PKQUEUE; // 40

typedef struct _KINTERRUPT{
	void * ServiceRoutine; // function *
	void * ServiceContext;
	DWORD SpinLock;
	DWORD ServiceCount;
	BYTE BusIrql;
	BYTE Irql;
	BYTE Connected : 1; // this bitfield may need swapping
	BYTE Mode : 7;
	BYTE TargetNumber;
} KINTERRUPT, *PKINTERRUPT; // 20

typedef struct _KTRAP_FRAME{
	STACK_FRAME_HEADER Header;
	ULONGLONG Gpr0;
	ULONGLONG Gpr1;
	ULONGLONG Gpr2;
	ULONGLONG Gpr3;
	ULONGLONG Gpr4;
	ULONGLONG Gpr5;
	ULONGLONG Gpr6;
	ULONGLONG Gpr7;
	ULONGLONG Gpr8;
	ULONGLONG Gpr9;
	ULONGLONG Gpr10;
	ULONGLONG Gpr11;
	ULONGLONG Gpr12;
	ULONGLONG Gpr13;
	ULONGLONG Gpr14;
	ULONGLONG Gpr15;
	ULONGLONG Gpr16;
	ULONGLONG Gpr17;
	ULONGLONG Gpr18;
	ULONGLONG Gpr19;
	ULONGLONG Gpr20;
	ULONGLONG Gpr21;
	ULONGLONG Gpr22;
	ULONGLONG Gpr23;
	ULONGLONG Gpr24;
	ULONGLONG Gpr25;
	ULONGLONG Gpr26;
	ULONGLONG Gpr27;
	ULONGLONG Gpr28;
	ULONGLONG Gpr29;
	ULONGLONG Gpr30;
	ULONGLONG Gpr31;
	union{
		struct{
			BYTE OldIrql;
			PKINTERRUPT InterruptObject;
			BYTE InterruptIrql;
		} asIrq;
		BYTE ExceptionRecord[80];
	};
	ULONGLONG Ctr;
	DWORD Lr;
	DWORD Iar;
	DWORD Cr;
	DWORD Msr;
	DWORD Xer;
	DWORD UserModeControl;
} KTRAP_FRAME, *PKTRAP_FRAME; // 448

typedef struct _KTHREAD{
	DISPATCHER_HEADER Header;
	LIST_ENTRY MutantListHead;
	KTIMER Timer;
	KWAIT_BLOCK TimerWaitBlock;
	DWORD KernelTime;
	void * StackBase;
	void * StackLimit;
	void * KernelStack;
	void * TlsData;
	BYTE State;
	BYTE Alerted[2];
	BYTE Alertable;
	BYTE Priority;
	BYTE FpuExceptionEnable;
	BYTE CreateProcessType;
	BYTE CurrentProcessType;
	LIST_ENTRY ApcListHead[2];
	PKPROCESS Process;
	BYTE KernelApcInProgress;
	BYTE KernelApcPending;
	BYTE UserApcPending;
	BYTE ApcQueueable;
	DWORD ApcQueueLock;
	DWORD ContextSwitches;
	LIST_ENTRY ReadyListEntry;
	union{
		struct{
			USHORT MsrEnableMaskHigh;
			USHORT MsrEnableMaskLow;
		};
		DWORD MsrEnableMask;
	};
	long WaitStatus;
	BYTE WaitIrql;
	BYTE WaitMode;
	BYTE WaitNext;
	BYTE WaitReason;
	PKWAIT_BLOCK WaitBlockList;
	DWORD Padding1;
	DWORD KernelApcDisable;
	long Quantum;
	char Saturation;
	BYTE BasePriority;
	BYTE PriorityDecrement;
	BYTE DisableBoost;
	char SuspendCount;
	BYTE Preempted;
	BYTE HasTerminated;
	BYTE CurrentProcessor;
	struct _KPRCB* CurrentPrcb;
	struct _KPRCB* AffinityPrcb;
	BYTE IdlePriorityClass;
	BYTE NormalPriorityClass;
	BYTE TimeCriticalPriorityClass;
	BYTE HasAsyncTerminated;
	DWORD ActiveTimerListLock;
	void * StackAllocatedBase;
	KAPC SuspendApc;
	KSEMAPHORE SuspendSemaphore;
	LIST_ENTRY ThreadListEntry;
	DWORD Padding2;
	PKQUEUE Queue;
	LIST_ENTRY QueueListEntry;
	void  * UserModeDispatcher; // function *
	PKTRAP_FRAME UserModeTrapFrame;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER ExitTime;
	long ExitStatus;
	LIST_ENTRY ActiveTimerListHead;
	void * ThreadId;
	void  * StartAddress; // function *
	LIST_ENTRY IrpList;
	void * DebugMonitorData;
	DWORD LastWin32ErrorCode;
	void * Win32CurrentFiber;
	DWORD Padding3;
	DWORD CreateOptions;
	float Vscr[4];
	float Vr[4][128];
	double Fpscr;
	double Fpr[32];
	KAPC TerminateApc;
} KTHREAD, *PKTHREAD; // 2736

// *********** PACKING ENDS HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS HERE **************//

typedef struct _KPRCB{
	PKTHREAD CurrentThread;
	PKTHREAD NextThread;
	PKTHREAD IdleThread;
	BYTE Number;
	DWORD SetMember;
	DWORD DpcTime;
	DWORD InterruptTime;
	DWORD InterruptCount;
	volatile DWORD IpiFrozen;
	volatile void * CurrentPacket[3];
	volatile DWORD TargetSet;
	volatile void * WorkerRoutine; // function *
	struct _KPRCB * SignalDone;
	volatile DWORD RequestSummary;
	DWORD DpcInterruptRequested;
	DWORD DpcLock;
	LIST_ENTRY DpcListHead;
	DWORD DpcRoutineActive;
	DWORD ReadyListLock;
	DWORD IdleThreadActive;
	SINGLE_LIST_ENTRY DeferredReadyListHead;
	DWORD ReadySummary;
	DWORD ReadySummaryMask;
	LIST_ENTRY DispatcherReadyListHead[32];
	KDPC ThreadReaperDpc;
	LIST_ENTRY ThreadReaperListHead;
	KDPC SwitchProcessorThreadDpc;
} KPRCB, *PKPRCB; // 424



// *********** PACKING STARTS AGAIN HERE **************//
#pragma pack(push, 1)
// *********** PACKING STARTS AGAIN HERE **************//



typedef struct _KPCR{
	PVOID TlsData;
	union{
		struct{
		USHORT MsrEnableMaskHigh;
		USHORT MsrEnableMaskLow;
		};
		DWORD MsrEnableMask;
	};
	union{
		struct{
			BYTE DispatchInterrupt;
			BYTE ApcInterrupt;
		} SIAsBytes;
		USHORT SoftwareInterrupt;
	};
	union{
		struct{
			BYTE DpcFpuStateSaved;
			BYTE DpcVpuStateSaved;
		} DpcAsBytes;
		USHORT DpcFpuVpuStateSaved;
	};
	BYTE DpcCurrentProcessType;
	BYTE QuantumEnd;
	BYTE TimerRequest;
	BYTE HvCr0Save;
	PKTHREAD FpuOwnerThread;
	PKTHREAD VpuOwnerThread;
	BYTE CurrentIrql;
	BYTE BackgroundSchedulingActive;
	union{
		struct{
			BYTE StartBackgroundScheduling;
			BYTE StopBackgroundScheduling;
		} StartStopAsBytes;
		USHORT StartStopBackgroundScheduling;
	};
	DWORD TimerHand;
	union{
		struct{
			ULONGLONG LrIarSave;
			ULONGLONG CrMsrSave;
			ULONGLONG Gpr13Save;
		} gpSave;
		struct{
			DWORD Gpr1Restore;
			DWORD IarRestore;
			DWORD CrRestore;
			DWORD MsrRestore;
		} gpRest;
	};
	ULONGLONG HvGpr1Save;
	ULONGLONG HvGpr3Save;
	ULONGLONG HvGpr4Save;
	ULONGLONG HvGpr5Save;
	DWORD UserModeControl;
	void * PanicStack;
	DWORD DarSave;
	DWORD DsisrSave;
	void * DbgLastDpcRoutine;
	DWORD OnInterruptStack;
	void * StackBase;
	void * StackLimit;
	void * InterruptStackBase;
	void * InterruptStackLimit;
	void * InterruptRoutine[32];
	KPRCB PrcbData;
	PKPRCB Prcb;
	DWORD Unused;
	DWORD * PixCurrent;
	DWORD * PixLimit;
	DWORD * ProfilerCurrent;
	DWORD * ProfilerLimit;
	DWORD ProfilerFlags;
	ULONGLONG Contention;
	DWORD * MonitorProfileData;
}KPCR, *PKPCR; // 728? adds up to 724

typedef struct _KPCR_PAGE{
	union{
		struct{
			KPCR Pcr;
			DWORD IdleThreadData[ANYSIZE_ARRAY]; // 4096 - 728 ?
		} AsSeparate;
		BYTE PcrAsUCHARs[4096];
	};
} KPCR_PAGE, *PKPCR_PAGE; // 4096


// *********** PACKING ENDS AGAIN HERE **************//
#pragma pack(pop)
// *********** PACKING ENDS AGAIN HERE **************//



//C_ASSERT(sizeof(KPCR_PAGE) == 4096);
//C_ASSERT(sizeof(KSEMAPHORE) == 20);
//C_ASSERT(sizeof(KTIMER) == 40);
//C_ASSERT(sizeof(DISPATCHER_HEADER) == 16);
//C_ASSERT(sizeof(STACK_FRAME_HEADER) == 80);
//C_ASSERT(sizeof(KDPC) == 28);
//C_ASSERT(sizeof(KWAIT_BLOCK) == 24);
//C_ASSERT(sizeof(KPROCESS) == 96);
//C_ASSERT(sizeof(KQUEUE) == 40);
//C_ASSERT(sizeof(KPCR) == 724); // was 728???
//C_ASSERT(sizeof(KPRCB) == 424);
//C_ASSERT(sizeof(KTRAP_FRAME) == 448);
//C_ASSERT(sizeof(KTHREAD) == 2736);
//C_ASSERT(sizeof(KINTERRUPT) == 20);
//C_ASSERT(sizeof(KEVENT) == 16);
//C_ASSERT(sizeof(DISPATCHER_HEADER) == 16);
//C_ASSERT(sizeof(KAPC) == 40);



#endif	//_KERNELP_DEFINES_H
