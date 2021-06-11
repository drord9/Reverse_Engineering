
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <sstream>

using std::endl;
using std::string;

char decrypt_char(char c)
{
	switch (c)
	{
	case 'A':
		c = 1;
		break;
	case 'J':
		c = 10;
		break;
	case 'Q':
		c = 11;
		break;
	case 'K':
		c = 12;
		break;
	default:
		c -= '0';
		break;
	}
	return c;
}

void decrypt_line(const string& in, string& out)
{
	string tmp;

	//1. clean (+ / -) charcters	

	for (size_t i = 0; i < in.size(); i++)
	{
		if (in[i] != '-' && in[i] != '+')
		{
			tmp.push_back(in[i]);
		}
		else
		{
			char sum = '0';
			if (in[i] == '+')
			{
				char prev = in[i - 1] - '0';
				char next = in[i + 1] - '0';
				sum += (prev + next);
			}

			tmp.back() = sum;
			i++;
		}
	}

	//2. decrypt the line
	for (size_t i = 0; i < tmp.size() - 1; i += 2)
	{
		char high = decrypt_char(tmp[i]);
		char low = decrypt_char(tmp[i + 1]);

		out.push_back(high << 4 | low);
	}
}


void decrypt_text(char* text)
{
	if (text)
	{
		int len = strlen(text);
		std::stringstream input(text);
		std::stringstream output;
		std::string line;

		while (getline(input, line))
		{
			string res;
			decrypt_line(line, res);

			output << res << endl;
		}

		strcpy_s(text, len, output.str().c_str());
	}
}

LPVOID real_func_address;
int len_override;

char* str1;
const char* ref = "MESSAGE: ";

__declspec(naked) void ClientHook()
{
	//get server request
	__asm {
		mov eax, ebp
		sub eax, 23
		mov str1, eax
	}

	if (strncmp(str1, ref, strlen(ref)) == 0)
	{//only if the server request was 'DMSG' decrypt the result string
		__asm {
			push[esp + 4]
			call decrypt_text
			pop eax	//clear stack		
		}
	}

	__asm{
		; restore the commands overriden

		push    14h
		mov		eax, 0x2F778
		add		eax, real_func_address
		push    eax

        ; jump back
        mov eax, real_func_address
        mov ecx, len_override
        add eax, ecx
        jmp eax
    }
}

void setHook()
{

    LPVOID f;
    HMODULE h = GetModuleHandle(L"msvcrt.dll");
    CHAR JmpOpcode[] = "\xE9\x90\x90\x90\x90\x90\x90";
    DWORD lpProtect = 0;
    LPVOID JumpTo;

    if (h == NULL)
    {
        //log_file << "couldnt get handle" << endl;
        return;
    }
    f = GetProcAddress(h, "puts");

    if (f == NULL)
    {
        //log_file << "couldnt get function" << endl;
        return;
    }

    // save the return address of f for jumping back
    real_func_address = f;
    len_override = 7; // nubmer of bytes to override, changes from function to function

    
    //log_file << "setting hook" << endl;
    // calculate relative jump to HOOK_NAME from f, add 5 cause its from eip after the execution
    JumpTo = (LPVOID)((char *)&ClientHook - ((char *)f + 5));
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
