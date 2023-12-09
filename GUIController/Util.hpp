#include <windows.h>
#include <tlhelp32.h>

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

public ref class AccessRight {
private:
    System::String^ Name;
    DWORD Access;

public:
    AccessRight(System::String^ name, DWORD access) {
        Name = name;
        Access = access;
    }

    virtual System::String^ ToString() override {
        return Name;
    }

    DWORD GetAccess() {
        return Access;
    }
};

public ref class AccessMask{
public:
    
    static AccessMask^ Instance(){
        if (AcessMaskInstance == nullptr)
            AcessMaskInstance = gcnew AccessMask();

        return AcessMaskInstance;
    }

    System::Collections::Generic::List<AccessRight^>^% GetAccessRights(){
        return AccessRightList;
    }

    DWORD GetMask(){
        return Mask;
    }

    void ResetMask() {
        Mask = 0;
    }

    void OperationOrMask(DWORD value) {
        Mask |= value;
    }

private:
    DWORD Mask;
    System::Collections::Generic::List<AccessRight^>^ AccessRightList;
    static AccessMask^ AcessMaskInstance = nullptr;
    
    AccessMask() {
        Mask = 0;
        AccessRightList = gcnew System::Collections::Generic::List<AccessRight^>();
        AccessRightList->Add(gcnew AccessRight("PROCESS_ALL_ACCESS", PROCESS_ALL_ACCESS));
        AccessRightList->Add(gcnew AccessRight("PROCESS_CREATE_PROCESS", PROCESS_CREATE_PROCESS));
        AccessRightList->Add(gcnew AccessRight("PROCESS_CREATE_THREAD", PROCESS_CREATE_THREAD));
        AccessRightList->Add(gcnew AccessRight("PROCESS_DUP_HANDLE", PROCESS_DUP_HANDLE));
        AccessRightList->Add(gcnew AccessRight("PROCESS_QUERY_INFORMATION", PROCESS_QUERY_INFORMATION));
        AccessRightList->Add(gcnew AccessRight("PROCESS_QUERY_LIMITED_INFORMATION", PROCESS_QUERY_LIMITED_INFORMATION));
        AccessRightList->Add(gcnew AccessRight("PROCESS_SET_INFORMATION", PROCESS_SET_INFORMATION));
        AccessRightList->Add(gcnew AccessRight("PROCESS_SET_QUOTA", PROCESS_SET_QUOTA));
        AccessRightList->Add(gcnew AccessRight("PROCESS_SUSPEND_RESUME", PROCESS_SUSPEND_RESUME));
        AccessRightList->Add(gcnew AccessRight("PROCESS_TERMINATE", PROCESS_TERMINATE));
        AccessRightList->Add(gcnew AccessRight("PROCESS_VM_OPERATION", PROCESS_VM_OPERATION));
        AccessRightList->Add(gcnew AccessRight("PROCESS_VM_READ", PROCESS_VM_READ));
        AccessRightList->Add(gcnew AccessRight("PROCESS_VM_WRITE", PROCESS_VM_WRITE));
        AccessRightList->Add(gcnew AccessRight("SYNCHRONIZE", SYNCHRONIZE));
    }
};

System::Collections::Generic::List<ProcessEntryWrapper^>^% GetProcessList();
bool IsServiceExists(System::String^ serviceName);
void CreateDriverService(System::String^ serviceName, System::String^ driverPath);
void ExecuteCmdCommand(System::String^ command);