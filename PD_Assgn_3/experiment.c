#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr, n, largest);
    }
}

int main(){

    char c = 'a';
    printf("%s\n", &c);

    return 0;
}