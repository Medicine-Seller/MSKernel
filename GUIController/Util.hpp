#include "ProcessEntryWrapper.hpp"
#include "AccessMask.hpp"

System::Collections::Generic::List<ProcessEntryWrapper^>^% GetProcessList();
bool IsServiceExists(System::String^ serviceName);
void CreateDriverService(System::String^ serviceName, System::String^ driverPath);
System::String^ ExecuteCmdCommand(System::String^ command);