#include "Definitions.h"

#ifndef UTIL_H
#define UTIL_H

NTSTATUS QueryProcessHandles(ULONG processId);
NTSTATUS QuerySystemModules();
NTSTATUS QuerySystem(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID* systemInformation);

#endif