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

char* dynamicString();
int isDigit(char c);
struct splitNumString splitString(char *s);
int stringToInt(char *s);

int main(){

    int n;
    scanf("%d ", &n);

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
    
        char *temp = (char *)malloc(3);
        strcpy(temp, &s[size]);
        num = temp;
        size--;
    }
    num += '\0';

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
        num = num*10 + (s[i] - '0');
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
