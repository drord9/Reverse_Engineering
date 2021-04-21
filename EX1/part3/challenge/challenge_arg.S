.intel_syntax noprefix
.global main

main:		

        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ebx
        push    ecx
        sub     esp, 48
        mov     ebx, ecx
	
	## int resources[NUM_OF_RESOURCES] = { 0 };
        mov     DWORD PTR [ebp-40], 0
        mov     DWORD PTR [ebp-36], 0
        mov     DWORD PTR [ebp-32], 0
        mov     DWORD PTR [ebp-28], 0
        mov     DWORD PTR [ebp-24], 0
	# char print_str[]    = "%02d ";
        mov     DWORD PTR [ebp-46], 1681010725
        mov     WORD PTR [ebp-42], 32
	## char _printf[]      = "printf";
        mov     DWORD PTR [ebp-53], 1852404336
        mov     WORD PTR [ebp-49], 26228
        mov     BYTE PTR [ebp-47], 0
	## char endl[]         = "\n";
        mov     WORD PTR [ebp-55], 10
	## FuncPtr printf = GetFuncAdd("printf");
        sub     esp, 12
        lea     eax, [ebp-53]
        push    eax
        call    GetFuncAdd
        add     esp, 16
        mov     DWORD PTR [ebp-20], eax
	## for (int i = 1; i < argc; ++i)
	mov     DWORD PTR [ebp-12], 1	#int i = 1
.L9:
        mov     eax, DWORD PTR [ebp-12]
        cmp     eax, DWORD PTR [ebx]	#i < argc
        jge     .L8
	## GetCosts(argv[i], resources);
        mov     eax, DWORD PTR [ebp-12]
        lea     edx, [0+eax*4]
        mov     eax, DWORD PTR [ebx+4]
        add     eax, edx
        mov     eax, DWORD PTR [eax]
        sub     esp, 8
        lea     edx, [ebp-40]
        push    edx
        push    eax
        call    GetCosts
        add     esp, 16
        add     DWORD PTR [ebp-12], 1	# ++i
        jmp     .L9
	#for (int i = 0; i < NUM_OF_RESOURCES; ++i)
.L8:
        mov     DWORD PTR [ebp-16], 0	# int i = 0
.L11:
        cmp     DWORD PTR [ebp-16], 4	# i < NUM_OF_RESOURCES
        jg      .L10
	# printf(print_str, resources[i]);
        mov     eax, DWORD PTR [ebp-16]
        mov     eax, DWORD PTR [ebp-40+eax*4]
        sub     esp, 8
        push    eax
        lea     eax, [ebp-46]
        push    eax
        mov     eax, DWORD PTR [ebp-20]
        call    eax
        add     esp, 16
        add     DWORD PTR [ebp-16], 1	#++i
        jmp     .L11
	# print("\n");
.L10:
        sub     esp, 12
        lea     eax, [ebp-55]
        push    eax
        mov     eax, DWORD PTR [ebp-20]
        call    eax
        add     esp, 16
        mov     eax, 0
        lea     esp, [ebp-8]
        pop     ecx
        pop     ebx
        pop     ebp
        lea     esp, [ecx-4]
        ret
##end main



## function: void GetCosts(char* goal, int resources[5])
GetCosts:
       GetCosts(char*, int*):
        push    ebp
        mov     ebp, esp
        sub     esp, 56
	## char funcName[] = "strcmp";
        mov     DWORD PTR [ebp-19], 1668445299	#"strcmp"
        mov     WORD PTR [ebp-15], 28781
        mov     BYTE PTR [ebp-13], 0
	## char road[] = "road";
        mov     DWORD PTR [ebp-24], 1684107122
        mov     BYTE PTR [ebp-20], 0
	## char settlement[] = "settlement";
        mov     DWORD PTR [ebp-35], 1953785203	#"settlement"
        mov     DWORD PTR [ebp-31], 1701668204
        mov     WORD PTR [ebp-27], 29806
        mov     BYTE PTR [ebp-25], 0
	## char city[] = "city";
        mov     DWORD PTR [ebp-40], 2037672291	#"city"
        mov     BYTE PTR [ebp-36], 0
	## char development[]  = "development";
        mov     DWORD PTR [ebp-52], 1702258020	#"development"
        mov     DWORD PTR [ebp-48], 1836085100
        mov     DWORD PTR [ebp-44], 7630437
	## FuncPtr __strcmp = GetFuncAdd("strcmp");
        sub     esp, 12
        lea     eax, [ebp-19]
        push    eax
        call    GetFuncAdd
        add     esp, 16		# clear stack
        mov     DWORD PTR [ebp-12], eax
	## if (!strcmp(goal, road))
        sub     esp, 8
        lea     eax, [ebp-24]
        push    eax
        push    DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [ebp-12]
        call    eax
        add     esp, 16
        test    eax, eax
        sete    al
        test    al, al
        je      .L2
	## resources[WOOD]++;
        mov     eax, DWORD PTR [ebp+12]
        mov     eax, DWORD PTR [eax]
        lea     edx, [eax+1]
        mov     eax, DWORD PTR [ebp+12]
        mov     DWORD PTR [eax], edx
	## resources[BRICK]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 4
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
        jmp     .L6
