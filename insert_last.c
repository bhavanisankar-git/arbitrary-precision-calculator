#include"apc.h"
#include<stdlib.h>

int insert_last(Dlist **head,Dlist **tail,int data)
{
   Dlist *new=malloc(sizeof(Dlist));
   if(new==NULL)
   {
    return FAILURE;
   } 
   new->data=data;
   new->prev=NULL;
   new->next=NULL;
   if(*head==NULL && *tail==NULL)
   {
    *head=new;
    *tail=new;
    return SUCCESS;
   }
   (*tail)->next=new;
   new->prev=*tail;
   *tail=new;
   return SUCCESS;
}
