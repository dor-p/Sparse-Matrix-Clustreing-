/*
 * spmat.c
 *
 *  Created on: 27 Apr 2020
 *      Author: computer
 */

#include "spmat.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct _Arrays {
    double *vals;
    int *cols, *next_non_zero;
    int next_to_fill, nnz;

} Arrays;

void add_rows_arrays (struct _spmat *A, const double *row, int i){
    int j, n, nxt;
    Arrays *arr = (Arrays*)A->private;
    n = A->n;
    nxt = arr->next_to_fill;

    for(j = 0; j < n; j++){
        if(row[j] != 0.0){
        	arr->vals[arr->next_to_fill] = row[j];
        	arr->cols[arr->next_to_fill] = j;
        	arr->next_to_fill++;
        }
    }

    arr->next_non_zero[i] = arr->next_to_fill > nxt ? nxt : arr->next_non_zero[n];
    if(i == n - 1){
        for(j = n - 2; j >= 0; j--){
            if(arr->next_non_zero[j] == -1){
            	arr->next_non_zero[j] = arr->next_non_zero[j + 1];
            }
        }
    }
}

void free_arr (struct _spmat *A){
	Arrays *arr = (Arrays*)A->private;
    free(arr->vals);
    free(arr->cols);
    free(arr->next_non_zero);
    free(A->private);
    free(A);
}

void mult_arr (const struct _spmat *A, const double *v, double *result){
    int i, j, n;
    Arrays *arr = (Arrays*)A->private;
    n = A->n;
    for(i = 0; i < n; i++){
        result[i] = 0.0;
        if(arr->next_non_zero[i] != arr->next_non_zero[i + 1]){
            for(j = arr->next_non_zero[i]; j < arr->next_non_zero[i + 1]; j++){
                result[i] += arr->vals[j] * v[arr->cols[j]];
            }
        }
    }
}

spmat* spmat_allocate_array(int n, int nnz){
    double *vals = (double*)malloc(nnz * sizeof(double));
    int *cols = (int*)malloc(nnz * sizeof(int));
    int *next_non_zero = (int*)malloc((n + 1) * sizeof(int));
    spmat* res = (spmat*)malloc(sizeof(spmat));
    assert(vals != NULL);
    assert(cols != NULL);
    assert(next_non_zero != NULL);
    assert(res != NULL);
    next_non_zero[n] = nnz;
    res->n = n;
    res->private = (Arrays*)malloc(sizeof(Arrays));
    assert(res->private != NULL);
    ((Arrays*)res->private)->vals = vals;
    ((Arrays*)res->private)->cols = cols;
    ((Arrays*)res->private)->next_non_zero = next_non_zero;
    ((Arrays*)res->private)->next_to_fill = 0;
    res->add_row = add_rows_arrays;
    res->free = free_arr;
    res->mult = mult_arr;
    return res;
}

/*done with array*/

/*now lists*/
    
typedef struct _linkedList {
    double val;
    int col;
    struct _linkedList *next;
    
} linkedList;

void add_at_start(linkedList *lst, double value, int column){
    linkedList* nxt;
    assert(lst != NULL);
    nxt = (linkedList*)malloc(sizeof(linkedList));
    assert(nxt != NULL);
    nxt->val = lst->val;
    nxt->col = lst->col;
    nxt->next = lst->next;

    lst->val = value;
    lst->col = column;
    lst->next = nxt;
}

void free_LL_s(linkedList *lst){
    linkedList* nxt = lst->next;
    free(lst);
    if(nxt != NULL){
    	free_LL_s(nxt);
    }
}

linkedList* linkedList_allocate(double value, int column){
    linkedList* res = (linkedList*)malloc(sizeof(linkedList));
    assert(res != NULL);
    res->val = value;
    res->col = column;
    res->next = NULL;
    return res;
}



void add_row_lists (struct _spmat *A, const double *row, int i){
    int j, n;
    linkedList* rowList;
    n = A->n;
    for(j = n - 1; j >= 0; j--){
        if(row[j] != 0.0){
            break;
        }
    }
    if(j == -1){
        return;
    }
    ((linkedList**)A->private)[i] = linkedList_allocate(row[j], j);
    j--;
    rowList = ((linkedList**)A->private)[i];
    while(j >= 0){
        if(row[j] != 0.0){
        	add_at_start(rowList, row[j], j);
        }
        j--;
    }
}

void free_LL_mat (struct _spmat *A){
    int i, n;
    linkedList** rows = ((linkedList**)A->private);
	n = A->n;
    for(i = 0; i < n; i++){
    	if(rows[i] != NULL){
    		free_LL(rows[i]);
    	}
    }
    free(rows);
    free(A);
}

void mult_LL(const struct _spmat *A, const double *v, double *result){
    int i, n;
    linkedList* curr;
    linkedList **rows;
    rows = (linkedList**)A->private;
    n = A->n;
    for(i = 0; i < n; i++){
        curr = rows[i];
        result[i] = 0.0;
        while(curr != NULL){
            result[i] += curr->val * v[curr->col];
            curr = curr->next;
        }
    }
}

spmat* spmat_allocate_list(int n){
	int i;
	linkedList **rows = (linkedList**)malloc(n * sizeof(linkedList*));
	spmat* res = malloc(sizeof(spmat));
	assert(rows != NULL);
    assert(res != NULL);
	for(i = 0; i < n; i++){
		rows[i] = NULL;
	}
    res->n = n;
    res->private = rows;
    res->add_row = add_row_lists;
    res->free = free_LL_mat;
    res->mult = mult_LL;
    return res;
}
