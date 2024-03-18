#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int *arr, int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int *arr, int n){
    for(int i = n/2 - 1; i >= 0; i--){
        maxHeapify(arr, n, i);
    }
}

void heapSort(int *arr, int n){
    buildMaxHeap(arr, n);
    for(int i = n-1; i > 0; i--){
        swap(&arr[0], &arr[i]);
        n--;
        maxHeapify(arr, n, 0);
    }
}

int main(){

    char c = 'a';
    printf("%s\n", &c);

    return 0;
}