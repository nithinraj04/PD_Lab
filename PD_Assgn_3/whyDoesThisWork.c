#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
    while(s[*ind] >= '0' && s[*ind] <= '9'){
        num = num*10 + (s[*ind] - '0');
        *ind += 1;
    }
    return num;
}

void strToBinaryTree(node *x, char *s, int *ind){

    printf("%d\n", *ind);
    printf("%p\n", *x);

    if(s[*ind] == '('){

        if (s[*ind+1] != ')'){
        
            if(*x == NULL){
                *x = createNode(s[*ind+1] - '0');
                *ind += 2;
                strToBinaryTree(x, s, ind);
            }
            //(1(2(4()())())(3()()))
            else{
                (*x)->left = createNode(s[*ind+1] - '0');
                *ind += 2;
                strToBinaryTree(&(*x)->left, s, ind);
            }
        }

        else{
            *ind += 2;
        }
    }
    

    if(s[*ind] == '('){
        if (s[*ind+1] != ')'){
            printf("Hello\n");
            (*x)->right = createNode(s[*ind+1] - '0');
            *ind += 2;
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

    printf("%d\n", *ind);
}


int main(){

    char *s = (char *)malloc(100);

    node root = NULL;

    scanf("%s", s);

    int ind = 0;

    strToBinaryTree(&root, s, &ind);

    inorder(root);
    printf("\n");

    // printf("%d\n", root->right->data);

    return 0;
}

//(2(7(1()())(6(5()())(8()())))(9()(3()())))


