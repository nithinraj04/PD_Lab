#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

typedef struct Node *node;

node createNode(int data){
    node temp = (node)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}

node insert(node *root, int data){
    
    node temp = createNode(data);

    node y = NULL;
    node x = *root;

    while(x != NULL){
        y = x;
        if(data < x->data){
            x = x->left;
        }else{
            x = x->right;
        }
    }

    if(y == NULL)
        *root = temp;

    else if(data < y->data){
        y->left = temp;
        temp->parent = y;
    }

    else{
        y->right = temp;
        temp->parent = y;
    }
}

void inorder(node root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int strToInt(char *s, int *ind){
    int num = 0;
    // printf("%s\n", s);
    while(s[*ind] >= '0' && s[*ind] <= '9'){
        num = num*10 + (s[*ind] - '0');
        *ind += 1;
    }
    return num;
}

void strToBinaryTree(node *x, char *s, int *ind){

    if(s[*ind] == '('){

        if (s[*ind+1] != ')'){
        
            if(*x == NULL){
                *ind += 1;
                int num = strToInt(s, ind);
                *x = createNode(num);
                // *ind += 1;
                strToBinaryTree(x, s, ind);
            }
            //(1(2(4()())())(3()()))
            else{
                *ind += 1;
                int num = strToInt(s, ind);
                (*x)->left = createNode(num);
                // *ind += 1;
                strToBinaryTree(&(*x)->left, s, ind);
            }
        }

        else{
            *ind += 2;
        }
    }
    

    if(s[*ind] == '('){
        if (s[*ind+1] != ')'){
            *ind += 1;
            int num = strToInt(s, ind);
            (*x)->right = createNode(num);
            // *ind += 1;
            strToBinaryTree(&(*x)->right, s, ind);
        }
        else{
            *ind += 2;
        }
    }

    if(s[*ind] == ')'){
        *ind += 1;
    }

    if(s[*ind] == '\0'){
        return;
    }
}

void printLevelK(node root, int k){
    if(root == NULL)
        return;
    if(k == 0){
        printf("%d ", root->data);
        return;
    }
    printLevelK(root->left, k-1);
    printLevelK(root->right, k-1);
}

node searchKey(node root, int key){
    
    if(root == NULL || root->data == key)
        return root;
    
    node l = searchKey(root->left, key);
    node r = searchKey(root->right, key);

    if(l != NULL)
        return l;
    if(r != NULL)
        return r;
}

char* dynamicString(){ //proprietory
    char c = ' ';
    char *s = (char *)malloc(1);
    int size = 1;

    while(c != '\n'){

        scanf("%c", &c);

        if(c != ' '){
            s[size-1] = c;
            size++;
            s = (char*)realloc(s, size);
        }
    }
    s[size-1] = '\0';

    return s;
}

int main(){

    node root = NULL;

    char *s = dynamicString();

    int index = 0;
    strToBinaryTree(&root, s, &index);

    int n, k;
    scanf("%d %d", &n, &k);

    node key = searchKey(root, n);

    if(key == NULL){
        printf("NOT FOUND\n");
    }
    else{
        printLevelK(key, k);
    }

    printf("\n");

    return 0;
}


