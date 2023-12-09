#include <ntifs.h>
#include "Logger.h"
#include "Definitions.h"

NTSTATUS InstallObCallback(PVOID preOperationFunction, PVOID postOperationFunction, PVOID* callbackHandle, ULONG altitude)
{
	UNICODE_STRING altitudeUnicode;
	WCHAR buffer[0x64];
	altitudeUnicode.Buffer = buffer;
	altitudeUnicode.MaximumLength = sizeof(buffer);
	altitudeUnicode.Length = altitudeUnicode.MaximumLength;
	RtlInt64ToUnicodeString(altitude, 10, &altitudeUnicode);

	OB_OPERATION_REGISTRATION operation;
	operation.ObjectType = PsProcessType;
	operation.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
	operation.PreOperation = (POB_PRE_OPERATION_CALLBACK)preOperationFunction;
	operation.PostOperation = (POB_POST_OPERATION_CALLBACK)postOperationFunction;

	OB_CALLBACK_REGISTRATION callbackRegistration;
	callbackRegistration.Version = OB_FLT_REGISTRATION_VERSION;
	callbackRegistration.OperationRegistrationCount = 1;
	callbackRegistration.Altitude = altitudeUnicode;
	callbackRegistration.RegistrationContext = NULL;
	callbackRegistration.OperationRegistration = &operation;

	return ObRegisterCallbacks(&callbackRegistration, callbackHandle);
}

