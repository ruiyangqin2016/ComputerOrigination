
#include "llist.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Function: create_list
 * 
 * Creates a new list by initializing the fields and returns a pointer 
 * to the list.
 */
LLIST *create_list()
{
  LLIST *newList = (LLIST*)malloc(sizeof(LLIST));
  newList->head = NULL;
  newList->tail = NULL;
  newList->size = 0;
  return newList;
//  return NULL;
}

/**
 * Function: create_node
 * 
 * Creates a new node from the given data and returns a pointer to the node.
 */
LNODE *create_node(char data)
{
//  UNUSED_PARAMETER(data);
  LNODE* newNode = (LNODE*) malloc(sizeof(LNODE));
  newNode->next = NULL;
  newNode->data = data;
  return newNode;
//  return NULL;
}

/**
 * Function: push_front
 * 
 * Adds a node with the given data to the head of the linked list. If the list
 * is empty then you must first push a null terminator character '\0' node and
 * then the data node.
 * 
 * In other words, '\0' will be the tail of the list, so doing so will make the 
 * size of the list increase by two.
 * 
 * Simply return if llist or data are NULL.
 */
void push_front(LLIST *llist, char data)
{
  LNODE* newNode = create_node(data);
  if (llist->head == NULL) {
    LNODE* newNode1 = create_node('\0');
    llist->head = newNode;
    llist->tail = newNode1;
    llist->size = 2;
    llist->head->next = llist->tail;
  } else {
    newNode->next = llist->head;
    llist->head = newNode;
    llist->size++;
  }
  return;
}

/**
 * Function: pop_front
 * 
 * Removes the first node from the head of the linked list and returns the char 
 * from the removed node to the user. Be sure to free the node properly!
 * 
 * Pop normally for the last char that's not the null terminator. After popping,
 * the size of the list will be 1. i.e. The only node will hold the '\0'.
 * 
 * After removing the final node, holding the '\0', the list's head and tail 
 * will point to NULL and the list will have size 0.
 * 
 * Note: If the list is empty or NULL, return -1.
 */
char pop_front(LLIST *llist)
{
  if (llist == NULL || llist->head == NULL) {
    return -1;
  } else {
    LNODE* newNode = llist->head;
    char holdData = newNode->data;
    if (llist->head->data == '\0') {
      llist->head = NULL;
      llist->tail = NULL;
      llist->size = 0;
      free(newNode);
    } else {
      llist->head = newNode->next;
      free(newNode);
      llist->size--;
    }
    return holdData;
  }
}

/**
 * Function: destroy_list
 * 
 * All memory used in the linked list that was allocated from the heap should 
 * be freed. This includes all of the node structs in the linked lists and the 
 * linked list struct.
 */
void destroy_list(LLIST *llist)
{
    if (llist == NULL || llist->head == NULL) {
        free(llist);
        return;
    } else {
        LNODE* currNode = llist->head;
        while (currNode != NULL) {
            LNODE* nextNode = currNode->next;
            free(currNode);
            llist->size--;
            currNode = nextNode;
        }
        free(llist);
    }
}


/** 
 * Function: get_string
 * 
 * Returns a persistent char* -- a string from your list's data.
 * 
 * This means you will need to traverse through your list and return the final 
 * string. For example, if you have a linked list such as:
 *  'h'->'e'->'l'->'l'->'o'->\0', 
 * then you should return the string: "hello". You have a null terminator in 
 * your list for a reason!
 * 
 * If the list is empty or NULL, return NULL.
 */
char* get_string(LLIST *llist)
{
    if (llist == NULL) {
        return NULL;
    } else {
        char *w = malloc(sizeof(char) * (llist->size + 1));
        LNODE* current = llist->head;
        int i = 0;
        if (llist == NULL) {
            return NULL;
        } else {
            while (current != '\0') {
                w[i] = current->data;
                current = current -> next;
                i++;
            }
        }
        w[i] = '\0';
        return w;
    }
}