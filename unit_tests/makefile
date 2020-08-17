FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cluster
clean:
	rm -rf *.o cluster

cluster: b_matrix.o helper_functions.o linked_list.o norm_1.o power_iteration.o read_write_graph.o set_of_sets.o spmat_lists.o sub_graph.o modularity_maximization.o cluster.o cluster_test.c
	gcc  b_matrix.o helper_functions.o linked_list.o norm_1.o power_iteration.o   read_write_graph.o set_of_sets.o  spmat_lists.o sub_graph.o modularity_maximization.o cluster.o cluster_test.c -o cluster_test $(LIBS)

b_matrix.o: b_matrix.c
	gcc $(FLAGS) -c b_matrix.c

helper_functions.o: helper_functions.c
	gcc $(FLAGS) -c helper_functions.c

linked_list.o: linked_list.c
	gcc $(FLAGS) -c linked_list.c

power_iteration.o: power_iteration.c
	gcc $(FLAGS) -c power_iteration.c

read_write_graph.o: read_write_graph.c
	gcc $(FLAGS) -c read_write_graph.c

set_of_sets.o: set_of_sets.c
	gcc $(FLAGS) -c set_of_sets.c

spmat_lists.o: spmat_lists.c
	gcc $(FLAGS) -c spmat_lists.c

norm_1.o: norm_1.c
	gcc $(FLAGS) -c norm_1.c

sub_graph.o: sub_graph.c
	gcc $(FLAGS) -c sub_graph.c

modularity_maximization.o:  modularity_maximization.c
	gcc $(FLAGS) -c modularity_maximization.c

cluster.o: cluster.c
	gcc $(FLAGS) -c cluster.c
  



linked_list: linked_list.o helper_functions.o linked_list_test.c
	gcc $(FLAGS) linked_list_test.c -c
	gcc $(FLAGS) helper_functions.o linked_list.o linked_list_test.o -o linked_list_test $(LIBS)

norm_1_test: helper_functions.o linked_list.o spmat_lists.o norm_1.o b_matrix.o norm_1_test.c
	gcc $(FLAGS) -c norm_1_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o norm_1.o b_matrix.o norm_1_test.o -o norm_1_test $(LIBS)

power_iteration: helper_functions.o linked_list.o spmat_lists.o  b_matrix.o read_write_graph.o power_iteration.o power_iteration_test.c
	gcc $(FLAGS) -c power_iteration_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o read_write_graph.o b_matrix.o power_iteration.o power_iteration_test.o -o power_iteration_test $(LIBS)

read_write_graph: helper_functions.o linked_list.o spmat_lists.o set_of_stes.o read_write_graph_test.c
	gcc $(FLAGS) -c read_write_graph_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o read_write_graph.o b_matrix.o set_of_stes.o read_write_graph_test.o -o read_write_graph_test $(LIBS)

set_of_sets: helper_functions.o linked_list.o set_of_sets_test.c
	gcc $(FLAGS) -c set_of_sets_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o set_of_stes.o set_of_stes_test.o -o set_of_stes_test $(LIBS)

spmat_lists: helper_functions.o linked_list.o spmat_lists_test.c
	gcc $(FLAGS) -c spmat_lists_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o spmat_lists_test.o -o spmat_lists_test $(LIBS)

modularity_maximization: helper_functions.o linked_list.o spmat_lists.o b_matrix.o modularity_maximization.o modularity_maximization_test.c
	gcc $(FLAGS) -c modularity_maximization_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o  b_matrix.o modularity_maximization.o modularity_maximization_test.o -o modularity_maximization_test $(LIBS)

b_matrix: helper_functions.o linked_list.o spmat_lists.o b_matrix.o read_write_graph.o b_matrix_test.c
	gcc $(FLAGS) -c b_matrix_test.c
	gcc $(FLAGS) helper_functions.o linked_list.o spmat_lists.o read_write_graph.o b_matrix.o b_matrix_test.o -o b_matrix_test $(LIBS)

