#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


int XDIM = 10000;
int YDIM = 10000;

// We return the pointer
float **alloc_matrix(void) /* Allocate the array */
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    float **array;
    array = calloc((size_t)XDIM, sizeof(float *));
    for(int i = 0 ; i < XDIM ; i++)
        array[i] = calloc((size_t)YDIM, sizeof(float));
    return array;
}


void fill(float** arr) {
    int i, j;
    time_t t1; 
    srand ( (unsigned) time (&t1));
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j++)
            arr[i][j] = (float)(rand() % 100);
}

void compute(float** arr, int kern[3][3]){
    float tmp_sum[9];
    float dato, accum;
    int i, j, k, l;
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j++){
            //printf("processing: %d - %d \n", i, j);
            if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1){
                for(k = 0; k < 3; k++)
                    for(l = 0; l < 3; l++){
                        int x = i + (l-1);
                        int y = j + (k-1);
                        dato = arr[x][y];
                        tmp_sum[l*3+k] = 2.0f*(2.0f*(float)kern[l][k]*dato)/1000.0f + 1.0f;
                    }

                accum = 0;
                for(k = 0; k < 3; k++)
                    for(l = 0; l < 3; l++)
                        accum = accum + tmp_sum[k*3+l];
  
            }
            arr[i][j] = accum;
        }    
}



void print(float** arr) {
    FILE *file = fopen("output","w");
    for(int i = 0 ; i < XDIM ; i++)
        for(int j = 0 ; j < YDIM ; j++)
            fprintf(file,"array[%d][%d] = %f\n", i, j, arr[i][j]);
    fclose(file);
}


int main(void)
{
    float **arr;
    int kern[3][3] = {{0, -1, 0},{-1, 5, -1},{0, -1, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    return 0;
}
