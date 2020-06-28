FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster
	
linked_list.o: linked_list.c linked_list.h
	gcc $(FLAGS) -c linked_list.c
	
norm_1.o: norm_1.c b_matrix.h b_matrix.o
	gcc $(FLAGS) -c norm_1.c
	
b_matrix.o: b_matrix.h spmat_lists.o

spmat_lists.o: spmat_lists.c spmat_lists.h linked_list.o
	gcc $(FLAGS) -c spmat_lists.c
