#include <ntifs.h>
#include "Definitions_Struct.h"

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

BOOLEAN InitializeDefinitions();

typedef NTKERNELAPI PCHAR (NTAPI *PsGetProcessImageFileName_t)(
    _In_ PEPROCESS Process
);
extern PsGetProcessImageFileName_t PsGetProcessImageFileName;

typedef NTSYSCALLAPI NTSTATUS (NTAPI *ZwQuerySystemInformation_t)(
    _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
    _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
);
extern ZwQuerySystemInformation_t ZwQuerySystemInformation;

#endif
