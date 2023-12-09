#include "MSKernelInterface.hpp"
#include <string>

int main()
{
	MSKernelInterface mskernel = MSKernelInterface("\\\\.\\MSKernel");

	std::string input;
	while (input != "exit")
	{
		std::cin >> input;
		if (input == "set_pid")
		{
			DWORD pid;
			std::cin >> pid;
			if (mskernel.SetPID(pid))
				printf("SUCCESS!\n");
		}
		else if (input == "set_access_mask")
		{
			DWORD accessMask;
			std::cin >> std::hex >> accessMask;
			if (mskernel.SetAccessMask(accessMask))
				printf("SUCCESS!\n");
		}
	}

	return 0;
}