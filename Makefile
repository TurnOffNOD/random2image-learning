C_STANDARD := c23
DEBUG_FLAG := -g
C_FLAFS := -std=$(C_STANDARD) -O0

DEBUG := 1

#ifeq ($(DEBUG)),
C_FLAFS += $(DEBUG_FLAG)
#endif

#CC := "D:\ProgramFiles\msys64\mingw64\bin\gcc"
#这样设定能在wsl和windows的mingw环境下通用
GNUCC := gcc
LLVMCLANG := clang

all: random2imageWinGCC random2imageWinCLANG

#random2imageOnWinMsys: random2image.c toBigEndian.h
random2imageWinGCC: random2image.c
	$(GNUCC) -o random2imageWinGCC $(C_FLAFS) random2image.c

random2imageWinCLANG: random2image.c
	$(LLVMCLANG) -o random2imageWinCLANG $(C_FLAFS) random2image.c


.PHONY: clean
clean:
	-rm *.exe
	-rm *.out
	-rm *.pam
	-rm *.rgba
	-rm random2imageWinGCC
	-rm random2imageWinCLANG