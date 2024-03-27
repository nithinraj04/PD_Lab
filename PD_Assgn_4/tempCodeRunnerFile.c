node searchKey(node root, int key){
    if(root == NULL || root->data == key)
        return root;
        
    if(key < root->data)
        searchKey(root->left, key);

    else
        searchKey(root->right, key);
}