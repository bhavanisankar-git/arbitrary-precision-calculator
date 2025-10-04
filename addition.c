#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    Dlist *res_head = NULL, *res_tail = NULL;
    int carry = 0;

    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int d1 = (t1 != NULL) ? t1->data : 0;
        int d2 = (t2 != NULL) ? t2->data : 0;
        int sum = d1 + d2 + carry;

        if (insert_at_begin(&res_head, &res_tail, sum % 10) == FAILURE)
        {
            printf("Failed to insert result node\n");
            return FAILURE;
        }

        carry = sum / 10;

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    *headR = res_head;
    return SUCCESS;
}
