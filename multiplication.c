#include "apc.h"
#include <stdlib.h>
#include <stdio.h>

/*
 Implements grade-school multiplication.
 Steps:
 - Convert each list to an integer-digit array (most-significant first).
 - Multiply producing result array of size n1 + n2.
 - Convert result array into a linked list (skip leading zeros; if all zeros, create a single 0 node).
*/

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    if (!*head1 || !*head2) {
        // If any operand is missing, treat as 0
        if (insert_last(headR, headR, 0) == FAILURE) return FAILURE; // though unlikely path
        return SUCCESS;
    }

    // Convert list1 to array
    int n1 = 0, n2 = 0;
    Dlist *t;           
    t = *head1;    // start at the head of list1
    while (t) 
    { 
        n1++;   // increase count for each node
        t = t->next;    // move to next node
    }
    t = *head2;     
    while (t) 
    { 
        n2++; 
        t = t->next; 
    }

    int *a = malloc(sizeof(int) * n1);      // creating memory for the first number
    int *b = malloc(sizeof(int) * n2);      // creating memory for sec number
    
    if (!a || !b) 
    { 
        free(a);   // free both pointers if either of the memory is not allocated
        free(b); 
        return FAILURE; // return failure
    }

    t = *head1;
    for (int i = 0; i < n1 && t; ++i, t = t->next) 
    a[i] = t->data;
    t = *head2;
    for (int i = 0; i < n2 && t; ++i, t = t->next) 
    b[i] = t->data;

    // result array (size n1 + n2), initialized to 0
    int res_size = n1 + n2;
    int *res = calloc(res_size, sizeof(int));
    if (!res) { free(a); free(b); return FAILURE; }

    // multiply (most-significant first arrays)
    // We will index from right (least significant). Convert indices accordingly:
    for (int i = n1 - 1; i >= 0; --i) {
        for (int j = n2 - 1; j >= 0; --j) {
            int pos_low = (i + j + 1);
            int mul = a[i] * b[j] + res[pos_low];
            res[pos_low] = mul % 10;
            res[pos_low - 1] += mul / 10;
        }
    }

    // convert result array to linked list skipping leading zeros
    int idx = 0;
    while (idx < res_size - 1 && res[idx] == 0) idx++; // keep one zero if entire result is zero

    Dlist *rhead = NULL, *rtail = NULL;
    for (; idx < res_size; ++idx) {
        if (insert_last(&rhead, &rtail, res[idx]) == FAILURE) {
            free(a); free(b); free(res); free_list(&rhead);
            return FAILURE;
        }
    }

    free(a); free(b); free(res);
    *headR = rhead;
    return SUCCESS;
}
