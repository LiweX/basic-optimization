#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


int XDIM = 10000;
int YDIM = 10000;

// We return the pointer
double **alloc_matrix(void) /* Allocate the array */
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    double **array;
    array = calloc((size_t)XDIM, sizeof(double *));
    for(int i = 0 ; i < XDIM ; i++)
        array[i] = calloc((size_t)YDIM, sizeof(double));
    return array;
}


void fill(double** arr) {
    int i, j;
    time_t t1; 
    srand ( (unsigned) time (&t1));
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j+=10){
            arr[i][j] = (double)(rand() % 100);
            arr[i][j+1] = (double)(rand() % 100);
            arr[i][j+2] = (double)(rand() % 100);
            arr[i][j+3] = (double)(rand() % 100);
            arr[i][j+4] = (double)(rand() % 100);
            arr[i][j+5] = (double)(rand() % 100);
            arr[i][j+6] = (double)(rand() % 100);
            arr[i][j+7] = (double)(rand() % 100);
            arr[i][j+8] = (double)(rand() % 100);
            arr[i][j+9] = (double)(rand() % 100);
            
        }

}

void compute(double** arr, int kern[3][3]){
    double tmp_sum[9];
    double dato, accum;
    int i, j;
    for(i = 1 ; i < XDIM-1 ; i++)
        for(j = 1 ; j < YDIM-1 ; j++){
            //printf("processing: %d - %d \n", i, j);
            
                        dato = arr[i - 1][j - 1];
                        tmp_sum[0] = (2.0*(double)kern[0][0]*dato)*0.002 + 1.0;
                        dato = arr[i][j - 1];
                        tmp_sum[3] = (2.0*(double)kern[1][0]*dato)*0.002 + 1.0;
                        dato = arr[i + 1][j - 1];
                        tmp_sum[6] = (2.0*(double)kern[2][0]*dato)*0.002 + 1.0;
                        dato = arr[i - 1][j];
                        tmp_sum[1] = (2.0*(double)kern[0][1]*dato)*0.002 + 1.0;
                        dato = arr[i][j];
                        tmp_sum[4] = (2.0*(double)kern[1][1]*dato)*0.002 + 1.0;
                        dato = arr[i + 1][j];
                        tmp_sum[7] = (2.0*(double)kern[2][1]*dato)*0.002 + 1.0;
                        dato = arr[i - 1][j + 1];
                        tmp_sum[2] = (2.0*(double)kern[0][2]*dato)*0.002 + 1.0;
                        dato = arr[i][j + 1];
                        tmp_sum[5] = (2.0*(double)kern[1][2]*dato)*0.002 + 1.0;
                        dato = arr[ i + 1][j + 1];
                        tmp_sum[8] = (2.0*(double)kern[2][2]*dato)*0.002 + 1.0;

                    

                accum = 0;
                
                   
                        accum = accum + tmp_sum[0];
                        accum = accum + tmp_sum[1];
                        accum = accum + tmp_sum[2];
                        accum = accum + tmp_sum[3];
                        accum = accum + tmp_sum[4];
                        accum = accum + tmp_sum[5];
                        accum = accum + tmp_sum[6];
                        accum = accum + tmp_sum[7];
                        accum = accum + tmp_sum[8];
                    
            arr[i][j] = accum;
        }    
}



void print(double** arr) {
    FILE *file = fopen("output.txt","w");
    for(int i = 0 ; i < XDIM ; i++)
        for(int j = 0 ; j < YDIM ; j+=10){
            fprintf(file,"array[%d][%d] = %f\n", i, j, arr[i][j]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+1, arr[i][j+1]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+2, arr[i][j+2]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+3, arr[i][j+3]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+4, arr[i][j+4]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+5, arr[i][j+5]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+6, arr[i][j+6]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+7, arr[i][j+7]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+8, arr[i][j+8]);
            fprintf(file,"array[%d][%d] = %f\n", i, j+9, arr[i][j+9]);
        }
    fclose(file);
}


int main(void)
{
    double **arr;
    int kern[3][3] = {{0, -1, 0},{-1, 5, -1},{0, -1, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    return 0;
}
