FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: matrix_functions.o group_functions.o main.o sub_graph read_write_graph b_matrix
	gcc $(FLAGS) spmat_lists.o linked_list.o set_of_sets.o read_write_graph.o sub_graph.o b_matrix.o matrix_functions.o group_functions.o main.o -o cluster $(LIBS)
matrix_functions.o: matrix_functions.c
	gcc $(FLAGS) -c matrix_functions.c 
group_functions.o: group_functions.c
	gcc $(FLAGS) -c group_functions.c
main.o: main.c
	gcc $(FLAGS) -c main.c

linked_list: linked_list.c linked_list.h
	gcc $(FLAGS) -c linked_list.c

spmat_lists: spmat_lists.c spmat_lists.h linked_list
	gcc $(FLAGS) -c spmat_lists.c

b_matrix: b_matrix.h b_matrix.c spmat_lists
	gcc $(FLAGS) -c b_matrix.c

set_of_sets: set_of_sets.h set_of_sets.c linked_list
	gcc $(FLAGS) -c set_of_sets.c

read_write_graph: read_write_graph.h read_write_graph.c set_of_sets spmat_lists
	gcc $(FLAGS) -c read_write_graph.c

sub_graph: sub_graph.h sub_graph.c spmat_lists
	gcc $(FLAGS) -c sub_graph.c

