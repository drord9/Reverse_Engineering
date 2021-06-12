#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

LPVOID real_func_address;
int len_override;

char* str2;
const char* no_such_code = "NO SUCH CODE";

__declspec(naked) void strcmp_hook()
{
    //get second input to strcmp
    __asm mov eax, [esp + 8]
    __asm mov str2, eax

    if (strncmp(str2, no_such_code, strlen(no_such_code)) == 0)
    {   // if compering to "NO SUCH CODE" than this is firs strcmp of "codes.exe"
        // return 1 to pass it
        __asm mov eax, 1
    }
    else
    {
        // this is second strcmp of "codes.exe"
        // return 0 to pass it
        __asm mov eax, 0   
    }

    _asm ret
}

void setHook()
{
    LPVOID f;
    HMODULE h = GetModuleHandle(L"msvcrt.dll");
    CHAR JmpOpcode[] = "\xE9\x90\x90\x90\x90";
    DWORD lpProtect = 0;
    LPVOID JumpTo;

    if (h == NULL)
    {
        //log_file << "couldnt get handle" << endl;
        return;
    }
    f = GetProcAddress(h, "strcmp");
    // alternatively, get the function address by offset:
    // f = (char*)h + offset_to_func
    if (f == NULL)
    {
        //log_file << "couldnt get function" << endl;
        return;
    }

    // save the return address of f for jumping back
    real_func_address = f;
    len_override = strlen(JmpOpcode); // nubmer of bytes to override, changes from function to function
    
    //log_file << "setting hook" << endl;
    // calculate relative jump to HOOK_NAME from f, add 5 cause its from eip after the execution
    JumpTo = (LPVOID)((char *)&strcmp_hook - ((char *)f + 5));
    memcpy(JmpOpcode + 1, &JumpTo, 0x4); // write the jump
    VirtualProtect((char *)f, 0x7, PAGE_EXECUTE_READWRITE, &lpProtect);
    memcpy((char *)f, &JmpOpcode, len_override);
    VirtualProtect((char *)f, 0x7, PAGE_EXECUTE_READ, &lpProtect);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        setHook();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
