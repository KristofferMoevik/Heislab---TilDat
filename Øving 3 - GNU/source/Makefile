TACO_DEPENDENCIES = taco_krydder.o taco_saus.o taco_lefse.o protein.o grønnsaker.o drikke.o main.o 

CC := gcc

CFLAGS := -O0 -g3

.DEFAULT_GOAL := taco

taco : $(TACO_DEPENDENCIES)
		$(CC) $(CFLAGS) $(TACO_DEPENDENCIES) -o $@


.PHONY : clean
clean :
		rm -rf $(.DEFAULT_GOAL) *.o