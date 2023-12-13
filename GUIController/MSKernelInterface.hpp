#include <Windows.h>
#include <iostream>
#include "../MSKernel/IOCTL_ControlCodes.h"

class MSKernelInterface
{
public:
	~MSKernelInterface();
	BOOL SetPID(ULONG pid);
	BOOL SetAccessMask(DWORD accessMask);
	void SetDriver(LPCSTR registryPath);
	BOOL Initialize();
	BOOL IsDriverValid();
	HANDLE GetDriverHandle();
	BOOL Close();

private:
	LPCSTR registryPath;
	HANDLE Driver = INVALID_HANDLE_VALUE;
};
