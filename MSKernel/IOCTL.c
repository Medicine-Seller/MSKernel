#include "IOCTL.h"
#include "Logger.h"

#define MEM_TAG 'IOIO'

struct HashMap IOCTL_ControlCodeMap;
BOOLEAN IOCTL_Enabled = FALSE;

UNICODE_STRING DriverName = { NULL };
UNICODE_STRING SymbolName = { NULL };
PDEVICE_OBJECT IoDeviceObject = NULL;

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IofCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IofCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT deviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObject);

	NTSTATUS status = STATUS_UNSUCCESSFUL;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	if (!stack)
		return status;

	ULONG controlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	void* function = NULL;
	HashMap_Get(&IOCTL_ControlCodeMap, controlCode, &function);

	if (function != NULL)
	{
		NTSTATUS (*functionPointer)(PIRP irp) = function;
		status = functionPointer(irp);
	}

	irp->IoStatus.Status = status;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS IOCTL_Setup(PDRIVER_OBJECT driverObject, PUNICODE_STRING driverName, PUNICODE_STRING symbolName)
{
	NTSTATUS status = STATUS_SUCCESS;

	if (IOCTL_IsEnabled())
		return status;

	RtlInitUnicodeString(&DriverName, driverName);
	RtlInitUnicodeString(&SymbolName, symbolName);

	status = IoCreateDevice(driverObject, 0, &DriverName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &IoDeviceObject);
	if (!NT_SUCCESS(status))
		return status;

	status = IoCreateSymbolicLink(&SymbolName, &DriverName);
	if (!NT_SUCCESS(status))
		return status;

	driverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	driverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	driverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	IoDeviceObject->Flags |= DO_DIRECT_IO;
	IoDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	IOCTL_Enabled = TRUE;
	return status;
}

NTSTATUS IOCTL_Dismantle(PDRIVER_OBJECT driverObject)
{
	NTSTATUS status = STATUS_SUCCESS;
	if (!IOCTL_IsEnabled())
		return status;

	status = IoDeleteSymbolicLink(&SymbolName);
	if (!NT_SUCCESS(status))
		return status;

	IoDeleteDevice(driverObject->DeviceObject);

	HashMap_Clear(&IOCTL_ControlCodeMap);

	IOCTL_Enabled = FALSE;
	return STATUS_SUCCESS;;
}

NTSTATUS IOCTL_AddControl(ULONG controlCode, void* function)
{
	if (!IOCTL_Enabled)
		return STATUS_INTERNAL_ERROR;

	return HashMap_Insert(&IOCTL_ControlCodeMap, controlCode, function);
}

NTSTATUS IOCTL_RemoveControl(ULONG controlCode)
{
	if (!IOCTL_Enabled)
		return STATUS_INTERNAL_ERROR;

	return HashMap_Erase(&IOCTL_ControlCodeMap, controlCode);
}

BOOLEAN IOCTL_IsEnabled()
{
	return IOCTL_Enabled;
}