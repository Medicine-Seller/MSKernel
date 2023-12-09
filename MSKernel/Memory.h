#include <ntifs.h>

#ifndef MEMORY_H
#define MEMORY_H


NTSTATUS WriteReadOnlyMemory(PVOID address, PVOID buffer, ULONG size);
NTSTATUS WriteUserModeMemory(PRKPROCESS targetProcess, PVOID address, PVOID buffer, ULONG size);


#endif