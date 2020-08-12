FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: b_matrix.o helper_functions.o linked_list.o norm_1_test.o power_iteration_test.o power_iteration.o read_write_graph_test.o read_write_graph.o set_of_sets_test.o set_of_sets.o spmat_lists_test.o spmat_lists.o sub_graph_test.o
	gcc  b_matrix.o helper_functions.o linked_list.o norm_1_test.o power_iteration_test.o power_iteration.o read_write_graph_test.o read_write_graph.o set_of_sets_test.o set_of_sets.o spmat_lists_test.o spmat_lists.o sub_graph_test.o -o cluster $(LIBS)
b_matrix.o: b_matrix.c
	gcc $(FLAGS) -c b_matrix.c 
helper_functions.o: helper_functions.c
	gcc $(FLAGS) -c helper_functions.c
linked_list.o: linked_list.c
	gcc $(FLAGS) -c linked_list.c
norm_1_test.o: norm_1_test.c
	gcc $(FLAGS) -c norm_1_test.c
power_iteration_test.o: power_iteration_test.c
	gcc $(FLAGS) -c power_iteration_test.c
power_iteration.o: power_iteration.c
	gcc $(FLAGS) -c power_iteration.c
read_write_graph_test.o: read_write_graph_test.c
	gcc $(FLAGS) -c read_write_graph_test.c
read_write_graph.o: read_write_graph.c
	gcc $(FLAGS) -c read_write_graph.c
set_of_sets_test.o: set_of_sets_test.c
	gcc $(FLAGS) -c set_of_sets_test.c
set_of_sets.o: set_of_sets.c
	gcc $(FLAGS) -c set_of_sets.c
spmat_lists_test.o: spmat_lists_test.c
	gcc $(FLAGS) -c spmat_lists_test.c
spmat_lists.o: spmat_lists.c
	gcc $(FLAGS) -c spmat_lists.c
spmat_lists.o: spmat_lists.c
	gcc $(FLAGS) -c spmat_lists.c



