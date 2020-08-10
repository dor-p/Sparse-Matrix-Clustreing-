
#include "group_functions.h"
#include "matrix_functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int modularity_maximization(SparseMatrix* hatB, double *s){
  double bk, M, bestM, *bestS, *delta, *stag, *sTempResult;
  int i, k, changed,moved, *hasMoved;
  Node *currentNode;

  bestS = (double*)malloc(hatB->n * sizeof(double));
  if(bestS == NULL){
    free(bestS);
    return 0;
  }

  stag = (double*)malloc(hatB->n * sizeof(double));
  if(stag == NULL){
    free(bestS);
    free(stag);
    return 0;
  }

  sTempResult = (double*)malloc(hatB->n * sizeof(double));
  if(stag == NULL){
    free(bestS);
    free(stag);
    return 0;
  }

  delta = (double*)malloc(hatB->n * sizeof(double));
  if(delta == NULL){
    free(bestS);
    free(stag);
    free(delta);
    return 0;
  }

  hasMoved = (int*)malloc(hatB->n*sizeof(int));
  if(delta == NULL){
    free(bestS);
    free(stag);
    free(delta);
    free(hasMoved);
    return 0;
  }
  memcpy(bestS, s, hatB->n * sizeof(double));
  matrix_mult_left(s, *hatB, sTempResult);
  memcpy(s, sTempResult, hatB->n * sizeof(double));
  bestM = dot(s, bestS, hatB->n);

  do{
    memcpy(s, bestS, hatB->n * sizeof(double));
    M = bestM;
    for(i = 0; i < hatB->n; i++){
      hasMoved[i] = 0;
    }
    moved = 0;

    while(moved < hatB->n){
      matrix_mult_left(s, *hatB, stag);
      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->rows[i];
        while(currentNode != NULL && currentNode->column < i){
          currentNode = currentNode->right;
        }
        bk = (currentNode != NULL && currentNode->column == i) ? currentNode->value : 0;
        delta[i] = s[i] * (2 * bk - stag[i]);
      }

      for(i = 0; i < hatB->n; i++){
        currentNode = hatB->rows[i];
        while(currentNode != NULL){
          delta[currentNode->column] -= s[i] * s[currentNode->column] * currentNode->value;
        }
      }

      k = 0;
      for(i = 0; i < hatB->n; i++){
        if(delta[i] > delta[k]) k = i;
      }
      M += delta[k];
      memcpy(stag, s, hatB->n * sizeof(double));
      stag[k] *= -1;

      moved++;
      hasMoved[k] = 1;

      if(M > bestM){
        bestM = M;
        memcpy(bestS, stag, hatB->n * sizeof(double));
      }

    }

    changed = memcmp(s, bestS, hatB->n * sizeof(double));

  } while(changed);

  memcpy(s, bestS, hatB->n * sizeof(double));

  free(bestS);
  free(stag);
  free(delta);
  free(hasMoved);
  free(sTempResult);
  return 1;
}

GroupSet group_set_allocate_capacity(int capacity)
{
	GroupSet groupSet;
	int i;

	groupSet.groups = (Group*)malloc(capacity * sizeof(Group));
	if (groupSet.groups == NULL)
	{
		groupSet.size = 0;
		groupSet.capacity = 0;
		return groupSet;
	}
	groupSet.capacity = capacity;
	groupSet.size = 0;

	for (i = 0; i < capacity; ++i)
	{
		groupSet.groups[i].indices = NULL;
		groupSet.groups[i].size = 0;
		groupSet.groups[i].capacity = 0;
	}

	return groupSet;
}

GroupSet group_set_create(int vertexCount)
{
	GroupSet groupSet;
	int i;

	groupSet.groups = (Group*)malloc(vertexCount * sizeof(Group));
	if (groupSet.groups == NULL)
	{
		groupSet.size = 0;
		groupSet.capacity = 0;
		return groupSet;
	}
	groupSet.capacity = vertexCount;
	groupSet.size = 1;

	groupSet.groups[0] = group_create(vertexCount);
	if (groupSet.groups[0].indices == NULL)
	{
		free(groupSet.groups);
		groupSet.size = 0;
		groupSet.capacity = 0;
		return groupSet;
	}
	for (i = 1; i < vertexCount; ++i)
	{
		groupSet.groups[i].indices = NULL;
		groupSet.groups[i].size = 0;
		groupSet.groups[i].capacity = 0;
	}

	return groupSet;
}

Group group_allocate_capacity(int capacity)
{
	Group group;

	group.indices = (int*)malloc(capacity * sizeof(int));
	if (group.indices == NULL)
	{
		group.size = 0;
		group.capacity = 0;
		return group;
	}
	group.capacity = capacity;
	group.size = 0;

	return group;
}

Group group_create(int vertexCount)
{
	Group group;
	int i;

	group.indices = (int*)malloc(vertexCount * sizeof(int));
	if (group.indices == NULL)
	{
		group.size = 0;
		group.capacity = 0;
		return group;
	}
	for (i = 0; i < vertexCount; ++i)
	{
		group.indices[i] = i;
	}
	group.capacity = vertexCount;
	group.size = vertexCount;

	return group;
}

