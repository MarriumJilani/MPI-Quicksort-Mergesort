#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

//you can enter 11, 13, 15, 17 as command line parameters
//this program will read stored data and sort and store it in files
double operation_count=0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
	
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
	    operation_count++;
            operation_count++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
	operation_count++;operation_count++;operation_count++;
    }
}

int main(int argc, char *argv[]) {
  int size;
  if (argc != 2) {
    printf("You must specify the parameter: ./program_name <size>\n");
    return 1;
  }

  size = atoi(argv[1]);
 
//we have four options for array size: 2^11=2048, 2^13= 8192, 2^15=32768, 2^17=131072
struct timeval start, end;

if(size==11)
{
    gettimeofday( &start, NULL );

    int arr[2048], size;
    FILE *fp_in, *fp_out;
   
    fp_in = fopen("array2^11.txt", "r");
    if(fp_in == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    int i = 0;
    while(fscanf(fp_in, "%d", &arr[i]) != EOF) {
        i++;
    }

    fclose(fp_in);
    printf("Array read from array2^11.txt file.\n");
   
     quicksort(arr, 0,2047);

//store sorted array in file

    fp_out = fopen("2^11_qsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }


    for(int i = 0; i < 2048; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^11_qsorted.txt file.\n");

    gettimeofday( &end, NULL );
}

else if(size==13)
{
    gettimeofday( &start, NULL );

    int arr[8192], size;
    FILE *fp_in, *fp_out;
   
    fp_in = fopen("array2^13.txt", "r");
    if(fp_in == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    int i = 0;
    while(fscanf(fp_in, "%d", &arr[i]) != EOF) {
        i++;
    }

    fclose(fp_in);
    printf("Array read from array2^13.txt file.\n");
   
     quicksort(arr, 0, 8191);

//store sorted array in file

    fp_out = fopen("2^13_qsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    for(int i = 0; i < 8192; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^13_qsorted.txt file.\n");

    gettimeofday( &end, NULL );
}

else if(size==15)
{
    gettimeofday( &start, NULL );

    int arr[32768], size;
    FILE *fp_in, *fp_out;
   
    fp_in = fopen("array2^15.txt", "r");
    if(fp_in == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    int i = 0;
    while(fscanf(fp_in, "%d", &arr[i]) != EOF) {
        i++;
    }

    fclose(fp_in);
    printf("Array read from array2^15.txt file.\n");
   
     quicksort(arr, 0, 32767);

//store sorted array in file

    fp_out = fopen("2^15_qsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    for(int i = 0; i < 32768; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^11_qsorted.txt file.\n");

    gettimeofday( &end, NULL );
}

else if(size==17)
{
    gettimeofday( &start, NULL );

    int arr[131072], size;
    FILE *fp_in, *fp_out;
   
    fp_in = fopen("array2^17.txt", "r");
    if(fp_in == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    int i = 0;
    while(fscanf(fp_in, "%d", &arr[i]) != EOF) {
        i++;
    }

    fclose(fp_in);
    printf("Array read from array2^17.txt file.\n");
   
     quicksort(arr, 0, 131071);

//store sorted array in file

    fp_out = fopen("2^17_qsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    // Write the sorted array to the output file
    for(int i = 0; i < 131072; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    // Close the output file
    fclose(fp_out);

    printf("Array sorted and stored in 2^17_qsorted.txt file.\n");

    gettimeofday( &end, NULL );
}
/* convert time to Gflop/s */
   double seconds = (end.tv_sec - start.tv_sec) +
   1.0e-6 * (end.tv_usec - start.tv_usec);
   
   double Gflops = 2e-9*operation_count/seconds;
   printf( "Performance in Gflops %.3f Gflop/s\n", Gflops );
  return 0;
}
	

