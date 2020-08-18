#include "matrix_functions.h"
#include "group_functions.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	SparseMatrix* mat;
	GroupSet P;
	GroupSet O;
	Group g;
	Group g1;
	Group g2;

	if (argc < 3)
	{
		printf("3 arguments required!\n");
		return -1;
	}

	mat = matrix_read(argv[1]);
	if (mat->n  == 0)
	{
		return -1;
	}

	if (mat->n == 0)
	{
		O = group_set_allocate_capacity(0);
	}
	else 
	{
		P = group_set_create(mat->n);
		if (P.groups == NULL)
		{
			printf("Error: couldn't allocate memory!\n");
			matrix_free(mat);
			group_set_free(&P);
			return -1;
		}

		O = group_set_allocate_capacity(mat->n);
		if (O.groups == NULL)
		{
			printf("Error: couldn't allocate memory!\n");
			matrix_free(mat);
			group_set_free(&P);
			group_set_free(&O);
			return -1;
		}

		while (P.size != 0)
		{
			g = group_set_remove_group(&P);
			g1 = group_allocate_capacity(0);
			g2 = group_allocate_capacity(0);

			if (group_divide(*mat, g, &g1, &g2) == -1)
			{
				group_free(&g);
				group_set_free(&P);
				group_set_free(&O);
				matrix_free(mat);
				return -1;
			}

			if (g1.size == 0 || g2.size == 0)
			{
				group_set_add_group(&O, &g);
				group_free(&g1);
				group_free(&g2);

			}
			else
			{
				if (g2.size > 1)
				{
					group_set_add_group(&P, &g2);
				}
				else if (g2.size == 1)
				{
					group_set_add_group(&O, &g2);
				}

				if (g1.size > 1)
				{
					group_set_add_group(&P, &g1);
				}
				else if (g1.size == 1)
				{
					group_set_add_group(&O, &g1);
				}

			    group_free(&g);
			}
		}

		group_set_print(O);
		if (group_set_write(O, argv[2]) == -1)
		{
			group_free(&g);
			group_free(&g1);
			group_free(&g2);
			group_set_free(&O);
			group_set_free(&P);
			matrix_free(mat);
			return -1;
		}

		group_free(&g);
		group_free(&g1);
		group_free(&g2);
		group_set_free(&O);
		group_set_free(&P);
		matrix_free(mat);
	}

	return 0;
}