void group_set_free(GroupSet* groupSet)
{
	int i;

	if (groupSet->groups != NULL)
	{
		for (i = 0; i < groupSet->size; ++i)
		{
			group_free(&(groupSet->groups[i]));
		}
		free(groupSet->groups);
		groupSet->groups = NULL;
	}
	groupSet->size = 0;
	groupSet->capacity = 0;
}

void group_free(Group* group)
{
	if (group->indices != NULL)
	{
		free(group->indices);
		group->indices = NULL;
	}
	group->size = 0;
	group->capacity = 0;
}

Group group_set_remove_group(GroupSet* groupSet)
{
	groupSet->size--;

	return groupSet->groups[groupSet->size];
}

void group_set_add_group(GroupSet* groupSet, Group* group)
{
	int i;
	int j;

	for (i = 0; i < groupSet->size; ++i)
	{
		if (groupSet->groups[i].indices[0] > group->indices[0])
		{
			for (j = groupSet->size - 1; j >= i; --j)
			{
				groupSet->groups[j + 1] = groupSet->groups[j];
			}
			groupSet->groups[i] = *group;
			groupSet->size++;
			*group = group_allocate_capacity(0);
			return;
		}
	}
	groupSet->groups[groupSet->size] = *group;
	groupSet->size++;
	*group = group_allocate_capacity(0);
}

int group_divide(SparseMatrix mat, Group g, Group* g1, Group* g2)
{
	SparseMatrix subModularity;
	double* eigenVector;
	double* s;
	double* v;
	double eigenValue;
	int i;
	Group* group;

	*g1 = group_allocate_capacity(0);
	*g2 = group_allocate_capacity(0);
	subModularity = matrix_submatrix(mat, g.indices, g.size);
	if (subModularity.n == 0)
	{
		return -1;
	}
	if (matrix_modify_submodularity(subModularity) == -1)
	{
		printf("Error: couldn't allocate memory!\n");
		matrix_free(&subModularity);
		return -1;
	}
	eigenVector = random_vector(subModularity.n);
	if (eigenVector == NULL)
	{
		matrix_free(&subModularity);
		return -1;
	}
	if (matrix_leading_eigenpair(subModularity, &eigenVector, &eigenValue) == -1)
	{
		free(eigenVector);
		matrix_free(&subModularity);
		return -1;
	}
	if (eigenValue > 0.0) /*divisible*/
	{
		s = (double*)malloc(subModularity.n * sizeof(double));
		if (s == NULL)
		{
			matrix_free(&subModularity);
			free(eigenVector);
			return -1;
		}
		for (i = 0; i < subModularity.n; ++i)
		{
			s[i] = eigenVector[i] > 0.0 ? 1.0 : -1.0;
		}
    modularity_maximization(&subModularity, s);
		v = (double*)malloc(subModularity.n * sizeof(double));
		if (v == NULL)
		{
			matrix_free(&subModularity);
			free(eigenVector);
			free(s);
			return -1;
		}
		matrix_mult_left(s, subModularity, v);
		if (dot(v, s, subModularity.n) > 0.0) /*divisible*/
		{
			for (i = 0; i < subModularity.n; ++i)
			{
				if (s[i] > 0.0)
				{
					group = g1;
				}
				else
				{
					group = g2;
				}

				if (group->capacity == 0)
				{
					*group = group_allocate_capacity(subModularity.n);
					if (group->indices == NULL)
					{
						matrix_free(&subModularity);
						free(eigenVector);
						free(s);
						free(v);
						return -1;
					}
				}
				group->indices[group->size] = g.indices[i];
				group->size++;
			}
		}
	}

	return 0;
}

void group_print(Group group)
{
	int i;

	for (i = 0; i < group.size; ++i)
	{
		printf("%d ", group.indices[i]);
	}
    printf("\n");
}

void group_set_print(GroupSet groupSet)
{
	int i;

	for (i = 0; i < groupSet.size; ++i)
	{
		group_print(groupSet.groups[i]);
	}

	if (groupSet.size == 0)
	{
		printf("\n");
	}
}

int group_set_write(GroupSet groupSet, const char* filename)
{
	FILE* file;
	int as;
	int i;
	int j;

	file = fopen(filename, "w");
	if (file == NULL)
	{
		return -1;
	}

	as = fwrite(&groupSet.size, sizeof(int), 1, file);
	if (as != 1)
	{
		fclose(file);
		return -1;
	}

	for (i = 0; i < groupSet.size; ++i)
	{
		as = fwrite(&groupSet.groups[i].size, sizeof(int), 1, file);
		if (as != 1)
		{
			fclose(file);
			return -1;
		}
		for (j = 0; j < groupSet.groups[i].size; ++j)
		{
			as = fwrite(&groupSet.groups[i].indices[j], sizeof(int), 1, file);
			if (as != 1)
			{
				fclose(file);
				return -1;
			}
		}
	}

	fclose(file);

	return 0;
}



