#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/dir.h>
#include <math.h>

struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

int ProcessNum(char arr[]);

int main () {

    int fd, sz;
    fd = open("nodes.txt", O_RDONLY);
    if (fd < 0) {
        perror("r1");
        exit(1);
    }

    char* buff = (char*)calloc(1, sizeof(char));
    char numBuff[20] = {}; 
    int indx = 0;

    struct node* prev = malloc(sizeof(struct node));
    struct node* head = malloc(sizeof(struct node));
    struct node* curr = head;

    int count = 0;
    while ((sz = read(fd, buff, 1)) > 0) {

        if (isdigit(*buff)) {
            numBuff[indx] = *buff;
            indx += 1;

        } else if (isblank(*buff)) {
            count += 1;
            curr->data = ProcessNum(numBuff);
            curr->prev = prev;
            prev = curr;
            curr = malloc(sizeof(struct node));
            prev->next = curr;
            indx = 0;
            memset(numBuff, 0, sizeof(numBuff));
        }

    }
    if (indx > 0) {
        count += 1;
        curr->data = ProcessNum(numBuff);
        curr->prev = prev;
        prev = curr;
        curr = malloc(sizeof(struct node));
        prev->next = curr;
    }

    int integer = -1;
    int *choice = &integer;

    while (*choice != 0) {
        printf("%s", "What else do you want?\nTo insert a new node press 1. \nTo insert a new node after a given node press 2 \nTo delete a node press 3 \nTo exit press 0.\n");
        scanf( "%d", choice);
        if (*choice == 1) {
            printf("%s", "Insert your node number. \n");
            struct node* newNode = malloc(sizeof(struct node));
            int *tempPtr;
            scanf("%d", tempPtr);
            newNode->data = *tempPtr;
            newNode->prev = prev;
            prev->next = newNode;
            newNode->next = curr;
            curr->prev = newNode;
            curr = newNode;
            
            printf("%s", "Your new linked list \n");
            struct node* temp3 = head;
            printf("%d", temp3->data);
            temp3 = temp3->next;
            while (temp3->next != NULL) {
                printf(" -> %d", temp3->data);
                temp3 = temp3->next;
            }
            printf("\n");
            
        } else if (*choice == 2) {
            printf("%s", "Insert your new node number. \n");
            struct node* newNode = malloc(sizeof(struct node));
            int tempPtr; 
            scanf("%d", &tempPtr);
            newNode->data = tempPtr;
            printf("%s", "Enter previous node number. \n");
            int val;
            scanf("%d", &val);

            struct node* temp2 = head;
            struct node* prev2 = head;
            while (temp2->next != NULL) {
                if (temp2->data == val) {
                    newNode->prev = temp2;
                    newNode->next = temp2->next;
                    temp2->next = newNode;
                    newNode->next->prev = newNode;
                    break;
                } else {
                    prev2 = temp2;
                    temp2 = temp2->next;
                }
            }
            if (temp2->next == NULL) {
                newNode->prev = temp2;
                temp2->next = newNode;
                newNode->next = NULL;
            }
 

            printf("%s", "Your new linked list \n");
            struct node* temp3 = head;
            printf("%d", temp3->data);
            temp3 = temp3->next;
            while (temp3->next != NULL) {
                printf(" -> %d", temp3->data);
                temp3 = temp3->next;
            }
            printf("\n");
            
        } else if (*choice == 3) {
            printf("Insert the node number you want to delete. \n");
            int val;
            scanf("%d", &val);
            struct node* prev2 = head;
            struct node* temp2 = head;
            while (temp2->next != NULL) {
                if (temp2->data == val) {
                    if (temp2->prev == NULL) {
                        head = temp2->next;
                        break;
                    }

                    temp2 = temp2->next;
                    prev2->next = temp2;
                    temp2->prev = prev2;
                } else {
                    prev2 = temp2;
                    temp2 = temp2->next;
                }
            }
            printf("%s", "Your new linked list \n");
            struct node* temp3 = head;
            printf("%d", temp3->data);
            temp3 = temp3->next;
            while (temp3->next != NULL) {
                printf(" -> %d", temp3->data);
                temp3 = temp3->next;
            }
            printf("\n");
        } 
    }

    printf("%s", "Your linked list ");
    struct node* temp1 = head;
    printf("%d", temp1->data);
    temp1 = temp1->next;
    while (temp1->next != NULL) {
        printf(" -> %d ", temp1->data);
        temp1 = temp1->next;
    }

    printf("%s", "\n");
    printf("Your linked list in reverse order ");
    printf("%d", prev->data);
    prev = prev->prev;
    while (prev->next != NULL) {
        printf(" -> %d", prev->data);
        prev = prev->prev;
    }
}


int ProcessNum(char arr[]) {
    int places = strlen(arr);
    int num = 0;
    for (int i = 0; i < places; i++) {
        num += (arr[i] - '0') * pow(10, places - i - 1);
    }
    return num;
}

