C_STANDARD := c23
DEBUG_FLAG := -g
C_FLAFS := -std=$(C_STANDARD) -O0

#ifeq($(DEBUG), 
#	C_FLAFS += DEBUG_FLAG
#endif

#CC := "D:\ProgramFiles\msys64\mingw64\bin\gcc"
#这样设定能在wsl和windows的mingw环境下通用
GNUCC := gcc

#random2imageOnWinMsys: random2image.c toBigEndian.h
random2imageOnWinMsys: random2image.c
	$(GNUCC) -o random2imageOnWinMsys $(C_FLAFS) random2image.c toBigEndian.h


.PHONY: clean
clean:
	-rm *.exe
	-rm *.out
	-rm *.pam
	-rm *.rgba