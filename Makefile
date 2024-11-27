GCC = wine $(HOME)/.local/share/mingw64/bin/gcc.exe
INSTALL_DIR = $(HOME)/.local/vmshare/
# $(info $(PATH) $(origin PATH))


main : main.c useful.h syscalls.obj
	$(GCC) -Wno-int-conversion -Wno-int-to-pointer-cast -o main.exe main.c syscalls.obj \
		&& cp main.exe $(INSTALL_DIR)

syscalls.obj : syscalls.asm
	nasm -f win64 syscalls.asm
