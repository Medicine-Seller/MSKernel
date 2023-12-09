#include "ObRegisterCallbacks.h"

#ifndef MODIFICATION_H
#define MODIFICATION_H

OB_PREOP_CALLBACK_STATUS PreOperation_LowAlt(PVOID registrationContext, POB_PRE_OPERATION_INFORMATION operationInformation);
OB_PREOP_CALLBACK_STATUS PreOperation_HighAlt(PVOID registrationContext, POB_PRE_OPERATION_INFORMATION operationInformation);

NTSTATUS InstallObCallbacks();
VOID UninstallObCallbacks();


#endif