#pragma once
#include "XeCrypt.h"
#include "kernelp.h"

typedef unsigned long long QWORD;
typedef long							NTSTATUS;
#define NT_EXTRACT_ST(Status)			((((ULONG)(Status)) >> 30)& 0x3)
#define NT_SUCCESS(Status)              (((NTSTATUS)(Status)) >= 0)
#define NT_INFORMATION(Status)          (NT_EXTRACT_ST(Status) == 1)
#define NT_WARNING(Status)              (NT_EXTRACT_ST(Status) == 2)
#define NT_ERROR(Status)                (NT_EXTRACT_ST(Status) == 3)

// IRQL values
#define PASSIVE_LEVEL 0
#define LOW_LEVEL 0
#define APC_LEVEL 1
#define DISPATCH_LEVEL 2

// Create disposition values.
#define FILE_SUPERSEDE                          0x00000000
#define FILE_OPEN                               0x00000001
#define FILE_CREATE                             0x00000002
#define FILE_OPEN_IF                            0x00000003
#define FILE_OVERWRITE                          0x00000004
#define FILE_OVERWRITE_IF                       0x00000005
#define FILE_MAXIMUM_DISPOSITION                0x00000005

// Create/open option flags.

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
#define FILE_OPEN_REMOTE_INSTANCE               0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000

