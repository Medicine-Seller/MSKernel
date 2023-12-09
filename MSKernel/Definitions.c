#include "Definitions.h"
#include "Util.h"
#include "Logger.h"

PsGetProcessImageFileName_t PsGetProcessImageFileName;
ZwQuerySystemInformation_t ZwQuerySystemInformation;

struct Definition
{
	PVOID* Function;
	UNICODE_STRING FunctionName;
};

#define P_F(x) {&x, RTL_CONSTANT_STRING(L#x)}
struct Definition UndocumentedFunctionList[] =
{
	P_F(PsGetProcessImageFileName),
	P_F(ZwQuerySystemInformation)
};
#undef P_F

const int UndocumentedFunctionSize = sizeof(UndocumentedFunctionList) / sizeof(UndocumentedFunctionList[0]);

BOOLEAN InitializeDefinitions()
{
	for (int i = 0; i < UndocumentedFunctionSize; i++)
	{
		struct Definition* d = &UndocumentedFunctionList[i];

		*d->Function = MmGetSystemRoutineAddress(&d->FunctionName);
		
		if (*d->Function == NULL)
			return FALSE;
	}

	return TRUE;
}