#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
    int JobID;
    int priority;
};

typedef struct Data data;

void swap(data *a, data *b);
void maxHeapify(data arr[], int n, int i);
void buildMaxHeap(data arr[], int n);
void increaseKey(data arr[], int n, int i, int newPriority);
void add(data arr[], int n, int JobID, int priority);
int schedule(data arr[], int n);
int nextJob(data arr[], int n);
int replacePriority(data arr[], int n, int JobID, int priority);
void display(data arr[], int n);

int main(){

    data arr[20] = {};
    int heapSize = 0;
    char c;

    while(1){
        scanf("%c", &c);

        if(c == 'a'){
            int JobID, priority;
            scanf("%d %d", &JobID, &priority);

            if(JobID < 1 || JobID > 10){
                printf("JobID out of bound\n");
                continue;
            }

            if(priority < 1 || priority > 50){
                printf("Priority out of bound\n");
                continue;
            }

            if(heapSize == 20){
                printf("Heap is full\n");
                continue;
            }

            add(arr, heapSize, JobID, priority);
            heapSize++;
        }

        else if(c == 's'){
            printf("%d\n", schedule(arr, heapSize));
            heapSize--;
        }

        else if(c == 'n')
            printf("%d\n", nextJob(arr, heapSize));

        else if(c == 'r'){
            int jobID, priority;
            scanf("%d %d", &jobID, &priority);
            int temp = replacePriority(arr, heapSize, jobID, priority);
            if(temp == -1){
                printf("-1\n");
            }
        }

        else if(c == 'd')
            display(arr, heapSize);

        else if(c == 'e')
            break;
    }
    

    return 0;
}

void swap(data *a, data *b){
    data c = *a;
    *a = *b;
    *b = c;
}

void maxHeapify(data arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l].priority > arr[largest].priority){
        largest = l;
    }
    if(r < n && arr[r].priority > arr[largest].priority){
        largest = r;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(data arr[], int n){
    for(int i = n/2 - 1; i >= 0; i--){
        maxHeapify(arr, n, i);
    }
}

void increaseKey(data arr[], int n, int i, int newPriority){

    arr[i].priority = newPriority;
    while(i > 0 && arr[(i-1)/2].priority < arr[i].priority){
        swap(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void add(data arr[], int n, int JobID, int priority){
    arr[n].JobID = JobID;
    arr[n].priority = -1;
    increaseKey(arr, n, n, priority);
}

int schedule(data arr[], int n){
    
    if(n < 1){
        return -1;
    }
    
    int max = arr[0].JobID;

    swap(&arr[0], &arr[n-1]);
    n--;
    maxHeapify(arr, n, 0);
    return max;
}

int nextJob(data arr[], int n){
    if(n < 1)
        return -1;

    return arr[0].JobID;
}

int replacePriority(data arr[], int n, int JobID, int priority){

    int pos = -1;
    for(int i = 0; i < n; i++){
        if(arr[i].JobID == JobID){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        return -1;
    }

    if(arr[pos].priority < priority){
        increaseKey(arr, n, pos, priority);
    }
    else{
        arr[pos].priority = priority;
        maxHeapify(arr, n, pos);
    }
    
    return 0;
}

void display(data arr[], int n){
    if(n < 1){
        printf("-1\n");
        return;
    }
    for(int i = 0; i < n; i++)
        printf("%d %d\n", arr[i].JobID, arr[i].priority);
    
}

// Parent of i is (i-1)/2