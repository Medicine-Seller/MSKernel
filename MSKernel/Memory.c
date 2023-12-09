#include "Memory.h"
#include "Definitions.h"
#include "Util.h"
#include "Structs.h"
#include "Logger.h"

NTSTATUS WriteReadOnlyMemory(PVOID address, PVOID buffer, ULONG size)
{
	MDL* mdl = IoAllocateMdl(address, size, FALSE, FALSE, NULL);
	if (!mdl)
		return STATUS_INSUFFICIENT_RESOURCES;

	MmProbeAndLockPages(mdl, KernelMode, IoReadAccess);
	
	void* mapping = MmMapLockedPagesSpecifyCache(mdl, KernelMode, MmNonCached, NULL, FALSE, NormalPagePriority);
	if (!mapping)
	{
		MmUnlockPages(mdl);
		IoFreeMdl(mdl);
		return STATUS_INTERNAL_ERROR;
	}

	NTSTATUS status = MmProtectMdlSystemAddress(mdl, PAGE_READWRITE);
	if (!NT_SUCCESS(status))
	{
		MmUnmapLockedPages(mapping, mdl);
		MmUnlockPages(mdl);
		IoFreeMdl(mdl);
		return status;
	}

	memcpy(mapping, buffer, size);
	MmUnmapLockedPages(mapping, mdl);
	MmUnlockPages(mdl);
	IoFreeMdl(mdl);

	return STATUS_SUCCESS;
}

NTSTATUS WriteUserModeMemory(PRKPROCESS targetProcess, PVOID address, PVOID buffer, ULONG size)
{
	KAPC_STATE apcState;
	KeStackAttachProcess(targetProcess, &apcState);
	NTSTATUS status = WriteReadOnlyMemory(address, buffer, size);
	KeUnstackDetachProcess(&apcState);
	return status;
}

