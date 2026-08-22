CC = gcc
ASM = nasm
CFLAGS = -Wall -Wextra -g3 -ItoolLib/include
ASMFLAGS = -f win64
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SRC = $(call rwildcard,toolLib/,*.c)
ASMSRC = $(call rwildcard,toolLib/,*.S)
ASMOBJ = $(ASMSRC:.S=.o)
OUT = output/main.exe

all: $(OUT)

%.o: %.S
	$(ASM) $(ASMFLAGS) $< -o $@

$(OUT): $(SRC) $(ASMOBJ)
	$(CC) $(CFLAGS) $(SRC) $(ASMOBJ) -o $(OUT)

clean:
	rm -f $(OUT) $(ASMOBJ)
