SELFDESC_C_FLAGS=-c -O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow -Wstrict-prototypes -Wswitch -Wwrite-strings

selfdesc: selfdesc.o
	gcc -o selfdesc selfdesc.o

selfdesc.o: selfdesc.c selfdesc.make
	gcc ${SELFDESC_C_FLAGS} -o selfdesc.o selfdesc.c

clean:
	rm -f selfdesc selfdesc.o
