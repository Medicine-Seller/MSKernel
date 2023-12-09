#include <Windows.h>
#include <iostream>
#include "../MSKernel/IOCTL_Definitions.h"

class MSKernelInterface
{
public:
	HANDLE Driver;

	MSKernelInterface(LPCSTR registryPath)
	{
		Driver = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		printf("Driver: %p\n", Driver);
	}

	BOOL SetPID(ULONG pid)
	{
		if (Driver == INVALID_HANDLE_VALUE)
			return FALSE;

		DWORD bytes;
		if (DeviceIoControl(Driver, IO_SET_PID, &pid, sizeof(pid), &pid, sizeof(pid), &bytes, NULL))
		{
			return TRUE;
		}
	}

	BOOL SetAccessMask(DWORD accessMask)
	{
		if (Driver == INVALID_HANDLE_VALUE)
			return FALSE;

		DWORD bytes;
		if (DeviceIoControl(Driver, IO_SET_PID, &accessMask, sizeof(accessMask), &accessMask, sizeof(accessMask), &bytes, NULL))
		{
			return TRUE;
		}
	}

private:
};
