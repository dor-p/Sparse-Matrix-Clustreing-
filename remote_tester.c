#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include <assert.h> 


typedef struct _int_set{
  int size;
  int* set;
} int_set;

char* int_to_string(int n){
    char* res;
    int len, i;
    len = n < 0 ? 3 : 2;
    if(abs(n) >= 10){
        len += (int)(floor( log10( (double)abs(n) ) ));
    }
    res = (char*)malloc(len * sizeof(char));
    res[len - 1] = '\0';
    if(n < 0) res[0] = '-';
    i = len - 2;
    n = abs(n);
    if(n == 0) res[0] = '0';
    while(n > 0){
        res[i--] = (n % 10) + '0';
        n /= 10;
    }
    return res;
}

int comp_int(const void* a, const void* b){
  return (int*)a - (int*)b;
}

int set_of_sets_equal(int** a, int* a_size, int ** b, int* b_size, int n){
    int i, j, done[2][n];
    char* s;
    
    for(i = 0; i < n; i++){
      done[0][i] = 0;
        done[1][i] = 0;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
          if(a_size[i] == b_size[j] && !done[j]){
            if(!memcmp(a[i], b[j], a_size[i] * sizeof(int))){
              done[1][j] = 1;
              done[0][i] = 1;
            }
          }
        }
        if(done[0][i] == 0){
          return i;
        }
    }
    return -1;
}

int read_set_of_sets(char* filename, int_set** S){
  FILE* file;
  int i, j, n;

  file = fopen(filename, "r");
    fread(&n, sizeof(int), 1, file);
    *S = (int_set*)malloc(n * sizeof(int_set));
    for(i = 0; i < n; i++){
      fread(&((*S)[i]->size), sizeof(int), 1, file);
      (*S)[i]->set = (int*)malloc((*S)[i]->size * sizeof(int));
      fread((*S)[i]->set, sizeof(int), (*S)[i]->size, file);
      qsort((*S)[i]->set, (*S)[i]->size, sizeof(int), comp_int);
      for(j = 0; j < (*S)[i]->size - 1; j++){
        if((*S)[i]->set[j] == (*S)[i]->set[j + 1]){
          return i;
        }
      }
    }
    fclose(file);
    return -1;
}

int compare_sets_by_size(const void *a, const void *b){
  
}

int main(int argc, char* argv[]){
    int **a, *Sa, **b, *Sb, n, i;
    FILE* file;
    assert(argc > 2);

    file = fopen(argv[1], "r");
    fread(&n, sizeof(int), 1, file);
    fclose(file);
    file = fopen(argv[2], "r");
    fread(&i, sizeof(int), 1, file);
    fclose(file);
    if(n != i){
      printf("Wrong number of sets\nFirst file has %d and second file has %d\n", n, i);
      return 0;
    }


    i = read_set_of_sets(argv[1], &a, &Sa);
    if(i >= 0){
      printf("First file has a repetition in set %d\n", i);
      return 0;
    }
    i = read_set_of_sets(argv[2], &b, &Sb);
    if(i >= 0){
      printf("Second file has a repetition in set %d\n", i);
      return 0;
    }
    i = set_of_sets_equal(a, Sa, b, Sb, n);
    if(i >= 0){
      printf("Problem in set number %d of first file\n", i);
      return 0;
    }
    printf("All good\n");
    
    return 0;
}


