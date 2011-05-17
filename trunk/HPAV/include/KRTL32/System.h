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

	/* 获得CPU的核数 */
	static int GetProcessorNumber(void);

	/* 获得CPU使用率 */
	int GetProcessorUsage(void);

	/* 获取CPU的频率 */
	static unsigned long GetProcessorFrequency(void);

	/* 获取内存总大小 */
	static unsigned long GetTotalMemorySize(void);

	/* 获取虚拟内存总大小 */
	static unsigned long GetTotalVirtualMemorySize(void);

	/* 获取页面文件总大小 */
	static unsigned long GetTotalPageFileSize(void);

	/* 获取可用内存大小 */
	static unsigned long GetAvailableMemorySize(void);

	/* 获取可用虚拟内存大小 */
	static unsigned long GetAvailableVirtualMemorySize(void);

	/* 获取可用页面文件大小 */
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
