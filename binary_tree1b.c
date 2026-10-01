#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure of Binary Tree Node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert node using level-order insertion
struct Node* insert(struct Node *root, int value)
{
    struct Node *newNode = createNode(value);

    if (root == NULL)
        return newNode;

    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

        // Check left child
        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        }
        else {
            queue[rear++] = temp->left;
        }

        // Check right child
        if (temp->right == NULL) {
            temp->right = newNode;
            return root;
        }
        else {
            queue[rear++] = temp->right;
        }
    }

    return root;
}

// Preorder Traversal
void preorder(struct Node *root)
{
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Inorder Traversal
void inorder(struct Node *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Postorder Traversal
void postorder(struct Node *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Level-order Traversal
void levelOrder(struct Node *root)
{
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

        printf("%d ", temp->data);

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }
}

// Search a node
int search(struct Node *root, int value)
{
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;

    return search(root->left, value) ||
           search(root->right, value);
}

// Count total nodes
int countNodes(struct Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(struct Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeafNodes(root->left)
         + countLeafNodes(root->right);
}

// Find height
int height(struct Node *root)
{
    if (root == NULL)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ?
                leftHeight : rightHeight);
}

// Display tree nodes with addresses
void display(struct Node *root)
{
    if (root == NULL) {
        printf("\nTree is empty.\n");
        return;
    }

    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    printf("\n");
    printf("==========================================================================\n");
    printf("                     BINARY TREE NODE DETAILS\n");
    printf("==========================================================================\n");

    printf("%-3s %-18s %-8s %-18s %-18s\n",
           "R", "Node Address", "Data",
           "Left Address", "Right Address");

    printf("--------------------------------------------------------------------------\n");

    while (front < rear) {

        struct Node *temp = queue[front++];

        // Mark root with *
        if (temp == root)
            printf("*   ");
        else
            printf("    ");

        // Node address
        printf("%-18p ", (void*)temp);

        // Data
        printf("%-8d ", temp->data);

        // Left child address
        if (temp->left != NULL)
            printf("%-18p ", (void*)temp->left);
        else
            printf("%-18s ", "NULL");

        // Right child address
        if (temp->right != NULL)
            printf("%-18p", (void*)temp->right);
        else
            printf("%-18s", "NULL");

        printf("\n");

        // Add children to queue
        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    printf("==========================================================================\n");
    printf("* = ROOT NODE\n");
}

// Delete node
struct Node* deleteNode(struct Node *root, int key)
{
    if (root == NULL) {
        printf("Tree is empty.\n");
        return NULL;
    }

    // If root is the only node
    if (root->left == NULL && root->right == NULL) {

        if (root->data == key) {
            free(root);
            return NULL;
        }

        printf("Node not found.\n");
        return root;
    }

    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    struct Node *keyNode = NULL;
    struct Node *temp = NULL;

    queue[rear++] = root;

    // Find the node and deepest node
    while (front < rear) {

        temp = queue[front++];

        if (temp->data == key)
            keyNode = temp;

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    if (keyNode == NULL) {
        printf("Node %d not found.\n", key);
        return root;
    }

    // temp is the deepest node
    struct Node *deepest = temp;

    // Find parent of deepest node
    struct Node *parent = NULL;

    front = 0;
    rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        temp = queue[front++];

        if (temp->left == deepest ||
            temp->right == deepest) {
            parent = temp;
            break;
        }

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    // Copy deepest node's data
    keyNode->data = deepest->data;

    // Remove deepest node
    if (parent->left == deepest)
        parent->left = NULL;
    else
        parent->right = NULL;

    free(deepest);

    printf("Node %d deleted successfully.\n", key);

    return root;
}

// Main function
int main()
{
    struct Node *root = NULL;

    int choice;
    int value;

    while (1) {

        printf("\n============================================\n");
        printf("          BINARY TREE OPERATIONS\n");
        printf("============================================\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Display Tree with Addresses\n");
        printf("5. Preorder Traversal\n");
        printf("6. Inorder Traversal\n");
        printf("7. Postorder Traversal\n");
        printf("8. Level-order Traversal\n");
        printf("9. Count Total Nodes\n");
        printf("10. Count Leaf Nodes\n");
        printf("11. Find Height\n");
        printf("12. Exit\n");
        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value: ");
                scanf("%d", &value);

                root = insert(root, value);

                printf("Node %d inserted successfully.\n", value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                root = deleteNode(root, value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);

                if (search(root, value))
                    printf("%d found in the tree.\n", value);
                else
                    printf("%d not found in the tree.\n", value);

                break;

            case 4:
                display(root);
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 7:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 8:
                printf("Level-order: ");
                levelOrder(root);
                printf("\n");
                break;

            case 9:
                printf("Total nodes = %d\n",
                       countNodes(root));
                break;

            case 10:
                printf("Leaf nodes = %d\n",
                       countLeafNodes(root));
                break;

            case 11:
                printf("Height = %d\n",
                       height(root));
                break;

            case 12:
                printf("Program terminated.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


/*
+---+----------------+------+----------------+----------------+
|   | Node Address   | Data | Left Address   | Right Address  |
+---+----------------+------+----------------+----------------+
| * | 0x...          |  10  | 0x...          | 0x...          |
|   | 0x...          |  20  | 0x...          | 0x...          |
|   | 0x...          |  30  | NULL           | NULL           |
|   | 0x...          |  40  | NULL           | NULL           |
|   | 0x...          |  50  | NULL           | NULL           |
+---+----------------+------+----------------+----------------+
*/