#include "Util.h"
#include "Definitions.h"
#include "Structs.h"
#include "Logger.h"

UNICODE_STRING ToUnicodeString(LPCSTR string)
{
	UNICODE_STRING unicodeString;
	RtlInitUnicodeString(&unicodeString, NULL);

	ANSI_STRING ansiString;
	RtlInitAnsiString(&ansiString, string);

	NTSTATUS status = RtlAnsiStringToUnicodeString(&unicodeString, &ansiString, TRUE);
	if (!NT_SUCCESS(status))
		return unicodeString;
	
	return unicodeString;
}

PVOID GetSystemRoutineAddress(LPCSTR routineName)
{
	UNICODE_STRING unicodeRoutineName = ToUnicodeString(routineName);
	void* routineAddress = MmGetSystemRoutineAddress(&unicodeRoutineName);
	RtlFreeUnicodeString(&unicodeRoutineName);
	return routineAddress;
}


NTSTATUS QuerySystemInformation(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, ULONG* returnLength)
{
	ULONG tempReturnLength;
	NTSTATUS status = ZwQuerySystemInformation(systemInformationClass, systemInformation, systemInformationLength, &tempReturnLength);
	if (returnLength != NULL)
		*returnLength = tempReturnLength;

	return status;
}

NTSTATUS QuerySystem(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID* systemInformation)
{
	if (!systemInformation)
		return STATUS_INTERNAL_ERROR;

	ULONG bufferSize = 0;
	PVOID buffer = NULL;
	NTSTATUS status;

	do
	{
		if (buffer)
			ExFreePool(buffer);

		bufferSize *= 2;
		buffer = ExAllocatePoolWithTag(PagedPool, bufferSize, 'kami');

		if (!buffer)
			return STATUS_INSUFFICIENT_RESOURCES;

		status = ZwQuerySystemInformation(systemInformationClass, buffer, bufferSize, &bufferSize);
	} while (status == STATUS_INFO_LENGTH_MISMATCH);

	if (!NT_SUCCESS(status)) 
	{
		ExFreePool(buffer);
		return status;
	}

	status = QuerySystemInformation(systemInformationClass, buffer, bufferSize, NULL);

	*systemInformation = buffer;

	return status;
}


NTSTATUS QueryHandles()
{
	PSYSTEM_HANDLE_INFORMATION systemHandleInformationBuffer = NULL;
	NTSTATUS status;

	status = QuerySystem(SystemHandleInformation, (PVOID*) & systemHandleInformationBuffer);

	if (!NT_SUCCESS(status))
		return status;

	if (!systemHandleInformationBuffer)
		return STATUS_INTERNAL_ERROR;

	for (auto i = 0; i < systemHandleInformationBuffer->NumberOfHandles; i++)
	{
		HANDLE handle = (HANDLE)systemHandleInformationBuffer->Handles[i].HandleValue;

		
		ULONG pid = systemHandleInformationBuffer->Handles[i].UniqueProcessId;
		if (pid != 4)
			continue;
		

		PEPROCESS process;
		status = PsLookupProcessByProcessId((HANDLE)0x4, &process);
		if (!NT_SUCCESS(status))
		{
			LOG("Process lookup failed!\n");
			continue;
		}

		KAPC_STATE apcState;
		KeStackAttachProcess(process, &apcState);

		PCHAR ProcessName = PsGetProcessImageFileName(IoGetCurrentProcess());
		LOG("%s : %p : IsKernalHandle(%d)", ProcessName, handle, ObIsKernelHandle(handle));
		


		KeUnstackDetachProcess(&apcState);
		ObDereferenceObject(process);
		//LOG("%lx\n", systemHandleInformationBuffer->Handles[i].HandleValue);
	}
	
	ExFreePool(systemHandleInformationBuffer);
	return STATUS_SUCCESS;
}

typedef struct _SYSTEM_MODULE_ENTRY
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} SYSTEM_MODULE_ENTRY, * PSYSTEM_MODULE_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG NumberOfModules;
	SYSTEM_MODULE_ENTRY Modules[1];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

NTSTATUS QueryModules()
{
	PSYSTEM_MODULE_INFORMATION modInfo = 0;
	QuerySystem(SystemModuleInformation, (PVOID*)&modInfo);


	ULONG bufferSize = 0;
	//PVOID buffer = NULL;
	NTSTATUS status;
	do
	{
		if (modInfo)
			ExFreePool(modInfo);

		bufferSize *= 2;
		modInfo = (PSYSTEM_MODULE_INFORMATION)ExAllocatePoolWithTag(PagedPool, bufferSize, 'kami');

		if (!modInfo)
			return STATUS_INSUFFICIENT_RESOURCES;

		status = ZwQuerySystemInformation(SystemModuleInformation, modInfo, bufferSize, &bufferSize);

	} while (status == STATUS_INFO_LENGTH_MISMATCH);

	if (!NT_SUCCESS(status))
	{
		ExFreePool(modInfo);
		return status;
	}

	for (ULONG i = 0; i < modInfo->NumberOfModules; i++)
	{
		LOG("ImageBase: %p ImageSize: %llx MappedBase: %p Offset: %p\n", 
			modInfo->Modules[i].ImageBase,
			modInfo->Modules[i].ImageSize,
			modInfo->Modules[i].MappedBase,
			modInfo->Modules[i].OffsetToFileName
			);
		LOG("FullPathName: %s\n", modInfo->Modules[i].FullPathName);
	}

	ExFreePool(modInfo);

	return STATUS_SUCCESS;
}
