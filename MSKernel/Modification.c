#include "Modification.h"
#include "Definitions.h"
#include "Logger.h"
#include "IOCTL.h"
#include "IOCTL_Definitions.h"

ULONG PID = NULL;
ACCESS_MASK AccessMask = NULL;
PVOID HighAltCallbackHandle;
PVOID LowAltCallbackHandle;

OB_PREOP_CALLBACK_STATUS PreOperation(PVOID registrationContext, POB_PRE_OPERATION_INFORMATION operationInformation)
{
	UNREFERENCED_PARAMETER(registrationContext);
	
	if (PID && PsGetCurrentProcessId() == PID)
	{
		operationInformation->Parameters->CreateHandleInformation.DesiredAccess = AccessMask;
		operationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = AccessMask;
	}

	return OB_PREOP_SUCCESS;
}

OB_PREOP_CALLBACK_STATUS PostOperation(PVOID registrationContext, POB_POST_OPERATION_INFORMATION operationInformation)
{
	UNREFERENCED_PARAMETER(registrationContext);

	if (PID && PsGetCurrentProcessId() == PID)
	{
		operationInformation->Parameters->CreateHandleInformation.GrantedAccess = AccessMask;
		operationInformation->Parameters->DuplicateHandleInformation.GrantedAccess = AccessMask;
	}
		
	return OB_PREOP_SUCCESS;
}

NTSTATUS SetPID(PIRP irp)
{
	PID = *(ULONG*)irp->AssociatedIrp.SystemBuffer;
	irp->IoStatus.Information = sizeof(PID);
	LOG("PID - %d\n", PID);
	return STATUS_SUCCESS;
}

NTSTATUS SetAccessMask(PIRP irp)
{
	AccessMask = *(ACCESS_MASK*)irp->AssociatedIrp.SystemBuffer;
	irp->IoStatus.Information = sizeof(AccessMask);
	LOG("Access Mask - %lx\n", AccessMask);
}

NTSTATUS InstallObCallbacks()
{
	NTSTATUS status;

	IOCTL_AddControl(IO_SET_PID, SetPID);
	IOCTL_AddControl(IO_SET_ACCESSMASK, SetAccessMask);

	status = InstallObCallback(PreOperation, PostOperation, &HighAltCallbackHandle, 429999);
	if (!NT_SUCCESS(status))
		return status;

	status = InstallObCallback(PreOperation, PostOperation, &LowAltCallbackHandle, 20000);
	if (!NT_SUCCESS(status))
		return status;

	return STATUS_SUCCESS;
}

VOID UninstallObCallbacks()
{
	if (HighAltCallbackHandle)
		ObUnRegisterCallbacks(HighAltCallbackHandle);
	if (LowAltCallbackHandle)
		ObUnRegisterCallbacks(LowAltCallbackHandle);
}


