#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct splitNumString{
    char *num;
    char *string;
};

struct carInfo{
    char *name;
    int mileage;
};

typedef struct carInfo data;

char* dynamicString();
int isDigit(char c);
struct splitNumString splitString(char *s);
int stringToInt(char *s);

void swap(data *a, data *b){
    data c = *a;
    *a = *b;
    *b = c;
}

void minHeapify(data arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l].mileage < arr[largest].mileage){
        largest = l;
    }
    if(r < n && arr[r].mileage < arr[largest].mileage){
        largest = r;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        minHeapify(arr, n, largest);
    }
}

void buildMinHeap(data arr[], int n){
    for(int i = n/2 - 1; i >= 0; i--){
        minHeapify(arr, n, i);
    }
}

void heapSort(data arr[], int n){
    buildMinHeap(arr, n);
    for(int i = n-1; i > 0; i--){
        swap(&arr[0], &arr[i]);
        n--;
        minHeapify(arr, n, 0);
    }
}

int main(){

    int n;
    scanf("%d ", &n);

    if(n < 1 || 1000){
        printf("Number of elements out of bound\n");
        return 0;
    }

    char * s[n];
    for(int i = 0; i < n; i++){
        s[i] = dynamicString();
    }

    struct carInfo car[n];
    for(int i = 0; i < n; i++){
        struct splitNumString split = splitString(s[i]);
        car[i].name = split.string;
        car[i].mileage = stringToInt(split.num);
    }

    heapSort(car, n);

    printf("\n");
    for(int i = 0; i < n; i++){
        printf("%s %d\n", car[i].name, car[i].mileage);
    }

    return 0;
}

struct splitNumString splitString(char *s){

    int size = strlen(s) - 1;
    char *num = (char *)malloc(3);
    char *string = (char *)malloc(size-1);
    num = "";

    while(isDigit(s[size])){
        size--;
    }

    num = &s[size+1];
    num += '\0';
    size--;

    while(size >= 0){
        string[size] = s[size];
        size--;
    }
    string[size] = '\0';

    struct splitNumString split;
    split.num = num;
    split.string = string;

    return split;
}

int stringToInt(char *s){
    int num = 0;
    int size = strlen(s);
    for(int i = 0; i < size; i++){
        num = num*10 + (int)(s[i] - '0');
    }
    return num;
}

char* dynamicString(){
    char c;
    char *s = (char *)malloc(1);
    int size = 1;

    scanf("%c", &c);

    while(c != '\n'){
        s[size-1] = c;
        size++;
        s = (char*)realloc(s, size);
        scanf("%c", &c);
    }
    s[size-1] = '\0';

    return s;
}

int isDigit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}

// abcdefghijklmnopqrstuvwxyz0000