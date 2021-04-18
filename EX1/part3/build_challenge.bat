gcc -c challenge.S -o challenge.o
objcopy -O binary challenge.o challenge.bin

type PE.bin challenge.bin find_function.bin > challenge.exe