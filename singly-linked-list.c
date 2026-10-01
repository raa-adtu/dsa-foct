#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

/* Insert at Beginning */
void insertBeg() {
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter data: ");
    scanf("%d", &newNode->data);

    newNode->next = head;
    head = newNode;

    printf("Node inserted at beginning.\n");
}

/* Insert at End */
void insertEnd() {
    struct Node *newNode, *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    printf("Enter data: ");
    scanf("%d", &newNode->data);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("Node inserted at end.\n");
}

/* Delete from Beginning */
void deleteBeg() {
    struct Node *temp;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    head = head->next;

    printf("Deleted data: %d\n", temp->data);

    free(temp);
}

/* Delete from End */
void deleteEnd() {
    struct Node *temp, *prev;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        printf("Deleted data: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    temp = head;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    printf("Deleted data: %d\n", temp->data);

    prev->next = NULL;
    free(temp);
}

/* Display Linked List */
void display() {
    struct Node *temp;

    if (head == NULL) {
        printf("\nList is empty.\n");
        return;
    }

    temp = head;

    printf("\n========== LINKED LIST ==========\n\n");

    while (temp != NULL) {
        printf("[ %d | %p ]", temp->data, (void *)temp->next);

        if (temp->next != NULL)
            printf(" -> ");

        temp = temp->next;
    }

    printf(" -> NULL\n");

    /* Table */
    printf("\n========== NODE TABLE ==========\n");

    printf("%-20s %-10s %-20s\n",
           "Node Address", "Data", "Next Address");

    printf("----------------------------------------------------------\n");

    temp = head;

    while (temp != NULL) {
        printf("%-20p %-10d %-20p\n",
               (void *)temp,
               temp->data,
               (void *)temp->next);

        temp = temp->next;
    }

    printf("----------------------------------------------------------\n");
}

/* Main Function */
int main() {
    int choice;

    do {
        printf("\n\n===== SINGLY LINKED LIST =====\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Beginning\n");
        printf("4. Delete from End\n");
        printf("5. Display\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                insertBeg();
                break;

            case 2:
                insertEnd();
                break;

            case 3:
                deleteBeg();
                break;

            case 4:
                deleteEnd();
                break;

            case 5:
                display();
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}