FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster
	
cluster: cluster.c modularity_maximization power_iteration norm_1 sub_graph
	gcc $(FLAGS) linked_list.o spmat_lists.o b_matrix.o norm_1.o set_of_sets.o sub_graph.o power_iteration.o modularity_maximization.o cluster.o -o cluster $(LIBS)
	
linked_list: linked_list.c linked_list.h
	gcc $(FLAGS) -c linked_list.c
	
norm_1: norm_1.c b_matrix
	gcc $(FLAGS) -c norm_1.c
	
b_matrix: b_matrix.h bmatrix.c spmat_lists

spmat_lists: spmat_lists.c spmat_lists.h linked_list
	gcc $(FLAGS) -c spmat_lists.c

set_of_sets: set_of_sets.h set_of_sets.c linked_list


modularity_maximization: modularity_maximization.h modularity_maximization.c set_of_sets


power_iteration: power_iteration.h power_iteration.c b_matrix

sub_graph: sub_graph.h sub_graph.c spmat_lists


