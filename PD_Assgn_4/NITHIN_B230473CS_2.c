#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct BST{
    int data;
    struct BST *left;
    struct BST *right;
};

typedef struct BST *node;

node createNode(int key){
    node temp = (node)malloc(sizeof(struct BST));
    temp->data = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insertNode(node *root, int key){
    node temp = createNode(key);

    node y = NULL;
    node x = *root;

    while(x != NULL){
        y = x;
        if(key < x->data)
            x = x->left;
        else
            x = x->right;
    }

    if(y == NULL)
        *root = temp;
    
    else if(key < y->data)
        y->left = temp;

    else
        y->right = temp;
}

node searchKey(node root, int key){
    if(root == NULL || root->data == key)
        return root;
        
    if(key < root->data)
        searchKey(root->left, key);

    else
        searchKey(root->right, key);
}

void translate(node *root, node u, node v){
    if(u == *root)
        *root = v;

    node x = *root;
    node y = NULL;
    while(x != u){
        y = x;
        if(u->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    if(y->left == u) //u < u.parent
        y->left = v;

    else
        y->right = v;
}

node minimum(node root){
    while(root->left != NULL)
        root = root->left;
    return root;
}

void deleteKey(node *root, int num){

    node key = searchKey(*root, num);

    if(key == NULL){
        printf("NOT FOUND\n");
        return;
    }

    if(key->left == NULL)
        translate(root, key, key->right);
    
    else if(key->right == NULL)
        translate(root, key, key->left);

    else{
        node min = minimum(key->right);

        if(min != key->right){  //Separate min from tree and connecting the right
            translate(root, min, min->right);
            min->right = key->right;
        }

        translate(root, key, min);  //Separate key from the tree and connect left of min
        min->left = key->left;
    }

    free(key);
}

void inorder(node root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(node root){
    if(root != NULL){
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node root){
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main(){

    char c;
    node root = NULL;

    while(1){
        scanf(" %c", &c);

        if(c == 'i'){
            int num;
            scanf("%d ", &num);
            insertNode(&root, num);
        }

        else if(c == 's'){
            int num;
            scanf("%d", &num);
            node temp = searchKey(root, num);
            if(temp != NULL)
                printf("PRESENT\n");
            else
                printf("NOT PRESENT\n");
        }

        else if(c == 'd'){
            int num;
            scanf("%d", &num);
            deleteKey(&root, num);
        }


        else if(c == 'p'){
            if(root == NULL)
                printf("NULL");
            else
                inorder(root);
            printf("\n");
        }

        else if(c == 't'){
            if(root == NULL)
                printf("NULL");
            else
                preorder(root);
            printf("\n");
        }

        else if(c == 'b'){
            if(root == NULL)
                printf("NULL");
            else
                postorder(root);
            printf("\n");
        }

        else if(c == 'e')
            break;
    }

    return 0;
}