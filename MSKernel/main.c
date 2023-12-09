#include "Logger.h"
#include "Modification.h"
#include "Util.h"
#include "IOCTL.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT driverObject, PUNICODE_STRING pRegistryPath);
NTSTATUS UnloadDriver(PDRIVER_OBJECT driverObject);

NTSTATUS DriverEntry(PDRIVER_OBJECT driverObject, PUNICODE_STRING pRegistryPath)
{
	//*(PULONG)((PCHAR)driverObject->DriverSection + 13 * sizeof(void*)) |= 0x20; // "/INTEGRITYCHECK"
	UNREFERENCED_PARAMETER(pRegistryPath);
	driverObject->DriverUnload = UnloadDriver;
	LOG("Loaded!\n");

	if (!InitializeDefinitions())
	{
		LOG("Initializing definitions failed");
		return STATUS_UNSUCCESSFUL;
	}

	NTSTATUS status;

	status = IOCTL_Setup(driverObject, L"\\Device\\MSKernel", L"\\DosDevices\\MSKernel");
	LOG("IOCTL_Setup status - %lx\n", status);

	status = InstallObCallbacks();
	LOG("InstallObCallbacks Status -  %lx\n", status);

    return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT driverObject)
{
	/*
	NTSTATUS status = IOCTL_Dismantle(driverObject);
	LOG("IOCTL_Dismantle status - %lx\n", status);

	UninstallObCallbacks();
	*/
	LOG("Unloaded!\n");
    return STATUS_SUCCESS;
}