typedef enum _FS_INFORMATION_CLASS {
    FileFsVolumeInformation=1,
    FileFsLabelInformation,
    FileFsSizeInformation,
    FileFsDeviceInformation,
    FileFsAttributeInformation,
    FileFsControlInformation,
    FileFsFullSizeInformation,
    FileFsObjectIdInformation,
    FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

typedef enum _FILE_INFORMATION_CLASS {
   FileDirectoryInformation = 1,
   FileFullDirectoryInformation,
   FileBothDirectoryInformation,
   FileBasicInformation,
   FileStandardInformation,
   FileInternalInformation,
   FileEaInformation,
   FileAccessInformation,
   FileNameInformation,
   FileRenameInformation,
   FileLinkInformation,
   FileNamesInformation,
   FileDispositionInformation,
   FilePositionInformation,
   FileFullEaInformation,
   FileModeInformation,
   FileAlignmentInformation,
   FileAllInformation,
   FileAllocationInformation,
   FileEndOfFileInformation,
   FileAlternateNameInformation,
   FileStreamInformation,
   FilePipeInformation,
   FilePipeLocalInformation,
   FilePipeRemoteInformation,
   FileMailslotQueryInformation,
   FileMailslotSetInformation,
   FileCompressionInformation,
   FileObjectIdInformation,
   FileCompletionInformation,
   FileMoveClusterInformation,
   FileQuotaInformation,
   FileReparsePointInformation,
   FileNetworkOpenInformation,
   FileAttributeTagInformation,
   FileTrackingInformation,
   FileIdBothDirectoryInformation,
   FileIdFullDirectoryInformation,
   FileValidDataLengthInformation,
   FileShortNameInformation,
   FileIoCompletionNotificationInformation,
   FileIoStatusBlockRangeInformation,
   FileIoPriorityHintInformation,
   FileSfioReserveInformation,
   FileSfioVolumeInformation,
   FileHardLinkInformation,
   FileProcessIdsUsingFileInformation,
   FileNormalizedNameInformation,
   FileNetworkPhysicalNameInformation,
   FileIdGlobalTxDirectoryInformation,
   FileIsRemoteDeviceInformation,
   FileAttributeCacheInformation,
   FileNumaNodeInformation,
   FileStandardLinkInformation,
   FileRemoteProtocolInformation,
   FileMaximumInformation
 } FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_FS_SIZE_INFORMATION {
  LARGE_INTEGER TotalAllocationUnits;
  LARGE_INTEGER AvailableAllocationUnits;
  ULONG         SectorsPerAllocationUnit;
  ULONG         BytesPerSector;
} FILE_FS_SIZE_INFORMATION, *PFILE_FS_SIZE_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION {
  LARGE_INTEGER           CreationTime;
  LARGE_INTEGER           LastAccessTime;
  LARGE_INTEGER           LastWriteTime;
  LARGE_INTEGER           ChangeTime;
  LARGE_INTEGER           AllocationSize;
  LARGE_INTEGER           EndOfFile;
  ULONG                   FileAttributes;
  ULONG                   Unknown;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

typedef struct _ANSI_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR Buffer;
} ANSI_STRING, *PANSI_STRING;

typedef struct _FILE_DISPOSITION_INFORMATION {
  BOOLEAN  DeleteFile;
} FILE_DISPOSITION_INFORMATION;

typedef struct _FILE_RENAME_INFORMATION {
  BOOLEAN ReplaceIfExists;
  HANDLE  RootDirectory;
  ANSI_STRING FileName;
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef struct _XEX_HEADER_STRING {
	ULONG Size;
	UCHAR Data[1];
} XEX_HEADER_STRING, *PXEX_HEADER_STRING;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWCHAR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef void (*pfnTitleTerminateRoutine)();
typedef struct _EX_TITLE_TERMINATE_REGISTRATION {
	pfnTitleTerminateRoutine	NotificationRoutine;
	DWORD						Priority;
	LIST_ENTRY					ListEntry;
} EX_TITLE_TERMINATE_REGISTRATION, *PEX_TITLE_TERMINATE_REGISTRATION;

typedef struct _EX_THREAD_REGISTRATION *PEX_THREAD_REGISTRATION;
typedef void (*pfnThreadNotificationRoutine)(PEX_THREAD_REGISTRATION ThisRegistration, PKTHREAD Thread, BOOL Creating);
typedef struct _EX_THREAD_REGISTRATION {
	pfnThreadNotificationRoutine	NotificationRoutine;
	DWORD							Priority;
	LIST_ENTRY						ListEntry;
} EX_THREAD_REGISTRATION;

typedef struct _XEX_IMPORT_DESCRIPTOR {
   DWORD Size;
   DWORD NameTableSize;
   DWORD ModuleCount;
} XEX_IMPORT_DESCRIPTOR, *PXEX_IMPORT_DESCRIPTOR;

typedef struct _HV_IMAGE_IMPORT_TABLE {
   BYTE  NextImportDigest[0x14];
   DWORD ModuleNumber;
   DWORD Version[0x02];
   BYTE  Unused;
   BYTE  ModuleIndex;
   WORD  ImportCount;
} HV_IMAGE_IMPORT_TABLE, *PHV_IMAGE_IMPORT_TABLE;

typedef struct _XEX_IMPORT_TABLE {
   DWORD                 TableSize;
   HV_IMAGE_IMPORT_TABLE ImportTable;
} XEX_IMPORT_TABLE, *PXEX_IMPORT_TABLE;

typedef struct _LDR_DATA_TABLE_ENTRY { 
	LIST_ENTRY     InLoadOrderLinks;
	LIST_ENTRY     InClosureOrderLinks;
	LIST_ENTRY     InInitializationOrderLinks;
	VOID*          NtHeadersBase;
	VOID*          ImageBase;
	DWORD          SizeOfNtImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	DWORD          Flags;
	DWORD          SizeOfFullImage;
	VOID*          EntryPoint;
	WORD           LoadCount;
	WORD           ModuleIndex;
	VOID*          DllBaseOriginal;
	DWORD          CheckSum;
	DWORD          ModuleLoadFlags;
	DWORD          TimeDateStamp;
	VOID*          LoadedImports;
	VOID*          XexHeaderBase;
	union {
		ANSI_STRING               LoadFileName;
		struct {
			struct _LDR_DATA_TABLE_ENTRY* ClosureRoot;
			struct _LDR_DATA_TABLE_ENTRY* TraversalParent;
		} asEntry;
	};
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _XBOX_HARDWARE_INFO {
	DWORD Flags;
	BYTE  NumberOfProcessors;
	BYTE  PCIBridgeRevisionID;
	BYTE  Reserved[6];
	WORD  BldrMagic;
	WORD  BldrFlags;
} XBOX_HARDWARE_INFO, *PXBOX_HARDWARE_INFO;

typedef struct _KERNEL_VERSION {
	WORD Major;
	WORD Minor;
	WORD Build;
	BYTE ApprovalType;
	BYTE QFE;
} KERNEL_VERSION, *PKERNEL_VERSION;

typedef struct _D3DPRIVATE_RECT {
	LONG x1, y1;
	LONG x2, y2;
} D3DPRIVATE_RECT, *PD3DPRIVATE_RECT;

typedef struct _D3DFILTER_PARAMETERS {
	FLOAT Nyquist;
	FLOAT FlickerFilter;
	FLOAT Beta;
} D3DFILTER_PARAMETERS, *PD3DFILTER_PARAMETERS;

typedef struct _D3DPRIVATE_SCALER_PARAMETERS {
	D3DPRIVATE_RECT		 ScalerSourceRect;
	LONG				 ScaledOutputWidth;
	LONG				 ScaledOutputHeight;
	DWORD				 VerticalFilterType;
	D3DFILTER_PARAMETERS VerticalFilterParameters;
	DWORD				 HorizontalFilterType;
	D3DFILTER_PARAMETERS HorizontalFilterParameters;
} D3DPRIVATE_SCALER_PARAMETERS, *PD3DPRIVATE_SCALER_PARAMETERS;

typedef struct _DISPLAY_INFORMATION {
	USHORT						 FrontBufferWidth;
	USHORT						 FrontBufferHeight;
	CHAR						 FrontBufferColorFormat;
	CHAR						 FrontBufferPixelFormat;
	D3DPRIVATE_SCALER_PARAMETERS ScalerParameters;
	USHORT						 DisplayWindowOverscanLeft;
	USHORT						 DisplayWindowOverscanTop;
	USHORT						 DisplayWindowOverscanRight;
	USHORT						 DisplayWindowOverscanBottom;
	USHORT						 DisplayWidth;
	USHORT						 DisplayHeight;
	FLOAT						 DisplayRefreshRate;
	UINT						 DisplayInterlaced;
	CHAR						 DisplayColorFormat;
	USHORT						 ActualDisplayWidth;
} DISPLAY_INFORMATION, *PDISPLAY_INFORMATION;

typedef struct _XEX_EXECUTION_ID {
	DWORD		 MediaID;
	DWORD		 Version;
	DWORD		 BaseVersion;
	union {
		struct {
			WORD PublisherID;
			WORD GameID;
		};
		DWORD	 TitleID;
	};
	BYTE		 Platform;
	BYTE		 ExecutableType;
	BYTE		 DiscNum;
	BYTE		 DiscsInSet;
	DWORD		 SaveGameID;
} XEX_EXECUTION_ID, *PXEX_EXECUTION_ID;

// Valid values for the Attributes field
#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_VALID_ATTRIBUTES    0x000001F2L

typedef struct _OBJECT_ATTRIBUTES {
    HANDLE		 RootDirectory;
	PANSI_STRING ObjectName;
    ULONG		 Attributes;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

// object type strings
#define OBJ_TYP_SYMBLINK	0x626d7953
#define OBJ_TYP_DIRECTORY	0x65726944
#define OBJ_TYP_DEVICE		0x69766544
#define OBJ_TYP_EVENT       0x76657645
#define OBJ_TYP_DEBUG       0x63706d64

typedef struct _OBJECT_DIRECTORY_INFORMATION {
	ANSI_STRING Name;
	DWORD		Type;
	CHAR		NameEx[MAX_PATH];
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID	 Pointer;
    } st;
    ULONG_PTR	 Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PIO_APC_ROUTINE) (
    IN PVOID ApcContext,
    IN PIO_STATUS_BLOCK IoStatusBlock,
    IN ULONG Reserved
);

typedef struct _FILE_DIRECTORY_INFORMATION {
	ULONG		  NextEntryOffset; 
	ULONG		  FileIndex; 
	LARGE_INTEGER CreationTime; 
	LARGE_INTEGER LastAccessTime; 
	LARGE_INTEGER LastWriteTime; 
	LARGE_INTEGER ChangeTime; 
	LARGE_INTEGER EndOfFile; 
	LARGE_INTEGER AllocationSize; 
	ULONG		  FileAttributes; 
	ULONG		  FileNameLength; 
	CHAR		  FileName[MAX_PATH];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct FILE_BASIC_INFORMATION {
  LARGE_INTEGER  CreationTime;
  LARGE_INTEGER  LastAccessTime;
  LARGE_INTEGER  LastWriteTime;
  LARGE_INTEGER  ChangeTime;
  ULONG  FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _TRANSLATE_SYMLINK
{
	DWORD reserved;
	PANSI_STRING name;
} TRANSLATE_SYMLINK, *PTRANSLATE_SYMLINK;

typedef struct _DRIVER_OBJECT
{
	DWORD Unk[3];
	LPVOID Create;
	LPVOID Close; // This appears to be when files are closed?
	LPVOID Read;
	LPVOID Write;
	LPVOID QueryInformation;
	LPVOID SetInformation;
	LPVOID FlushBuffers;
	LPVOID QueryVolumeInformation;
	LPVOID DirectoryControl;
	LPVOID Unk2;
	LPVOID CloseHandle; // This appears to be when handles are closed
} DRIVER_OBJECT, *PDRIVER_OBJECT;

#define InitializeObjectAttributes( p, n, a, r){ \
	(p)->RootDirectory = r;                             \
	(p)->Attributes = a;                                \
	(p)->ObjectName = n;                                \
}

NTSTATUS ExGetXConfigSetting(USHORT Category, USHORT Entry, LPVOID Buffer, DWORD cchBuffer, LPDWORD cchOutBuffer);
NTSTATUS ExSetXConfigSetting(USHORT Category, USHORT Entry, LPVOID Buffer, DWORD cchBuffer);

extern XBOX_HARDWARE_INFO*	  XboxHardwareInfo;
extern KERNEL_VERSION*		  XboxKrnlVersion;
extern KERNEL_VERSION*		  XboxKrnlBaseVersion;
extern PLDR_DATA_TABLE_ENTRY* XexExecutableModuleHandle;
extern CONST LPCSTR			  ExLoadedImageName;
extern DWORD				  ObDirectoryObjectType;
extern DWORD				  ObSymbolicLinkObjectType;
extern DWORD                  IoDeviceObjectType;
extern DWORD*				  KeDebugMonitorData;

extern DWORD *KeTimeStampBundle;

void KeQuerySystemTime(PULARGE_INTEGER Time);
VOID VdGetCurrentDisplayInformation(PDISPLAY_INFORMATION DisplayInfo);
DWORD KeGetCurrentProcessType();

void ExRegisterTitleTerminateNotification(PEX_TITLE_TERMINATE_REGISTRATION pRegistration, BOOL Register);
void ExRegisterThreadNotification(PEX_THREAD_REGISTRATION pRegistration, BOOL Register);

void RtlInitAnsiString(PANSI_STRING DestinationString, const char* SourceString);

PIMAGE_NT_HEADERS RtlImageNtHeader(PVOID ModuleAddress);
PVOID RtlImageDirectoryEntryToData(PVOID BaseAddress, BOOL MappedAsImage, USHORT Directory, PULONG Size);

void*	RtlImageXexHeaderField(void* XexHeaderBase, DWORD Key);
HRESULT XexStartExecutable(FARPROC TitleProcessInitThreadProc);
BOOL	XexCheckExecutablePrivilege(DWORD Privilege);

NTSTATUS XexGetModuleHandle(LPCSTR XexName, HMODULE *ModuleHandle);
NTSTATUS XexGetProcedureAddress(HMODULE ModuleHandle, DWORD dwOrdinal, PVOID OutAddress);
NTSTATUS ObCreateSymbolicLink(PANSI_STRING, PANSI_STRING);
NTSTATUS ObDeleteSymbolicLink(PANSI_STRING);
NTSTATUS ObTranslateSymbolicLink(IN PVOID, OUT PANSI_STRING);
NTSTATUS ObOpenObjectByPointer(PVOID Object, PHANDLE Handle);
NTSTATUS NtOpenSymbolicLinkObject(PHANDLE LinkHandle, POBJECT_ATTRIBUTES ObjectAttributes);
NTSTATUS NtQuerySymbolicLinkObject(HANDLE LinkHandle, PANSI_STRING LinkTarget, PULONG ReturnedLength);
NTSTATUS NtQueryVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileSystemInformation, ULONG Length, FS_INFORMATION_CLASS FileSystemInformationClass); //FILE_FS_SIZE_INFORMATION NormalSizeInfo);
NTSTATUS NtClose(HANDLE Handle);

NTSTATUS NtQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, 
	PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);

NTSTATUS XeKeysGetKey(DWORD KeyNum, void* KeyBuffer, DWORD* KeySize);
NTSTATUS XeKeysSetKey(DWORD KeyNum, void* KeyBuffer, DWORD* KeySize);
NTSTATUS XeKeysGetConsoleID(void* KeyBuffer, char* KeyString);

BOOL MmIsAddressValid(VOID* Address);
PVOID MmCreateKernelStack(DWORD Size, DWORD Type);
DWORD MmGetPhysicalAddress(VOID* Address);

void HalReturnToFirmware(DWORD);

void  XapiThreadStartup(void (__cdecl *StartRoutine)(void*), void* StartContext);
DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, 
	LPDWORD lpThreadId, VOID* apiThreadStartup , 
	LPTHREAD_START_ROUTINE lpStartAddress, 
	LPVOID lpParameter, DWORD dwCreationFlagsMod);

HRESULT HalOpenCloseODDTray(BOOL Open);

NTSTATUS NtSetSystemTime(IN PULARGE_INTEGER SystemTime, OUT PULARGE_INTEGER PreviousTime OPTIONAL);

NTSTATUS NtCreateFile(HANDLE* FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, 
	ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);

NTSTATUS NtOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions); 

