#ifndef APC_H
#define APC_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* prototypes */
// int validate(int argc, char *argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *operator);
void print_list(Dlist *head);
int compare_lists(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);
int insert_last(Dlist **head,Dlist **tail,int data);
int insert_at_begin(Dlist **head, Dlist **tail, int data);
int copy_list(Dlist **src_head, Dlist **dest_head, Dlist **dest_tail);
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headQ, Dlist **headR);
void free_list(Dlist **head);
void remove_leading_zeros(Dlist **head, Dlist **tail);
#endif
