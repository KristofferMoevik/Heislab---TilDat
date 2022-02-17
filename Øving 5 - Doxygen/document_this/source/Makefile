C_FILES := calculations.o system.o 

CC := gcc

CFLAGS := -O0 -g3

.DEFAULT_GOAL := main

main : $(C_FILES)
		$(CC) $(CFLAGS) $(C_FILES) -o $@


.PHONY : clean
clean :
		rm -rf $(.DEFAULT_GOAL) *.o
