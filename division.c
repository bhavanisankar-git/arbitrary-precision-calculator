#include "apc.h"
#include <stdlib.h>
#include <stdio.h>

/* Helper to remove leading zeros from a list and update tail */
void remove_leading_zeros(Dlist **head, Dlist **tail) {
    while (*head && (*head)->data == 0 && (*head)->next) {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    // Update tail
    *tail = *head;
    while (*tail && (*tail)->next)
        *tail = (*tail)->next;
}

/* Helper to check if a list represents zero */
static int is_zero_list(Dlist *head) {
    if (!head) return 1;
    Dlist *t = head;
    while (t) {
        if (t->data != 0) return 0;
        t = t->next;
    }
    return 1;
}

/* division: dividend = head1, divisor = head2
   headQ: pointer to quotient head (returned)
   headR: pointer to remainder head (returned)
*/
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headQ, Dlist **headR)
{
    // Check divisor existence / zero
    if (*head2 == NULL || is_zero_list(*head2))
    {
        printf("Division by zero error\n");
        return FAILURE;
    }

    // If dividend < divisor, quotient = 0, remainder = dividend
    if (compare_lists(head1, tail1, head2, tail2) < 0)
    {
        Dlist *quot_head = NULL, *quot_tail = NULL;
        if (insert_last(&quot_head, &quot_tail, 0) == FAILURE)
        {
            printf("Division failed: unable to set quotient to zero\n");
            return FAILURE;
        }
        Dlist *rem_head = NULL, *rem_tail = NULL;
        if (copy_list(head1, &rem_head, &rem_tail) == FAILURE)
        {
            printf("Division failed: unable to copy remainder\n");
            free_list(&quot_head);
            return FAILURE;
        }
        *headQ = quot_head;
        *headR = rem_head;
        return SUCCESS;
    }

    Dlist *curr = *head1;
    Dlist *rem_head = NULL, *rem_tail = NULL;
    Dlist *quot_head = NULL, *quot_tail = NULL;

    while (curr)
    {
        // Append current digit to remainder
        if (insert_last(&rem_head, &rem_tail, curr->data) == FAILURE)
        {
            printf("Memory error during remainder building\n");
            free_list(&rem_head);
            free_list(&quot_head);
            return FAILURE;
        }

        // Remove leading zeros in remainder
        remove_leading_zeros(&rem_head, &rem_tail);

        // Count how many times divisor fits in remainder
        int count = 0;
        while (compare_lists(&rem_head, &rem_tail, head2, tail2) >= 0)
        {
            Dlist *new_rem_head = NULL, *new_rem_tail = NULL;
            if (subtraction(&rem_head, &rem_tail, head2, tail2, &new_rem_head) == FAILURE)
            {
                printf("Division failed during subtraction\n");
                free_list(&rem_head);
                free_list(&quot_head);
                return FAILURE;
            }

            free_list(&rem_head);
            rem_head = new_rem_head;
            rem_tail = rem_head;
            while (rem_tail && rem_tail->next)
                rem_tail = rem_tail->next;

            count++;
        }

        // Append count (quotient digit)
        if (insert_last(&quot_head, &quot_tail, count) == FAILURE)
        {
            printf("Division failed while storing quotient digit\n");
            free_list(&rem_head);
            free_list(&quot_head);
            return FAILURE;
        }

        curr = curr->next;
    }

    remove_leading_zeros(&quot_head, &quot_tail);
    remove_leading_zeros(&rem_head, &rem_tail);

    *headQ = quot_head;
    *headR = rem_head;
    return SUCCESS;
}
