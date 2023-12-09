#pragma once
#include <Windows.h>

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

public ref class AccessMask {
public:

    static AccessMask^ Instance() {
        if (AcessMaskInstance == nullptr)
            AcessMaskInstance = gcnew AccessMask();

        return AcessMaskInstance;
    }

    System::Collections::Generic::List<AccessRight^>^% GetAccessRights() {
        return AccessRightList;
    }

    DWORD GetMask() {
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
        AccessRightList->Add(gcnew AccessRight("DELETE ", DELETE));
        AccessRightList->Add(gcnew AccessRight("READ_CONTROL ", READ_CONTROL));
        AccessRightList->Add(gcnew AccessRight("WRITE_DAC ", WRITE_DAC));
        AccessRightList->Add(gcnew AccessRight("WRITE_OWNER ", WRITE_OWNER));
    }
};