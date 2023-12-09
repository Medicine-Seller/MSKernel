#include <ntifs.h>]
#include "HashMap.h"

#ifndef IOCTL_H
#define IOCTL_H
NTSTATUS IOCTL_Setup(PDRIVER_OBJECT driverObject, PUNICODE_STRING driverName, PUNICODE_STRING symbolName);
NTSTATUS IOCTL_Dismantle(PDRIVER_OBJECT driverObject);
NTSTATUS IOCTL_AddControl(ULONG controlCode, void* function);
NTSTATUS IOCTL_RemoveControl(ULONG controlCode);
BOOLEAN IOCTL_IsEnabled();
#endif
