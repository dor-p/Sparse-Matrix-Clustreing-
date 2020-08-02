FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: matrix_functions.o group_functions.o main.o
	gcc matrix_functions.o group_functions.o main.o -o cluster $(LIBS)
matrix_functions.o: matrix_functions.c
	gcc $(FLAGS) -c matrix_functions.c 
group_functions.o: group_functions.c
	gcc $(FLAGS) -c group_functions.c
main.o: main.c
	gcc $(FLAGS) -c main.c