NTSTATUS NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, 
	PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, PANSI_STRING FileMask, PVOID Unk);

NTSTATUS NtQueryFullAttributesFile(POBJECT_ATTRIBUTES ObjectAttributes, PFILE_NETWORK_OPEN_INFORMATION Attributes );

NTSTATUS NtReadFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, 
	PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset);
NTSTATUS NtWriteFile(HANDLE FileHandle, IN HANDLE Event OPTIONAL, IN PIO_APC_ROUTINE ApcRoutine OPTIONAL, IN PVOID ApcContext OPTIONAL,
	OUT PIO_STATUS_BLOCK IoStatusBlock, IN PVOID Buffer, IN ULONG Length, IN PLARGE_INTEGER ByteOffset OPTIONAL);

NTSTATUS NtOpenDirectoryObject(PHANDLE DirectoryHandle, POBJECT_ATTRIBUTES ObjectAttributes);

NTSTATUS NtQueryDirectoryObject(HANDLE DirectoryHandle, PVOID Buffer, ULONG Length, 
	BOOLEAN ReturnSingleEntry, PULONG Context, PULONG ReturnLength);

NTSTATUS NtSetInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock,
	PVOID FileInformation, ULONG Length, DWORD FileInformationClass);

NTSTATUS NtClose(HANDLE Handle);

