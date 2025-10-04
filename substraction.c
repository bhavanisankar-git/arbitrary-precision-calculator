#include "apc.h"
#include <stdlib.h>

/*
 Behavior:
 - Produces absolute value of (num1 - num2) into headR.
 - If result is negative (num1 < num2), the result list is prefixed by a node with data == -1
   so that print_list prints '-' before the digits.
*/

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    int negative = 0;
    // Compare num1 and num2
    int cmp = compare_lists(head1, tail1, head2, tail2);
    Dlist *t1, *t2;
    Dlist *res_head = NULL, *res_tail = NULL;
    int borrow = 0;

    if (cmp == 0) // Equal numbers -> 0
    {
        if (insert_at_begin(&res_head, &res_tail, 0) == FAILURE)
        {
            printf("Subtraction failed: memory error\n");
            return FAILURE;
        }
        *headR = res_head;
        return SUCCESS;
    }
    else if (cmp < 0) // num1 < num2, compute num2 - num1 and mark negative
    {
        t1 = *tail2;
        t2 = *tail1;
        negative = 1;
    }
    else // num1 > num2
    {
        t1 = *tail1;
        t2 = *tail2;
    }

    while (t1 != NULL)
    {
        int d1 = t1->data - borrow;
        int d2 = (t2 != NULL) ? t2->data : 0;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int diff = d1 - d2;

        if (insert_at_begin(&res_head, &res_tail, diff) == FAILURE)
        {
            printf("Subtraction failed: memory error\n");
            return FAILURE;
        }

        t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    // Remove leading zeros from result
    while (res_head && res_head->data == 0 && res_head->next != NULL)
    {
        Dlist *temp = res_head;
        res_head = res_head->next;
        res_head->prev = NULL;
        free(temp);
    }

    // If negative, prefix a marker node with data == -1
    if (negative)
    {
        Dlist *negnode = malloc(sizeof(Dlist));
        if (!negnode) { free_list(&res_head); return FAILURE; }
        negnode->data = -1;
        negnode->prev = NULL;
        negnode->next = res_head;
        if (res_head) res_head->prev = negnode;
        res_head = negnode;
    }

    *headR = res_head;
    return SUCCESS;
}
