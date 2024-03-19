#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int id;
    int p;
}job;

void swap(job *a, job *b) {
    job temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(job A[], int n, int start) {
    int largest = start;
    int l = 2 * largest;
    int r = 2 * largest + 1;

    while (l < n && A[l].p > A[largest].p) {
        largest = l;
    }
    while (r < n && A[r].p > A[largest].p) {
        largest = r;
    }
    if (largest != start) {
        job temp = A[start];
        A[start] = A[largest];
        A[largest] = temp;
        heapify(A, n, largest);
    }
}



void increase_key(job A[], int pos, int p) {

    if (pos < 1 || pos >19) {
        printf("Error: Invalid position\n");
        return;
    }
    A[pos].p=p;

    while(pos>0 && A[pos/2].p<A[pos].p)   //we corrected here initially it was pos-1>1 , we changed it to pos-1>0.
    {
        swap(&A[pos],&A[pos/2]);  //we also have adjuted code so that indexing problem doesnt happen.
        pos=pos/2;
    }
}

void replace_priority(job A[], int ID, int np, int heap_size) {
    int i;
    for (i = 0; i < heap_size; i++) {
        if (A[i].id == ID) {

            if(A[i].p>np){
                A[i].p = np;
                heapify(A,heap_size,i);
                return;
            }
            else{
                increase_key(A,i,np);
                return;
            }
            
            }

    }

    printf("-1\n");
}



void add(job A[], int ID, int p, int *heap_size) {
    if (*heap_size >= 20) {
        printf("Error: Overflow\n");
        return;
        }


    A[*heap_size].id = ID;
    A[*heap_size].p = p;

    
    (*heap_size)++; 
    increase_key(A,*heap_size-1,p);

  //we have to check new node with its parent and above parents.
}

void schedule(job A[],int *heap_size )
{

    if (*heap_size <= 0) {
        printf("-1\n");
        return;
    }

    printf("%d\n",A[0].id);
    A[0]=A[*heap_size-1];
    *heap_size=*heap_size-1;
    heapify(A,*heap_size,0);

}

void display(job A[], int heap_size) {
    if (heap_size <= 0) {
        printf("-1\n");
        return;
    }

    for (int i = 0; i < heap_size; i++) {
        printf("ID: %d, Priority: %d\n", A[i].id, A[i].p);
    }
}
void next_job(job A[],int *heap_size )
{

    if (*heap_size <= 0) {
        printf("-1\n");
        return;
    }
    printf("%d\n",A[0].id);
}


int main() {
    job jobs[20];
    int heap_size = 0;

       char option;
    int ID, p, np;

    while (1) {
        scanf(" %c", &option);

        switch (option) {
            case 'a':
                scanf("%d %d", &ID, &p);
                add(jobs, ID, p, &heap_size);
                break;
            case 's':
                schedule(jobs, &heap_size);
                break;
            case 'n':
                next_job(jobs,&heap_size);
                break;
            case 'r':
                scanf("%d %d", &ID, &np);
                replace_priority(jobs, ID, np, heap_size);
                break;
            case 'd':
                display(jobs, heap_size);
                break;
            case 'e':
                exit(0);
            default:
                printf("Invalid option\n");
                break;
        }
    }



    return 0;
}