NTSTATUS IoCreateDevice(PDRIVER_OBJECT DriverObject, ULONG DeviceExtensionSize, PANSI_STRING DeviceName,
	DWORD DeviceType, ULONG DeviceCharacteristics, LPDWORD *DeviceObject);
NTSTATUS IoInvalidDeviceRequest();

UINT32 __stdcall XexLoadExecutable(char* xexName, PHANDLE handle, UINT32 typeInfo, UINT32 ver);
UINT32 __stdcall XexLoadImageFromMemory(char* XexBuffer, DWORD Size, char* xexName, DWORD Flags, DWORD MinVersion, HMODULE* Module);

DWORD KeSuspendThread(HANDLE hThread);

PVOID ExAllocatePoolWithTag(SIZE_T NumberOfBytes, ULONG Tag);
PVOID ExAllocatePoolTypeWithTag(SIZE_T NumberOfBytes, ULONG Tag, ULONG Type);
VOID ExFreePool(PVOID P);
	
DWORD KeResumeThread(HANDLE hThread);
	
HRESULT ObLookupAnyThreadByThreadId(DWORD dwThreadId, PKTHREAD *pthr);
	
VOID ObDereferenceObject(PVOID Object);
NTSTATUS ObReferenceObjectByHandle(HANDLE Handle, DWORD ObjectType, PVOID *Object);

