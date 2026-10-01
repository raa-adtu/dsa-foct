#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *prev;
    int data;
    struct Node *next;
};

struct Node *head = NULL;


/*--------------------------------------------------
  Function to create a new node
--------------------------------------------------*/
struct Node* createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->prev = NULL;
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}


/*--------------------------------------------------
  Insert at Beginning
--------------------------------------------------*/
void insertBeginning(int value)
{
    struct Node *newNode;

    newNode = createNode(value);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    printf("\n%d inserted at beginning.\n", value);
}


/*--------------------------------------------------
  Insert at End
--------------------------------------------------*/
void insertEnd(int value)
{
    struct Node *newNode;
    struct Node *temp;

    newNode = createNode(value);

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    printf("\n%d inserted at end.\n", value);
}


/*--------------------------------------------------
  Insert After a Given Value
--------------------------------------------------*/
void insertAfter(int searchValue, int value)
{
    struct Node *temp;
    struct Node *newNode;

    temp = head;

    while (temp != NULL && temp->data != searchValue)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("\n%d not found in the list.\n", searchValue);
        return;
    }

    newNode = createNode(value);

    newNode->prev = temp;
    newNode->next = temp->next;

    if (temp->next != NULL)
    {
        temp->next->prev = newNode;
    }

    temp->next = newNode;

    printf("\n%d inserted after %d.\n", value, searchValue);
}


/*--------------------------------------------------
  Insert Before a Given Value
--------------------------------------------------*/
void insertBefore(int searchValue, int value)
{
    struct Node *temp;
    struct Node *newNode;

    temp = head;

    while (temp != NULL && temp->data != searchValue)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("\n%d not found in the list.\n", searchValue);
        return;
    }

    newNode = createNode(value);

    newNode->next = temp;
    newNode->prev = temp->prev;

    if (temp->prev != NULL)
    {
        temp->prev->next = newNode;
    }
    else
    {
        head = newNode;
    }

    temp->prev = newNode;

    printf("\n%d inserted before %d.\n", value, searchValue);
}


/*--------------------------------------------------
  Delete from Beginning
--------------------------------------------------*/
void deleteBeginning()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;
    head = head->next;

    if (head != NULL)
    {
        head->prev = NULL;
    }

    printf("\n%d deleted from beginning.\n", temp->data);

    free(temp);
}


/*--------------------------------------------------
  Delete from End
--------------------------------------------------*/
void deleteEnd()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    if (temp->prev == NULL)
    {
        head = NULL;
    }
    else
    {
        temp->prev->next = NULL;
    }

    printf("\n%d deleted from end.\n", temp->data);

    free(temp);
}


/*--------------------------------------------------
  Delete a Given Value
--------------------------------------------------*/
void deleteValue(int value)
{
    struct Node *temp;

    temp = head;

    while (temp != NULL && temp->data != value)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("\n%d not found in the list.\n", value);
        return;
    }

    /* If deleting the first node */
    if (temp->prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        temp->prev->next = temp->next;
    }

    /* If deleting a node other than last */
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    printf("\n%d deleted from the list.\n", value);

    free(temp);
}


/*--------------------------------------------------
  Search an Element
--------------------------------------------------*/
void search(int value)
{
    struct Node *temp;
    int position = 1;

    temp = head;

    while (temp != NULL)
    {
        if (temp->data == value)
        {
            printf("\n%d found at position %d.\n",
                   value, position);
            return;
        }

        temp = temp->next;
        position++;
    }

    printf("\n%d not found in the list.\n", value);
}


/*--------------------------------------------------
  Display Forward
--------------------------------------------------*/
void displayForward()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;

    printf("\nForward List:\n");

    while (temp != NULL)
    {
        printf("%d", temp->data);

        if (temp->next != NULL)
        {
            printf(" <-> ");
        }

        temp = temp->next;
    }

    printf(" -> NULL\n");
}


/*--------------------------------------------------
  Display Backward
--------------------------------------------------*/
void displayBackward()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;

    /* Move to the last node */
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    printf("\nBackward List:\n");

    while (temp != NULL)
    {
        printf("%d", temp->data);

        if (temp->prev != NULL)
        {
            printf(" <-> ");
        }

        temp = temp->prev;
    }

    printf(" -> NULL\n");
}


/*--------------------------------------------------
  Display Node Table
--------------------------------------------------*/
void displayTable()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;

    printf("\n");
    printf("Doubly Linked List Node Table\n");

    printf("---------------------------------------------------------------\n");
    printf("| %20s | %10s | %20s |\n",
           "PREV ADDRESS",
           "DATA",
           "NEXT ADDRESS");
    printf("---------------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("| %20p | %10d | %20p |\n",
               (void*)temp->prev,
               temp->data,
               (void*)temp->next);

        temp = temp->next;
    }

    printf("---------------------------------------------------------------\n");
}


/*--------------------------------------------------
  Count Nodes
--------------------------------------------------*/
void countNodes()
{
    struct Node *temp;
    int count = 0;

    temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    printf("\nNumber of nodes = %d\n", count);
}


/*--------------------------------------------------
  Delete Complete List
--------------------------------------------------*/
void deleteList()
{
    struct Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    printf("\nComplete list deleted.\n");
}


/*--------------------------------------------------
  Main Function
--------------------------------------------------*/
int main()
{
    int choice;
    int value;
    int searchValue;

    do
    {
        printf("\n\n");
        printf("====================================================\n");
        printf("          DOUBLY LINKED LIST MENU\n");
        printf("====================================================\n");

        printf("1.  Insert at Beginning\n");
        printf("2.  Insert at End\n");
        printf("3.  Insert After a Given Value\n");
        printf("4.  Insert Before a Given Value\n");
        printf("5.  Delete from Beginning\n");
        printf("6.  Delete from End\n");
        printf("7.  Delete a Given Value\n");
        printf("8.  Search an Element\n");
        printf("9.  Display Forward\n");
        printf("10. Display Backward\n");
        printf("11. Display Node Table\n");
        printf("12. Count Nodes\n");
        printf("13. Delete Complete List\n");
        printf("14. Exit\n");

        printf("====================================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                printf("Enter value: ");
                scanf("%d", &value);

                insertBeginning(value);
                break;


            case 2:

                printf("Enter value: ");
                scanf("%d", &value);

                insertEnd(value);
                break;


            case 3:

                printf("Enter value after which to insert: ");
                scanf("%d", &searchValue);

                printf("Enter new value: ");
                scanf("%d", &value);

                insertAfter(searchValue, value);
                break;


            case 4:

                printf("Enter value before which to insert: ");
                scanf("%d", &searchValue);

                printf("Enter new value: ");
                scanf("%d", &value);

                insertBefore(searchValue, value);
                break;


            case 5:

                deleteBeginning();
                break;


            case 6:

                deleteEnd();
                break;


            case 7:

                printf("Enter value to delete: ");
                scanf("%d", &value);

                deleteValue(value);
                break;


            case 8:

                printf("Enter value to search: ");
                scanf("%d", &value);

                search(value);
                break;


            case 9:

                displayForward();
                break;


            case 10:

                displayBackward();
                break;


            case 11:

                displayTable();
                break;


            case 12:

                countNodes();
                break;


            case 13:

                deleteList();
                break;


            case 14:

                deleteList();
                printf("\nProgram terminated.\n");
                break;


            default:

                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 14);

    return 0;
}