.L2:
	## else if (!strcmp(goal, settlement))
        sub     esp, 8
        lea     eax, [ebp-35]
        push    eax
        push    DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [ebp-12]
        call    eax
        add     esp, 16
        test    eax, eax
        sete    al
        test    al, al
        je      .L4
	## resources[WOOD]++;
        mov     eax, DWORD PTR [ebp+12]
        mov     eax, DWORD PTR [eax]
        lea     edx, [eax+1]
        mov     eax, DWORD PTR [ebp+12]
        mov     DWORD PTR [eax], edx
	## resources[BRICK]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 4
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
	## resources[WOLL]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 8
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
	## resources[GRAIN]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 12
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
        jmp     .L6
.L4:
	## else if (!strcmp(goal, city))
        sub     esp, 8
        lea     eax, [ebp-40]
        push    eax
        push    DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [ebp-12]
        call    eax
        add     esp, 16
        test    eax, eax
        sete    al
        test    al, al
        je      .L5
	## resources[GRAIN] += 2;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 12
        mov     edx, DWORD PTR [eax]
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 12
        add     edx, 2
        mov     DWORD PTR [eax], edx
	## resources[ORE] += 3;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 16
        mov     edx, DWORD PTR [eax]
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 16
        add     edx, 3
        mov     DWORD PTR [eax], edx
        jmp     .L6
.L5:
	## else if (!strcmp(goal, development))
        sub     esp, 8
        lea     eax, [ebp-52]
        push    eax
        push    DWORD PTR [ebp+8]
        mov     eax, DWORD PTR [ebp-12]
        call    eax
        add     esp, 16
        test    eax, eax
        sete    al
        test    al, al
        je      .L6
	## resources[WOLL]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 8
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
	## resources[GRAIN]++;
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 12
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
	## resources[ORE] ++
        mov     eax, DWORD PTR [ebp+12]
        add     eax, 16
        mov     edx, DWORD PTR [eax]
        add     edx, 1
        mov     DWORD PTR [eax], edx
.L6:
        nop
        leave
        ret
##end GetCosts

## function: void* GetFuncAdd(char* funcName)
GetFuncAdd:
	push ebp            # store ebp
	mov ebp, esp
	
	push ebx

	push 0x0       		# pushing null
	push 0x41797261		# pushing A,y,r,a
	push 0x7262694c		# pushing r,b,i,L
	push 0x64616f4c		# pushing d,a,o,L
	push esp            # push pointer for "LoadLibraryA"

	call FindFunction   # call FindFunction("LoadLibraryA")
	add esp, 0x14       # clear stack

	push 0x00006c6c		# pushing null,l,l
	push 0x642e7472		# pushing d,#,t,r
	push 0x6376736d		# pushing c,v,s,m
	push esp

	call eax            # call LoadLibrary("msvcrt.dll")
	add esp, 0x0c       # clear stack (note arguments are cleared already)

	push eax            # store module handle for msvcrt
	push 0x00007373		# pushing null,s,s
	push 0x65726464		# pushing e,r,d,d
	push 0x41636f72		# pushing A,c,o,r
	push 0x50746547		# pushing P,t,e,G
	push esp            # push pointer for "GetProcAddress"
	call FindFunction   # call FindFunction("GetProcAddress")
	add esp, 0x14       # clear stack
	pop ebx             # restore module handle for msvcrt

	push DWORD PTR [ebp+8]	# push funcName
	push ebx            	# push module handle for msvcrt
	call eax            	# call GetProcAddress(msvcrt, "printf")
	#add esp, 0x00       	# clear stack (note arguments are cleared already)

	pop ebx
	pop ebp             # restore ebp
	ret                 # return
##end GetFuncAdd

FindFunction:       # placeholder for search_kernel32
