#include"apc.h"
#include<stdio.h>
#include<stdlib.h>

void print_list(Dlist *head) {
    if (!head) {
        printf("0\n");
        return;
    }

    // If first node encodes negative flag (data == -1)
    if (head->data == -1) {
        printf("-");
        head = head->next;
        if (!head) { printf("0\n"); return; }
    }

    while (head) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}


// Returns 1 if num1 > num2, 0 if equal, -1 if num1 < num2
int compare_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    Dlist *t1 = *head1;
    Dlist *t2 = *head2;

    // Count digits (skip any leading negative marker if present)
    int len1 = 0, len2 = 0;
    while (t1) { 
        if (t1->data != -1) len1++; 
        t1 = t1->next; 
    }
    while (t2) { 
        if (t2->data != -1) len2++; 
        t2 = t2->next; 
    }

    // Compare lengths
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // Same length, compare digit by digit (skip -1 nodes)
    t1 = *head1;
    t2 = *head2;
    while (t1 && t2)
    {
        if (t1->data == -1) { t1 = t1->next; continue; }
        if (t2->data == -1) { t2 = t2->next; continue; }
        if (t1->data > t2->data) return 1;
        if (t1->data < t2->data) return -1;
        t1 = t1->next;
        t2 = t2->next;
    }
    return 0; // Equal
}


// Copies a doubly linked list from src_head to dest_head/dest_tail
int copy_list(Dlist **src_head, Dlist **dest_head, Dlist **dest_tail)
{
    Dlist *temp = *src_head;
    *dest_head = NULL;
    *dest_tail = NULL;

    while (temp)
    {
        if (insert_last(dest_head, dest_tail, temp->data) == FAILURE)
        {
            printf("copy_list: memory allocation failed\n");
            return FAILURE;
        }
        temp = temp->next;
    }
    return SUCCESS;
}


void free_list(Dlist **head)
{
    Dlist *temp;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
