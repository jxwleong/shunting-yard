#include "LinkedList.h"
#include <stdio.h>
#include <malloc.h>
#include "Exception.h"
#include "Error.h"

// ItemToAdd->next neccessary?
int *LinkedListAddToHead(LinkedList *List, void *data){

  if(*(int*)(data) == NULL){
    throwSimpleError(ERR_DATA_NULL,"Data trying to add is NULL");
  }
  else{
    ListItem *newLinkedList = (struct ListItem*)malloc (sizeof(struct ListItem));
    if(List->head == NULL){
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = NULL;
      List->count++;
      List->head = newLinkedList;
      List->tail = newLinkedList;
    }
    else{
      newLinkedList->data = *(int*)(data);
      newLinkedList->next = List->head;     // Take previous node as next
      List->count++;
      List->head = newLinkedList;           // Point to the next node
      List->tail = newLinkedList;
    }
    return newLinkedList;
} }

ListItem *LinkedListRemoveFromHead(LinkedList *List){
  if(List->head == NULL){
    throwSimpleError(ERR_LINKEDLIST_NULL,"Empty linkedlist detected");
  }
  else{
    List->head = List->head->next;
    List->count--;
  }
}
