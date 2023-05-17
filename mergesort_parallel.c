//basic algo for quicksort
//divide array into smaller arrays using mpi scatter()
//each processor will sort using quicksort
//each process will communicate result back to masterusing gather
//merge all sorted arrays using merge step of quicksort
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include<math.h>
#include <sys/time.h>
#include <time.h>
#include<mpi.h>

double operation_count=0;

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // temporary arrays here and then inn mein data copy
    int L[n1], R[n2];

    for(i = 0; i < n1; i++) {
        L[i] = arr[left + i];
	operation_count++;
	operation_count++;
    }
    for(j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
	operation_count++;
	operation_count++;
    }

    // now inn ko merge
    i = 0;
    j = 0;
    k = left;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
	    operation_count++;
	    operation_count++;
        }
        else {
            arr[k] = R[j];
            j++;
	    operation_count++;
	    operation_count++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
	operation_count++;
	operation_count++;
	operation_count++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
	operation_count++;operation_count++;operation_count++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;
	operation_count++;
	operation_count++;

        merge_sort(arr, left, mid);//left part

        merge_sort(arr, mid+1, right);//right part

        merge(arr, left, mid, right);
    }
}



//here code wo wala aaye ga jo arrays ko merge krnay k liyay hoga
int main(int argc, char *argv[]) {

struct timeval start, end;
  int size;
  if (argc != 2) {
    printf("You must specify the parameter: ./program_name <size>\n");
    return 1;
  }

  size = atoi(argv[1]);

int num_process, rank;
MPI_Status status;

    int mpi = MPI_Init(&argc, &argv);
gettimeofday( &start, NULL );
 
 
    if (mpi != MPI_SUCCESS) {
        printf("Error in creating MPI\n");
        MPI_Abort(MPI_COMM_WORLD, mpi);
    }
 
    MPI_Comm_size(MPI_COMM_WORLD, &num_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
int s_size=0;
int arr_size=0;
int *arr = (int *) malloc(2048 * sizeof(int));

if(size==11){
arr = (int *) realloc(arr,2048 * sizeof(int));}

else if(size==13){
arr = (int *) realloc(arr,8192 * sizeof(int));}

else if(size==15){
arr = (int *) realloc(arr,32768 * sizeof(int));}

else if(size==17){
arr = (int *) realloc(arr,131072 * sizeof(int));}

if(rank==0)
{
//filling array for 2^11
if(size==11){
    int arr_size=2048;
    //*arr = (int *) malloc(2048 * sizeof(int));
    for(int i = 0; i < 2048; i++) {
        arr[i]=rand()%100;}
    

        if(2048% num_process == 0)
	s_size=2048/num_process;
	else
	s_size=2048/num_process-1;
}

else if(size==13){
    int arr_size=8192;
    //*arr = (int *) malloc(2048 * sizeof(int));
    for(int i = 0; i < 8192; i++) {
        arr[i]=rand()%100;}
    

        if(8192% num_process == 0)
	s_size=8192/num_process;
	else
	s_size=8192/num_process-1;
}

else if(size==15){
    int arr_size=32768;
    //*arr = (int *) malloc(2048 * sizeof(int));
    for(int i = 0; i < 32768; i++) {
        arr[i]=rand()%100;}
    

        if(32768% num_process == 0)
	s_size=32768/num_process;
	else
	s_size=32768/num_process-1;
}

else if(size==17){
    int arr_size=131072;
    //*arr = (int *) malloc(2048 * sizeof(int));
    for(int i = 0; i < 131072; i++) {
        arr[i]=rand()%100;}
    

        if(131072% num_process == 0)
	s_size=131072/num_process;
	else
	s_size=131072/num_process-1;
}



    }
MPI_Barrier(MPI_COMM_WORLD);


int* data=(int*)malloc(s_size * sizeof(int));
MPI_Scatter(arr, s_size, MPI_INT, data ,s_size, MPI_INT, 0, MPI_COMM_WORLD);

//free(arr);
//calculating

int last=0;
if(arr_size >= s_size * (rank + 1))
{last =s_size;}
else
{last =arr_size- s_size * rank;}

 merge_sort(data, 0, last);

//int recv=(int*)malloc(s_size * sizeof(int));


MPI_Gather(data,s_size,MPI_INT,arr,arr_size,MPI_INT,0,MPI_COMM_WORLD);
if(size==11)
 merge_sort(arr, 0, 2047);

else if(size==13)
 merge_sort(arr, 0, 8191);

else if(size==15)
 merge_sort(arr, 0, 32767);

else if(size==17)
 merge_sort(arr, 0, 131071);


if(rank==0)
{
if(size==11){
 FILE *fp_out;
    fp_out = fopen("2^11_pmsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }


    for(int i = 0; i < 2048; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^11_pmsorted.txt file.\n");
}

if(size==13){
 FILE *fp_out;
    fp_out = fopen("2^13_pmsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }


    for(int i = 0; i < 8192; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^13_pmsorted.txt file.\n");
}

if(size==15){
 FILE *fp_out;
    fp_out = fopen("2^15_pmsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }


    for(int i = 0; i < 32768; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^15_pmsorted.txt file.\n");
}

if(size==17){
 FILE *fp_out;
    fp_out = fopen("2^17_pmsorted.txt", "w");
    if(fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }


    for(int i = 0; i < 131072; i++) {
        fprintf(fp_out, "%d ", arr[i]);
    }

    fclose(fp_out);

    printf("Array sorted and stored in 2^17_pmsorted.txt file.\n");
}
}
 gettimeofday( &end, NULL );
   double seconds = (end.tv_sec - start.tv_sec) +
   1.0e-6 * (end.tv_usec - start.tv_usec);
   
   double Gflops = 2e-9*operation_count/seconds;
   printf( "Performance in Gflops %.3f Gflop/s\n", Gflops );

MPI_Finalize();
return 0;

}

