#include <windows.h>
#include <iostream>
#include <vector>

int main() {
    SC_HANDLE scmHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (!scmHandle)
        return 1;

    DWORD bytesNeeded = 0;
    DWORD servicesCount = 0;
    DWORD resumeHandle = 0;

    // Prima apelare pentru a determina dimensiunea buffer-ului necesar
    EnumServicesStatusEx(
        scmHandle,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        NULL,
        0,
        &bytesNeeded,
        &servicesCount,
        &resumeHandle,
        NULL);

    std::vector<BYTE> buffer(bytesNeeded);
    LPENUM_SERVICE_STATUS_PROCESS services = reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());

    // A doua apelare pentru a obține datele efective
    if (EnumServicesStatusEx(
        scmHandle,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        buffer.data(),
        bytesNeeded,
        &bytesNeeded,
        &servicesCount,
        &resumeHandle,
        NULL))
        {

        std::cout << "Servicii care ruleaza in prezent: " << servicesCount << "\n\n";
        for (DWORD i = 0; i < servicesCount; i++) {
            std::wcout << L"Nume: " << services[i].lpDisplayName << L" [" << services[i].lpServiceName << L"]" << std::endl;
        }
        }

    CloseServiceHandle(scmHandle);
    return 0;
}