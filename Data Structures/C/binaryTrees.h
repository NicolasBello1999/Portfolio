typedef struct node node;

struct node {
    int data;
    node *left;
    node *right;
};

// prototypes / main tree operations
node *insertIntoBST(node *root, int data);
node *deleteFromBST(node *root, int data);

node *createChildLeaf(node *root, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if (!root) return temp;

    if (root->data > data)
        root->left = createChildLeaf(root->left, data);
    else
        root->right = createChildLeaf(root->right, data);
    
    return root;
}

node *deleteFromBST(node *root, int data) {
    
}