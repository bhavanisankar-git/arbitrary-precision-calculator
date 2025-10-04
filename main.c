/**************************************************************************************************************************************************************
Name            : K Bhavani sankar
Title		    : Arbitrary Precision Calculator
Description	    : The Arbitrary Precision Calculator is a C program that performs addition, subtraction, multiplication, and division on numbers of any size 
                  using doubly linked lists to store each digit. It overcomes the limits of standard data types, supports very large integers, and outputs 
                  accurate results for all four operations.
***************************************************************************************************************************************************************/
#include "apc.h"
#include<string.h>
#include<ctype.h>
#include<stdio.h>

int validate(int argc, char *argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *operator)
{
    if (argc < 4)
    {
        printf("Insufficient number of arguments!\n");
        return FAILURE;
    }

    char *opr1 = argv[1];
    char *opr2 = argv[3];
    char *operator_str = argv[2];

    // Validate operator
    if (strcmp(operator_str, "+") != 0 && strcmp(operator_str, "-") != 0 &&
        strcmp(operator_str, "x") != 0 && strcmp(operator_str, "/") != 0)
    {
        printf("Invalid operator: %s\n", operator_str);
        return FAILURE;
    }

    *operator = operator_str[0];  // Copy operator to the passed char variable

    // Validate and insert first operand
    for (int i = 0; opr1[i]; i++)
    {
        if (!isdigit((unsigned char)opr1[i]))
        {
            printf("Invalid character in first operand: %c\n", opr1[i]);
            return FAILURE;
        }
        if (insert_last(head1, tail1, opr1[i] - '0') == FAILURE)
        {
            printf("Insertion failed for operand 1\n");
            return FAILURE;
        }
    }

    // Validate and insert second operand
    for (int i = 0; opr2[i]; i++)
    {
        if (!isdigit((unsigned char)opr2[i]))
        {
            printf("Invalid character in second operand: %c\n", opr2[i]);
            return FAILURE;
        }
        if (insert_last(head2, tail2, opr2[i] - '0') == FAILURE)
        {
            printf("Insertion failed for operand 2\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

int main(int argc, char *argv[])
{
    /* Declare the pointers */
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *headQ = NULL;
    char operator;

    /* Code for reading the inputs */
    if (validate(argc, argv, &head1, &tail1, &head2, &tail2, &operator) == FAILURE)
    {
        printf("Validation failed!\n");
        return FAILURE;
    }

    switch (operator)
    {
        case '+':
            if (addition(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
            {
                printf("Addition failed!\n");
                return FAILURE;
            }
            printf("Result: ");
            print_list(headR);
            break;

        case '-':
            if (subtraction(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
            {
                printf("Subtraction failed!\n");
                return FAILURE;
            }
            printf("Result: ");
            print_list(headR);
            break;

        case 'x':
            if (multiplication(&head1, &tail1, &head2, &tail2, &headR) == FAILURE)
            {
                printf("Multiplication failed!\n");
                return FAILURE;
            }
            printf("Result: ");
            print_list(headR);
            break;

        case '/':
            if (division(&head1, &tail1, &head2, &tail2, &headQ, &headR) == FAILURE)
            {
                printf("Division failed!\n");
                return FAILURE;
            }
            printf("Quotient: ");
            print_list(headQ);
            printf("Remainder: ");
            print_list(headR);
            free_list(&headQ);
            break;

        default:
            printf("Invalid Input :-( Try again...\n");
    }

    /* Free all lists */
    free_list(&head1);
    free_list(&head2);
    free_list(&headR);

    return 0;
}

