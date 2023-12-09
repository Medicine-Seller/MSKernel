#include <ntifs.h>
#include "Structs.h"

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define STRING_PAIR(x) x,#x

BOOLEAN InitializeDefinitions();

typedef NTKERNELAPI PCHAR (NTAPI *pfnPsGetProcessImageFileName)(
    _In_ PEPROCESS Process
);
extern pfnPsGetProcessImageFileName PsGetProcessImageFileName;

typedef NTSYSCALLAPI NTSTATUS (NTAPI *pfnZwQuerySystemInformation)(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
);
extern pfnZwQuerySystemInformation ZwQuerySystemInformation;

#endif