BYTE KfRaiseIrql(BYTE irql);
BYTE KeRaiseIrqlToDpcLevel();
VOID KfLowerIrql(BYTE Irql);
VOID KeEnterCriticalRegion();
VOID KeLeaveCriticalRegion();
BYTE KfAcquireSpinLock(LPVOID Object);
VOID KfReleaseSpinLock(LPVOID Object, BYTE Irql);
VOID KeAcquireSpinLockAtRaisedIrql(LPVOID Object);
VOID KeReleaseSpinLockFromRaisedIrql(LPVOID Object);
NTSTATUS ObCreateObject(PVOID ObjectType, POBJECT_ATTRIBUTES ObjectAttributes, DWORD Unknown, PVOID *Object);
NTSTATUS ObInsertObject(PVOID Object, POBJECT_ATTRIBUTES ObjectAttributes, DWORD Unk, PHANDLE Handle);
VOID IoDeleteDevice(PVOID Object);

NTSTATUS NtCreateDirectoryObject(PHANDLE DirectoryHandle, POBJECT_ATTRIBUTES ObjectAttributes);

BOOL ExTerminateThread(DWORD ReturnCode);

BOOL KeSetEvent(HANDLE Event, DWORD Increment, BOOL Wait);
VOID KeResetEvent(HANDLE Event);
VOID KeSetBasePriorityThread(PKTHREAD Thread, DWORD Priority);

