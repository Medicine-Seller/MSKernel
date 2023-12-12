#pragma once
#include <Windows.h>
#include <TlHelp32.h>

public ref class ProcessEntryWrapper {
public:

    ProcessEntryWrapper(PROCESSENTRY32& pe32) {
        Size = pe32.dwSize;
        Usage = pe32.cntUsage;
        ProcessID = pe32.th32ProcessID;
        DefaultHeapID = pe32.th32DefaultHeapID;
        ModuleID = pe32.th32ModuleID;
        Threads = pe32.cntThreads;
        ParentProcessID = pe32.th32ParentProcessID;
        PriClassBase = pe32.pcPriClassBase;
        Flags = pe32.dwFlags;
        ExeFile = gcnew System::String(pe32.szExeFile);
    }

    virtual System::String^ ToString() override {
        return ExeFile;
    }

    DWORD GetProcessId() {
        return ProcessID;
    }
private:
    DWORD Size;
    DWORD Usage;
    DWORD ProcessID;
    ULONG_PTR DefaultHeapID;
    DWORD ModuleID;
    DWORD Threads;
    DWORD ParentProcessID;
    LONG PriClassBase;
    DWORD Flags;
    System::String^ ExeFile;
};