#pragma once
#include <Windows.h>
#include <TlHelp32.h>

public ref class ProcessEntryWrapper {
public:
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID;
    ULONG_PTR th32DefaultHeapID;
    DWORD th32ModuleID;
    DWORD cntThreads;
    DWORD th32ParentProcessID;
    LONG pcPriClassBase;
    DWORD dwFlags;
    System::String^ szExeFile;

    ProcessEntryWrapper(PROCESSENTRY32& pe32) {
        dwSize = pe32.dwSize;
        cntUsage = pe32.cntUsage;
        th32ProcessID = pe32.th32ProcessID;
        th32DefaultHeapID = pe32.th32DefaultHeapID;
        th32ModuleID = pe32.th32ModuleID;
        cntThreads = pe32.cntThreads;
        th32ParentProcessID = pe32.th32ParentProcessID;
        pcPriClassBase = pe32.pcPriClassBase;
        dwFlags = pe32.dwFlags;
        szExeFile = gcnew System::String(pe32.szExeFile);
    }

    virtual System::String^ ToString() override {
        return szExeFile;
    }
private:

};