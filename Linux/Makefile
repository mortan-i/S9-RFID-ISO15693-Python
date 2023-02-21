
#GCC:= arm-none-linux-gnueabi-gcc
GCC:= gcc
SONAME:=libS8.so
SRC:=*.c
all:
	cp $(SONAME) /lib/
	$(GCC) -fPIC -o demo -g $(SRC) $(SONAME)
clean:
	rm -rf demo *~
