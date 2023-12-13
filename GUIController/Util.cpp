#include "Util.hpp"

System::Collections::Generic::List<ProcessEntryWrapper^>^% GetProcessList() {
    System::Collections::Generic::List< ProcessEntryWrapper^>^ processes = gcnew System::Collections::Generic::List< ProcessEntryWrapper^>();
    HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapShot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapShot, &pe32)) {
            do {
                processes->Add(gcnew ProcessEntryWrapper(pe32));
            } while (Process32Next(snapShot, &pe32));
        }

        CloseHandle(snapShot);
    }
    return processes;
}

bool IsServiceExists(System::String^ serviceName) {
    System::Diagnostics::ProcessStartInfo^ startInfo = gcnew System::Diagnostics::ProcessStartInfo();
    startInfo->FileName = "sc.exe";
    startInfo->Arguments = "query " + serviceName;
    startInfo->RedirectStandardOutput = true;
    startInfo->UseShellExecute = false;
    startInfo->CreateNoWindow = true;

    System::Diagnostics::Process^ process = System::Diagnostics::Process::Start(startInfo);
    System::String^ output = process->StandardOutput->ReadToEnd();
    return output->Contains("SERVICE_NAME: " + serviceName);
}

void CreateDriverService(System::String^ serviceName, System::String^ driverPath) {
    System::Diagnostics::ProcessStartInfo^ startInfo = gcnew System::Diagnostics::ProcessStartInfo();
    startInfo->FileName = "sc.exe";
    startInfo->Arguments = "create " + serviceName + " binPath= \"" + driverPath + "\" type= kernel";
    startInfo->Verb = "runas";
    startInfo->UseShellExecute = false;

    System::Diagnostics::Process::Start(startInfo);
}

System::String^ ExecuteCmdCommand(System::String^ command) {
    System::Diagnostics::ProcessStartInfo^ startInfo = gcnew System::Diagnostics::ProcessStartInfo();
    startInfo->FileName = "cmd.exe";
    startInfo->Arguments = "/C " + command;
    startInfo->RedirectStandardOutput = true;
    startInfo->UseShellExecute = false;
    startInfo->CreateNoWindow = true;

    System::Diagnostics::Process^ process = System::Diagnostics::Process::Start(startInfo);
    return process->StandardOutput->ReadToEnd();
}
