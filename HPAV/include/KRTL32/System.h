#pragma once

typedef struct
{
	DWORD   dwUnknown1;
	ULONG   uKeMaximumIncrement;
	ULONG   uPageSize;
	ULONG   uMmNumberOfPhysicalPages;
	ULONG   uMmLowestPhysicalPage;
	ULONG   uMmHighestPhysicalPage;
	ULONG   uAllocationGranularity;
	PVOID   pLowestUserAddress;
	PVOID   pMmHighestUserAddress;
	ULONG   uKeActiveProcessors;
	BYTE    bKeNumberProcessors;
	BYTE    bUnknown2;
	WORD    wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
	LARGE_INTEGER   liIdleTime;
	DWORD           dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liExpTimeZoneBias;
	ULONG         uCurrentTimeZoneId;
	DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;


// ntdll!NtQuerySystemInformation (NT specific!)
//
// The function copies the system information of the
// specified type into a buffer
//
// NTSYSAPI
// NTSTATUS
// NTAPI
// NtQuerySystemInformation(
//    IN UINT SystemInformationClass,    // information type
//    OUT PVOID SystemInformation,       // pointer to buffer
//    IN ULONG SystemInformationLength,  // buffer size in bytes
//    OUT PULONG ReturnLength OPTIONAL   // pointer to a 32-bit
//                                       // variable that receives
//                                       // the number of bytes
//                                       // written to the buffer 
// );
typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KSystem
{
public:
	KSystem(void);
	virtual ~KSystem(void);

	/* ���CPU�ĺ��� */
	static int GetProcessorNumber(void);

	/* ���CPUʹ���� */
	int GetProcessorUsage(void);

	/* ��ȡCPU��Ƶ�� */
	static unsigned long GetProcessorFrequency(void);

	/* ��ȡ�ڴ��ܴ�С */
	static unsigned long GetTotalMemorySize(void);

	/* ��ȡ�����ڴ��ܴ�С */
	static unsigned long GetTotalVirtualMemorySize(void);

	/* ��ȡҳ���ļ��ܴ�С */
	static unsigned long GetTotalPageFileSize(void);

	/* ��ȡ�����ڴ��С */
	static unsigned long GetAvailableMemorySize(void);

	/* ��ȡ���������ڴ��С */
	static unsigned long GetAvailableVirtualMemorySize(void);

	/* ��ȡ����ҳ���ļ���С */
	static unsigned long GetAvailablePageFileSize(void);

protected:
	PROCNTQSI						NtQuerySystemInformation;
    SYSTEM_PERFORMANCE_INFORMATION	SysPerfInfo;
    SYSTEM_TIME_INFORMATION			SysTimeInfo;
    SYSTEM_BASIC_INFORMATION		SysBaseInfo;
    double							dbIdleTime;
    double							dbSystemTime;
    LONG							status;
    LARGE_INTEGER					liOldIdleTime;
    LARGE_INTEGER					liOldSystemTime;
};
