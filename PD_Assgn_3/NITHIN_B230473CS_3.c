#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char data;
    struct Node *next;
};

typedef struct Node * node;

node createNode(int data);
void insert(node *head, int data);
int pop(node *head);
char* dynamicString();
int length(node head);

int main(){

    int n;
    scanf("%d ", &n);
    char *arr[n];


    for(int i = 0; i < n; i++){
        arr[i] = dynamicString();
    }

    int count = 0;

    for(int i = 0; i < n; i++){
        int flag = 0, j = 0;
        node head = NULL;
        while(arr[i][j] != '\0'){
            if(arr[i][j] == '('){
                insert(&head, '(');
            }
            else if(arr[i][j] == ')'){
                flag = pop(&head);
                if(flag == -1)
                    break;
            }
            j++;
        }
        if(flag == -1)
            continue;
        if(length(head) != 0)
            continue;
        count++;
    }   

    printf("%d\n", count);

    return 0;
}

node createNode(int data){
    node temp = (node)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insert(node *head, int data){
    node temp = createNode(data);
    if(*head == NULL){
        *head = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
}

int pop(node *head){
    if(*head == NULL){
        return -1;
    }
    node temp = *head;
    *head = (*head)->next;
    free(temp);
    return 0;
}

char* dynamicString(){  //proprietory

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

int length(node head){
    node x = head;
    int count = 0;
    while(x != NULL){
        count++;
        x = x->next;
    }
    return count;
}
