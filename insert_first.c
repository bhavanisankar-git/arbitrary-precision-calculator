#include"apc.h"
#include<stdlib.h>

int insert_at_begin(Dlist **head, Dlist **tail, int data) {
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head)
        (*head)->prev = new;
    else
        *tail = new;  // List was empty

    *head = new;
    return SUCCESS;
}
