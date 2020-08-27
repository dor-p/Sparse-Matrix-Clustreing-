#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include <assert.h> 

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


char* sets_equal(int* a, int* b, int n){
    int i, j, *tmp;
    tmp = (int*)calloc(n, sizeof(int));
    for(i = 0; i < n; i++){        
        for(j = 0; j < n; j++){
            if(b[j] == a[i]){
                if(tmp[i] == 1){
                    return (int_to_string(a[i]), " appears twice");
                }
                tmp[i] = 1;
                break;
            }
        }
        if(tmp[i] == 0){
            return strcat(int_to_string(a[i]), " is not in b");
    }
    return "all good";
}

int set_of_sets_equal(int** a, int* a_size, int* b_size, int ** b, int n){
    int i, j, done[n];
    char* s;
    
    for(i = 0; i < n; i++){
        done[i] = 0;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(a_size[i] != b_size[j] || done[j]) continue;
            s = sets_equal(a[i], b[i], a_size[i]);
            if(strcmp(s, "all good") == 0){
                done[j] = 1;
                break;
            }
        }
        return i;
    }
    return -1;
}


int main(int argc, char* argv[]){
    int **a, *Sa, **b, *Sb; 
    assert(argc > 2);
    
    return 0;
}


