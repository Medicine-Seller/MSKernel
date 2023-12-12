#include "Util.h"
#include "Definitions.h"
#include "Logger.h"

#define MEM_TAG_UTIL 'UTIL'

NTSTATUS QuerySystem(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID* systemInformation)
{
	if (!systemInformation)
		return STATUS_UNSUCCESSFUL;

	ULONG bufferSize = 0;
	PVOID buffer = NULL;
	NTSTATUS status;

	do
	{
		if (buffer)
			ExFreePoolWithTag(buffer, MEM_TAG_UTIL);

		bufferSize *= 2;
		buffer = ExAllocatePoolWithTag(PagedPool, bufferSize, MEM_TAG_UTIL);

		if (!buffer)
			return STATUS_INSUFFICIENT_RESOURCES;

		status = ZwQuerySystemInformation(systemInformationClass, buffer, bufferSize, &bufferSize);
	} 
	while (status == STATUS_INFO_LENGTH_MISMATCH);

	if (!NT_SUCCESS(status)) 
	{
		ExFreePoolWithTag(buffer, MEM_TAG_UTIL);
		return status;
	}

	*systemInformation = buffer;

	return status;
}

NTSTATUS QueryProcessHandles(ULONG processId)
{
	PSYSTEM_HANDLE_INFORMATION handleInformationBuffer = NULL;
	NTSTATUS status;

	status = QuerySystem(SystemHandleInformation, &handleInformationBuffer);
	if (!NT_SUCCESS(status))
		return status;

	for (auto i = 0; i < handleInformationBuffer->NumberOfHandles; i++)
	{
		PSYSTEM_HANDLE_ENTRY handleInfo = &handleInformationBuffer->Handles[i];

		if (processId != -1 && handleInfo->UniqueProcessId != processId)
			continue;
		
		LOG("PID: %d - %lx\n", handleInfo->UniqueProcessId, handleInfo->HandleValue);
	}
	
	ExFreePoolWithTag(handleInformationBuffer, MEM_TAG_UTIL);
	return STATUS_SUCCESS;
}

NTSTATUS QuerySystemModules()
{
	PSYSTEM_MODULE_INFORMATION moduleInformationBuffer;
	NTSTATUS status;
	
	status = QuerySystem(SystemModuleInformation, &moduleInformationBuffer);
	if (!NT_SUCCESS(status))
		return status;

	for (ULONG i = 0; i < moduleInformationBuffer->NumberOfModules; i++)
	{
		PSYSTEM_MODULE_ENTRY module = &moduleInformationBuffer->Modules[i];
		LOG("ImageBase: %p - %s\n", module->ImageBase, module->FullPathName);
	}

	ExFreePoolWithTag(moduleInformationBuffer, MEM_TAG_UTIL);
	return STATUS_SUCCESS;
}
