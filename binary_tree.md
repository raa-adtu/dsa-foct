Yes. For a **DSA lab**, a useful version is to display the binary tree graphically when the number of nodes is **less than 21**. The program below uses level-order insertion and prints the tree with `/` and `\` branches.

For example, after inserting `10, 20, 30, 40, 50, 60, 70`:

```text
                 10
              /      \
            20        30
          /   \      /   \
        40     50   60    70
```

Here is the complete version:

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Binary Tree Node
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

// Count total nodes
int countNodes(struct Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

// Level-order insertion
struct Node* insert(struct Node *root, int value)
{
    struct Node *newNode;
    struct Node *queue[MAX];

    int front = 0;
    int rear = 0;

    newNode = createNode(value);

    if (root == NULL)
        return newNode;

    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

        // Insert into left
        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        }
        else {
            queue[rear++] = temp->left;
        }

        // Insert into right
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

// Level Order Traversal
void levelOrder(struct Node *root)
{
    struct Node *queue[MAX];

    int front = 0;
    int rear = 0;

    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

        printf("%d ", temp->data);

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    printf("\n");
}

// Search
int search(struct Node *root, int value)
{
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;

    return search(root->left, value) ||
           search(root->right, value);
}

// Height
int height(struct Node *root)
{
    int leftHeight;
    int rightHeight;

    if (root == NULL)
        return -1;

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

// Count leaf nodes
int countLeaf(struct Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL &&
        root->right == NULL)
        return 1;

    return countLeaf(root->left) +
           countLeaf(root->right);
}

/*
    Display tree structure.

    This function is intended for trees
    containing fewer than 21 nodes.
*/
void displayTree(struct Node *root)
{
    int n;

    if (root == NULL) {
        printf("\nTree is empty.\n");
        return;
    }

    n = countNodes(root);

    if (n >= 21) {
        printf("\nTree contains %d nodes.\n", n);
        printf("Tree display is available only for");
        printf(" fewer than 21 nodes.\n");
        return;
    }

    printf("\n");
    printf("             BINARY TREE\n");
    printf("------------------------------------------\n\n");

    /*
       For a small tree, use level-order
       arrays to display the structure.
    */

    struct Node *queue[MAX];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    int level = 0;
    int nodesInLevel;
    int i;

    while (front < rear) {

        nodesInLevel = rear - front;

        // Spacing before nodes
        if (level == 0)
            printf("                ");
        else if (level == 1)
            printf("        ");
        else if (level == 2)
            printf("    ");
        else
            printf(" ");

        for (i = 0; i < nodesInLevel; i++) {

            struct Node *temp = queue[front++];

            if (temp != NULL) {

                printf("%-5d", temp->data);

                queue[rear++] = temp->left;
                queue[rear++] = temp->right;
            }
            else {
                printf("     ");
            }
        }

        printf("\n");

        /*
           Print branches except after last level.
        */
        if (front < rear) {

            int remaining = rear - front;

            if (level == 0)
                printf("             /      \\\n");
            else if (level == 1)
                printf("        /   \\    /   \\\n");
            else if (level == 2)
                printf("     / \\ / \\ / \\ / \\\n");

            /*
               Stop displaying if all remaining
               nodes are NULL.
            */
            int hasNode = 0;

            for (i = front; i < rear; i++) {
                if (queue[i] != NULL) {
                    hasNode = 1;
                    break;
                }
            }

            if (!hasNode)
                break;
        }

        level++;

        /*
           Avoid excessive output for
           unexpected tree structures.
        */
        if (level > 4)
            break;
    }

    printf("\n");
}

// Delete node
struct Node* deleteNode(struct Node *root, int value)
{
    struct Node *queue[MAX];
    struct Node *keyNode = NULL;
    struct Node *deepest = NULL;
    struct Node *parent = NULL;

    int front = 0;
    int rear = 0;

    if (root == NULL) {
        printf("Tree is empty.\n");
        return root;
    }

    /*
       Find the node to delete and
       the deepest node.
    */
    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

        if (temp->data == value)
            keyNode = temp;

        deepest = temp;

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    if (keyNode == NULL) {
        printf("Node %d not found.\n", value);
        return root;
    }

    /*
       If only root exists.
    */
    if (root->left == NULL &&
        root->right == NULL) {

        free(root);
        return NULL;
    }

    /*
       Find parent of deepest node.
    */
    front = 0;
    rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        struct Node *temp = queue[front++];

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

    /*
       Replace deleted node's data
       with deepest node's data.
    */
    keyNode->data = deepest->data;

    /*
       Remove deepest node.
    */
    if (parent->left == deepest)
        parent->left = NULL;
    else
        parent->right = NULL;

    free(deepest);

    printf("Node %d deleted successfully.\n", value);

    return root;
}

// Main
int main()
{
    struct Node *root = NULL;

    int choice;
    int value;

    while (1) {

        printf("\n=====================================\n");
        printf("       BINARY TREE OPERATIONS\n");
        printf("=====================================\n");

        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Display Tree Structure\n");
        printf("5. Preorder Traversal\n");
        printf("6. Inorder Traversal\n");
        printf("7. Postorder Traversal\n");
        printf("8. Level-order Traversal\n");
        printf("9. Count Nodes\n");
        printf("10. Count Leaf Nodes\n");
        printf("11. Find Height\n");
        printf("12. Exit\n");

        printf("=====================================\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                if (countNodes(root) >= 20) {
                    printf("Maximum 20 nodes allowed.\n");
                    break;
                }

                printf("Enter value: ");
                scanf("%d", &value);

                root = insert(root, value);

                printf("Node inserted successfully.\n");

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
                    printf("%d found in tree.\n", value);
                else
                    printf("%d not found.\n", value);

                break;

            case 4:

                displayTree(root);

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

                printf("Level Order: ");
                levelOrder(root);

                break;

            case 9:

                printf("Total nodes = %d\n",
                       countNodes(root));

                break;

            case 10:

                printf("Leaf nodes = %d\n",
                       countLeaf(root));

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
```

### Recommended input for testing

Insert these values in this order:

```text
10 20 30 40 50 60 70
```

The logical tree is:

```text
                  10
                /    \
              20      30
             /  \    /  \
            40   50 60   70
```

Then select **4. Display Tree Structure**.

**Important:** This version allows a maximum of **20 nodes** specifically so that the graphical display remains manageable. For a classroom/lab program, this is convenient because students can visually relate the **tree structure** to the `left` and `right` pointers.
