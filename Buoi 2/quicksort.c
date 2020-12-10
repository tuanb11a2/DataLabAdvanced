#include<stdio.h>
#include<time.h>
#include <stdlib.h> 
#define MAX_ARRAY_LENGTH 10

void swap(int* i,int* j){
    int tmp;
    tmp = *i;
    *i = *j;
    *j = tmp;
}

//Quicksort 2way(first way)
//Really slow!
void quicksort_2way_1st(int array[],int length,int left,int right){
    int i,j,pivot,l;
    i = left;
    j = right;
    if(left<right){
        while(i !=j){
            while(array[i] < array[j]){
                i++;
            };

            swap(&array[i],&array[j]);
            while(array[i] < array[j]){
                j--;
            }
            swap(&array[i],&array[j]);
        }
        pivot = i;
        quicksort_2way_1st(array,length,left,pivot-1);
        quicksort_2way_1st(array,length,pivot+1,right);
    }
}


//Quicksort 2way(second way)
void quicksort_2way_2nd(int array[],int length,int left,int right){
    int i,j,pivot,l;
    i = left;
    j = right;
    if(left<right){
        while(i !=j){
            while(array[i] < array[j]){
                i++;
            };

            swap(&array[i],&array[j]);
            while(array[i] < array[j]){
                j--;
            }
            swap(&array[i],&array[j]);
        }
        pivot = i;
        quicksort_2way_2nd(array,length,left,pivot-1);
        quicksort_2way_2nd(array,length,pivot+1,right);
    }
}

void print_array(int array[],int length){
    int i;
    printf("The array: ");
    for(i = 0;i < length;i++){
        printf("%d-",array[i]);
    }
    printf("\n");
}

void main(){
    clock_t start,end;
    int i;
    // int* A = malloc(sizeof(int) * MAX_ARRAY_LENGTH);
    // for(i = 0;i < MAX_ARRAY_LENGTH;i++){
    //     A[i] = rand()%10;
    // }
    int A[MAX_ARRAY_LENGTH]={10,9,8,8,5,6,7,3,2,1};
    print_array(A,MAX_ARRAY_LENGTH);
    //start = clock();
    quicksort_2way_1st(A,MAX_ARRAY_LENGTH,0,MAX_ARRAY_LENGTH-1);
    //end = clock();
    print_array(A,MAX_ARRAY_LENGTH);

    printf("\nThe time is: %.2f",(double)((end-start)/CLOCKS_PER_SEC));
}