VOID KeSweepIcacheRange(PVOID Address, DWORD cbBytes);

INT KeQueryBasePriorityThread(PVOID pThread);

NTSTATUS ObReferenceObjectByName(PANSI_STRING ObjectName, ULONG Attributes, DWORD ObjectType, DWORD Unk, PVOID *Object);
NTSTATUS IoCompleteRequest(PVOID IoRequest, DWORD Unk);

VOID IoSetShareAccess(ACCESS_MASK DesiredAccess, ULONG DesiredShareAccess, PVOID FileObject, PVOID ShareAccess);

PVOID MmDbgReadCheck(PVOID pAddress);
PVOID MmDbgWriteCheck(PVOID pAddress, PHANDLE pHandle);

VOID MmDbgReleaseAddress(PVOID pAddress, PHANDLE pHandle);

VOID KeSetSpecialPurposeRegister(DWORD dwRegister, ULONGLONG ulValue);

ULONG_PTR KeIpiGenericCall(LPVOID BroadcastFunction, ULONG_PTR Context);

VOID KeStallExecutionProcessor(DWORD);

NTSTATUS KeWaitForSingleObject(PVOID Object, DWORD WaitReason, DWORD WaitMode, BOOL Alertable, PLARGE_INTEGER Timeout);

PVOID XexPcToFileHeader(PVOID address, PLDR_DATA_TABLE_ENTRY* ldatOut);

VOID KeInitializeEvent(PKEVENT Event, DWORD Type, BOOL State);

