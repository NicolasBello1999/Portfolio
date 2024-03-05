typedef struct node node;

struct node {
    int data;
    node *left;
    node *right;
};

// prototypes / main tree operations
node *insertRecBST(node *root, int data);
node *insertIterBST(node *root, int data);
node *deleteFromBST(node *root, int data);

node *insertRecBST(node *root, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if (!root) return temp;

    if (root->data > data)
        root->left = insertRecBST(root->left, data);
    else
        root->right = insertRecBST(root->right, data);
    
    return root;
}

node *insertIterBST(node *root, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if (!root) return temp;

    while (root->data > data) {
        
    }
}

node *deleteFromBST(node *root, int data) {
    
}