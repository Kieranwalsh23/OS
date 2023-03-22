# Set of .c Files that we will compile
C_FILES = ./kernel.c ./shell/console.c
# Create set of .o Files by using replacement on C_FILES
O_FILES = $(C_FILES:.c=.o)


# Launch the OS in QEMU
all:	qemu_launch
qemu_launch: os.bin
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy

# For every file in the set O_FILES, compile the similarly named C file and generate an O file.
# The –Iinclude tells the system where to find the #include headers we are using (the include folder)
$(O_FILES):
	gcc -Iinclude -fno-pie -m32 -ffreestanding -c $(@:.o=.c) -o $@

# Assemble kernel_entry.o from kernel_entry.elf
kernel_entry.o: kernel_entry.elf
	nasm $< -f elf -o $@

# Link kernel.bin and kernel_entry.o to create kernel.bin
kernel.bin: kernel_entry.o $(O_FILES)
	ld -m elf_i386 -s -o $@ -Ttext 0x1000 $^ --oformat binary

# Assemble boot.bin from boot.asm
boot.bin: boot.asm
	nasm $< -f bin -o $@

# Create os.bin from boot.bin and kernel.bin
os.bin: boot.bin kernel.bin
	cat $^ > $@

# remove old binaries and objects
clean:
	$(RM) *.bin *.o
	find . -name \*.o | xargs --no-run-if-empty rm