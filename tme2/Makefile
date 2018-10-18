GCC_FLAGS = -Wall -g
CC = gcc

all : mytimes mytimes3 mytimes4 exo5

exo2.o : exo2.c exo2.h
	${CC} ${GCC_FLAGS} -c $^

exo3.o : exo3.c exo2.h
	${CC} ${GCC_FLAGS} -c $^

exo4.o : exo4.c exo2.h
	${CC} ${GCC_FLAGS} -c $^

exo5 : exo5.c
	${CC} ${GCC_FLAGS} -o $@ $^

mytimes : exo2.o mytimes.c
	${CC} ${GCC_FLAGS} -o $@ $^

mytimes3 : exo3.o mytimes.c
	${CC} ${GCC_FLAGS} -o $@ $^

mytimes4 : exo4.o mytimes.c
	${CC} ${GCC_FLAGS} -o $@ $^

clean : 
	rm *.o