HRESULT RtlNtStatusToDosError(NTSTATUS Status);

VOID VdDisplayFatalError(DWORD Error);

typedef struct _FILE_OBJECT
{
	WORD Type;			// 00
	WORD Size;			// 02
	PVOID DeviceObject;	// 04
	PVOID CustomData;	// 08
} FILE_OBJECT, *PFILE_OBJECT;

typedef struct _PARAMS_EVERYWHERE
{
	DWORD Unk[18];			// 00 - 44
	PANSI_STRING FileName;	// 48
} PARAMS_EVERYWHERE, *PPARAMS_EVERYWHERE;

typedef struct _MORE_DRIVER_PARAMS
{
	DWORD Unk;							// 00
	union {
		struct {
			DWORD dwDesiredAccess;				// 04
			BYTE bCreationDisposition;			// 08
			BYTE Unk2;							// 09
			WORD wCreateOptions;				// 0A
			DWORD Unk3;							// 0C
		} CreateFile;
		struct {
			DWORD dwBytesRequested;
		} ReadFile;
	};
	PANSI_STRING FileName;				// 10
	DWORD Unk4;							// 14
	PFILE_OBJECT FileObject;			// 18
										// 1c
} MORE_DRIVER_PARAMS, *PMORE_DRIVER_PARAMS;

typedef struct _DRIVER_PARAMS
{
	DWORD Unk[4];					// 00
									// 04
									// 08
									// 0C
	NTSTATUS Status;				// 10
	DWORD BytesRead;				// 14
	DWORD Unk2;						// 18
	PVOID DataBuffer;				// 1C
	DWORD Unk3[12];					// 20
									// 24
									// 28
									// 2c
									// 30
									// 34
									// 38
									// 3c
									// 40
									// 44
									// 48
									// 4c
	PMORE_DRIVER_PARAMS MoreParams;	// 50
} DRIVER_PARAMS, *PDRIVER_PARAMS;

#ifndef InitializeListHead
//
//  VOID
//  InitializeListHead(
//      PLIST_ENTRY ListHead
//      );
//

#define InitializeListHead(ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = (ListHead))

//
//  BOOLEAN
//  IsListEmpty(
//      PLIST_ENTRY ListHead
//      );
//

#define IsListEmpty(ListHead) \
    ((ListHead)->Flink == (ListHead))

//
//  PLIST_ENTRY
//  RemoveHeadList(
//      PLIST_ENTRY ListHead
//      );
//

#define RemoveHeadList(ListHead) \
    (ListHead)->Flink;\
    {RemoveEntryList((ListHead)->Flink)}

//
//  PLIST_ENTRY
//  RemoveTailList(
//      PLIST_ENTRY ListHead
//      );
//

#define RemoveTailList(ListHead) \
    (ListHead)->Blink;\
    {RemoveEntryList((ListHead)->Blink)}

//
//  VOID
//  RemoveEntryList(
//      PLIST_ENTRY Entry
//      );
//

#define RemoveEntryList(Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_Flink;\
    _EX_Flink = (Entry)->Flink;\
    _EX_Blink = (Entry)->Blink;\
    _EX_Blink->Flink = _EX_Flink;\
    _EX_Flink->Blink = _EX_Blink;\
    }

//
//  VOID
//  InsertTailList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertTailList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Blink = _EX_ListHead->Blink;\
    (Entry)->Flink = _EX_ListHead;\
    (Entry)->Blink = _EX_Blink;\
    _EX_Blink->Flink = (Entry);\
    _EX_ListHead->Blink = (Entry);\
    }

//
//  VOID
//  InsertHeadList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertHeadList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Flink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Flink = _EX_ListHead->Flink;\
    (Entry)->Flink = _EX_Flink;\
    (Entry)->Blink = _EX_ListHead;\
    _EX_Flink->Blink = (Entry);\
    _EX_ListHead->Flink = (Entry);\
    }

#endif  // InitializeListHead