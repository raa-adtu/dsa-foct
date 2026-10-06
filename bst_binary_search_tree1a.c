#include <stdio.h>
#include <stdlib.h>

// Structure of a BST node
// ============================================
// Structure of a BST Node
// ============================================

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};


// ============================================
// Create a New Node
// ============================================

struct Node* createNode(int data) {

    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


// ============================================
// Insert a Node into BST
// ============================================

struct Node* insert(struct Node *root, int data) {

    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {

        root->left = insert(root->left, data);
    }

    else if (data > root->data) {

        root->right = insert(root->right, data);
    }

    else {

        printf("Duplicate value %d is not allowed.\n", data);
    }

    return root;
}


// ============================================
// Search an Element
// ============================================

struct Node* search(struct Node *root, int key) {

    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {

        return search(root->left, key);
    }

    return search(root->right, key);
}


// ============================================
// Find Minimum Element
// ============================================

struct Node* findMin(struct Node *root) {

    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {

        root = root->left;
    }

    return root;
}


// ============================================
// Find Maximum Element
// ============================================

struct Node* findMax(struct Node *root) {

    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {

        root = root->right;
    }

    return root;
}


// ============================================
// Delete a Node
// ============================================

struct Node* deleteNode(struct Node *root, int key) {

    struct Node *temp;

    if (root == NULL) {

        printf("Value %d not found.\n", key);
        return root;
    }

    // Search in left subtree
    if (key < root->data) {

        root->left = deleteNode(root->left, key);
    }

    // Search in right subtree
    else if (key > root->data) {

        root->right = deleteNode(root->right, key);
    }

    // Node found
    else {

        // Case 1: No child
        if (root->left == NULL &&
            root->right == NULL) {

            free(root);
            return NULL;
        }

        // Case 2: Only right child
        else if (root->left == NULL) {

            temp = root->right;

            free(root);

            return temp;
        }

        // Case 3: Only left child
        else if (root->right == NULL) {

            temp = root->left;

            free(root);

            return temp;
        }

        // Case 4: Two children
        else {

            temp = findMin(root->right);

            root->data = temp->data;

            root->right =
                deleteNode(root->right, temp->data);
        }
    }

    return root;
}


// ============================================
// In-order Traversal
// ============================================

void inorder(struct Node *root) {

    if (root != NULL) {

        inorder(root->left);

        printf("%d ", root->data);

        inorder(root->right);
    }
}


// ============================================
// Pre-order Traversal
// ============================================

void preorder(struct Node *root) {

    if (root != NULL) {

        printf("%d ", root->data);

        preorder(root->left);

        preorder(root->right);
    }
}


// ============================================
// Post-order Traversal
// ============================================

void postorder(struct Node *root) {

    if (root != NULL) {

        postorder(root->left);

        postorder(root->right);

        printf("%d ", root->data);
    }
}


// ============================================
// Count Total Number of Nodes
// ============================================

int countNodes(struct Node *root) {

    if (root == NULL) {
        return 0;
    }

    return 1 +
           countNodes(root->left) +
           countNodes(root->right);
}


// ============================================
// Count Leaf Nodes
// ============================================

int countLeafNodes(struct Node *root) {

    if (root == NULL) {
        return 0;
    }

    // Node with no children
    if (root->left == NULL &&
        root->right == NULL) {

        return 1;
    }

    return countLeafNodes(root->left) +
           countLeafNodes(root->right);
}


// ============================================
// Find Height of BST
// ============================================

int height(struct Node *root) {

    int leftHeight;
    int rightHeight;

    if (root == NULL) {
        return 0;
    }

    leftHeight = height(root->left);

    rightHeight = height(root->right);

    if (leftHeight > rightHeight) {

        return leftHeight + 1;
    }

    else {

        return rightHeight + 1;
    }
}


// ============================================
// Display BST in Tree-like Structure
// ============================================

void displayTree(struct Node *root, int space) {

    int i;

    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space = space + 5;

    // Display right subtree first
    displayTree(root->right, space);

    printf("\n");

    // Print spaces
    for (i = 5; i < space; i++) {

        printf(" ");
    }

    printf("%d", root->data);

    // Display left subtree
    displayTree(root->left, space);
}


// ============================================
// Tree Information Function
// ============================================

void tree_info(struct Node *root) {

    struct Node *minNode;
    struct Node *maxNode;

    if (root == NULL) {

        printf("\nBST is empty.\n");

        return;
    }

    // Find minimum and maximum
    minNode = findMin(root);

    maxNode = findMax(root);


    printf("\n========================================\n");
    printf("           BST INFORMATION\n");
    printf("========================================\n");


    // Minimum element
    printf("Minimum element       : %d\n",
           minNode->data);


    // Maximum element
    printf("Maximum element       : %d\n",
           maxNode->data);


    // Total number of nodes
    printf("Total number of nodes : %d\n",
           countNodes(root));


    // Total leaf nodes
    printf("Total leaf nodes      : %d\n",
           countLeafNodes(root));


    // Height
    printf("Height of BST         : %d\n",
           height(root));


    // Tree structure
    printf("\nBST in Tree Structure:\n");

    printf("----------------------------------------\n");

    displayTree(root, 0);

    printf("\n========================================\n");
}

// Main function
int main()
{

    struct Node *root = NULL;
    struct Node *result;

    int choice;
    int value;

    do
    {

        printf("\n========================================\n");
        printf("       BINARY SEARCH TREE (BST)\n");
        printf("========================================\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. In-order Traversal\n");
        printf("5. Pre-order Traversal\n");
        printf("6. Post-order Traversal\n");
        printf("7. Display All Traversals\n");
        printf("8. Tree Information\n");
        printf("9. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);

            root = insert(root, value);

            printf("Insertion completed.\n");
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);

            root = deleteNode(root, value);
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);

            result = search(root, value);

            if (result != NULL)
            {
                printf("%d found in the BST.\n", value);
            }
            else
            {
                printf("%d not found in the BST.\n", value);
            }

            break;

        case 4:
            if (root == NULL)
            {
                printf("BST is empty.\n");
            }
            else
            {
                printf("In-order Traversal: ");
                inorder(root);
                printf("\n");
            }
            break;

        case 5:
            if (root == NULL)
            {
                printf("BST is empty.\n");
            }
            else
            {
                printf("Pre-order Traversal: ");
                preorder(root);
                printf("\n");
            }
            break;

        case 6:
            if (root == NULL)
            {
                printf("BST is empty.\n");
            }
            else
            {
                printf("Post-order Traversal: ");
                postorder(root);
                printf("\n");
            }
            break;

        // Display all three traversals
        case 7:
            if (root == NULL)
            {
                printf("BST is empty.\n");
            }
            else
            {
                printf("\nIn-order Traversal   : ");
                inorder(root);

                printf("\nPre-order Traversal  : ");
                preorder(root);

                printf("\nPost-order Traversal : ");
                postorder(root);

                printf("\n");
            }
            break;

        // Display tree information
        case 8:
            tree_info(root);
            break;

        case 9:
            printf("\nProgram terminated.\n");
            break;

        default:
            printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}