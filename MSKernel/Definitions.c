#include "Definitions.h"
#include "Util.h"
#include "Logger.h"

pfnPsGetProcessImageFileName PsGetProcessImageFileName;
pfnZwQuerySystemInformation ZwQuerySystemInformation;

struct Definition
{
	void** function;
	const char* functionName;
};

#define P_F(x) {(void**)(&x), #x}
struct Definition UndocumentedFunctionList[] =
{
	P_F(PsGetProcessImageFileName),
	P_F(ZwQuerySystemInformation)
};
#undef P_F

BOOLEAN InitializeDefinitions()
{
	const int size = sizeof(UndocumentedFunctionList) / sizeof(UndocumentedFunctionList[0]);
	LOGF("Size = %d", size);

	for (int i = 0; i < size; i++)
	{
		struct Definition* d = &UndocumentedFunctionList[i];

		if (d->function == NULL)
		{
			LOGF("Failed to initialize definition: %s = %p\n", d->functionName, d->function);
			return FALSE;
		}

		*d->function = GetSystemRoutineAddress(d->functionName);
		LOGF("%s = %p", d->functionName, *d->function);
	}

	return TRUE;
}