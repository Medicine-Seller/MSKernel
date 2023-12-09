#include "Definitions.h"
#include "Structs.h"

#ifndef UTIL_H
#define UTIL_H

UNICODE_STRING ToUnicodeString(LPCSTR string);
PVOID GetSystemRoutineAddress(LPCSTR routineName);

NTSTATUS QueryHandles();
NTSTATUS QueryModules();
NTSTATUS QuerySystemInformation(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, ULONG* returnLength);
NTSTATUS QuerySystem(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID* systemInformation);

#endif