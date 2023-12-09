#include "MSKernelInterface.hpp"

MSKernelInterface::~MSKernelInterface()
{
	if (!IsDriverValid())
		return;

	CloseHandle(Driver);
}

BOOL MSKernelInterface::IsDriverValid()
{
	return Driver != INVALID_HANDLE_VALUE;
}

void MSKernelInterface::SetDriver(LPCSTR registryPath)
{
	this->registryPath = registryPath;
}

BOOL MSKernelInterface::Initialize()
{
	if (!IsDriverValid())
		Driver = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	return IsDriverValid();
}

BOOL MSKernelInterface::SetPID(ULONG pid)
{
	if (!Initialize())
		return FALSE;

	DWORD bytes;
	return DeviceIoControl(Driver, IO_SET_PID, &pid, sizeof(pid), &pid, sizeof(pid), &bytes, NULL);
}

BOOL MSKernelInterface::SetAccessMask(DWORD accessMask)
{
	if (!Initialize())
		return FALSE;

	DWORD bytes;
	return DeviceIoControl(Driver, IO_SET_ACCESSMASK, &accessMask, sizeof(accessMask), &accessMask, sizeof(accessMask), &bytes, NULL);
}

HANDLE MSKernelInterface::GetDriverHandle()
{
	return Driver;
}

BOOL MSKernelInterface::Close()
{
	return CloseHandle(Driver);
}

