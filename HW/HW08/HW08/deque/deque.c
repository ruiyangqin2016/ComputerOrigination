/**
 * CS 2110 - Summer 2018 - Homework 08
 *
 * @author YOUR NAME HERE
 *
 * deque.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "deque.h"

/** The node struct. Has a prev pointer, next pointer, and data. 
  * DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO
  * Design consideration: Only this file should know about nodes
  * Only this file should be manipulating nodes.
  * DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES
  */
typedef struct dnode
{
  struct dnode* prev; /* Pointer to previous node */
  struct dnode* next; /* Pointer to next node */
  void* data;         /* User data */
} node;

/* Do not create any global variables here. Your deque library should obviously
 * work for multiple concurrent deques */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the deque
  * @return a node
  */
static node* create_node(void* data)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode -> data = data; // =(*newNode).data
    newNode -> prev = NULL;
    newNode -> next = NULL;
  return newNode;
}

/** create_deque
  *
  * Creates a deque by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty deque
  */
deque* create_deque(void)
{
    deque* newDeque = (deque*) malloc(sizeof(deque));
    newDeque -> head = NULL;
    newDeque -> tail = NULL;
    newDeque -> size = 0;
  return newDeque;
}

/** push_front
  *
  * Adds the data to the front of the deque.
  *
  * @param d a pointer to the deque structure.
  * @param data pointer to data the user wants to store in the deque.
  */
void push_front(deque *d, void *data)
{
    node* newNode = create_node(data);
    if (d -> head == NULL) {
        d -> head = newNode;
        d -> tail = newNode;
    } else{ // head is not NULL
        (d -> head) -> prev = newNode;
        newNode -> next = d -> head;
        d -> head = newNode;
    }
    d->size++;
}

/** push_back
  *
  * Adds the data to the back of the deque.
  *
  * @param d a pointer to the deque structure.
  * @param data pointer to data the user wants to store in the deque.
  */
void push_back(deque *d, void *data)
{
    node* newNode = create_node(data);
    if (d -> tail == NULL) {
        d -> tail = newNode;
        d -> head = newNode;
    } else {
        (d -> tail) -> next = newNode;
        newNode -> prev = d -> tail;
        d -> tail = newNode;
    }
    int size = d->size;
    size += 1;
    d->size = size;
}

/** front
  *
  * Gets the data at the front of the deque
  * If the deque is empty return NULL.
  *
  * @param d a pointer to the deque
  * @return The data at the first node in the deque or NULL.
  */
void *front(deque *d)
{
  /// @note you are returning the HEAD's DATA not the head node. Remember, the
  /// user should never deal with the deque nodes.
    if (d == NULL || d -> head == NULL) {
        return NULL;
    } else {
        return d -> head -> data;
    }
}

/** back
  *
  * Gets the data at the "end" of the deque
  * If the deque is empty return NULL.
  *
  * @param d a pointer to the deque structure
  * @return The data at the last node in the deque or NULL.
  */
void *back(deque *d)
{
    if (d == NULL || d -> tail == NULL) {
        return NULL;
    } else {
        return d -> tail -> data;
    }
}

/** get
  *
  * Gets the data at the specified index in the deque
  *
  * @param d a pointer to the deque structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the deque or NULL if index is
  *         out of range of the deque.
  */
void *get(deque *d, int index)
{
    void* returnValue = NULL;
    if (index >= d -> size || index < 0) {
        return returnValue;
    } else {
        node* newNode = d -> head;
        for (int i = 0; i < index; i++) {
            newNode = newNode -> next;
        }
        returnValue = newNode -> data;
        return returnValue;
    }
}

/** contains
  *
  * Traverses the deque, trying to see if the deque contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a deque of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the deque which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param d a pointer to the deque structure
  * @param data The data, to see if it exists in the deque
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the deque, or NULL if it doesn't exist
  */
void *contains(deque *d, void *data, deque_eq eq_func)
{
    if (d == NULL || d -> head == NULL) {
        return NULL;
    } else {
        node* newNode = d -> head;
	while (newNode != NULL) {
	    if (eq_func(newNode->data, data) == 0) {
                return newNode->data;
            }
            newNode = newNode -> next;
	}
        return NULL;
    }
}

/** pop_front
  *
  * Removes the node at the front of the deque, and returns its data to the user
  *
  * @param d a pointer to the deque.
  * @return The data in the first node, or NULL if the deque is NULL or empty
  */
void *pop_front(deque *d)
{
    if (d == NULL || d->head == NULL || d->size == 0) {
        //d->size = 0;
        return NULL;
    } else {
        node* newNode = d->head;
        if (d-> size == 1) {
            d->head = NULL;
            d->tail = NULL;
        } else {
            d->head = newNode -> next;
        }
        // int size = d->size;
        // size -= 1;
        // d->size = size;
        d->size--;

        void* a = newNode->data;
        free(newNode);
        return a;
    }
}

/** pop_back
  *
  * Removes the node at the end of the deque, and returns its data to the user
  *
  * @param d a pointer to the deque.
  * @return The data in the first node, or NULL if the deque is NULL or empty
  */
void *pop_back(deque *d)
{
    if (d == NULL || d->tail == NULL || d->size == 0) {
        d->size = 0;
        return NULL;
    } else {
        node* newNode = d->tail;
        if (d->size == 1) {
            d->head = NULL;
            d->tail = NULL;
        } else {
            d->tail = newNode -> prev;
        }
        int size = d->size;
        size -= 1;
        d->size = size;
        void* a = newNode->data;
        free(newNode);
        return a;
    }
}

/** copy_deque
  *
  * Create a new deque structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param d A pointer to the deque structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this deque, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the deque for in your test
  * @return The deque structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
deque* copy_deque(deque *d, deque_copy copy_func)
{
    if (d == NULL || d->head == NULL) {
        return NULL;
    } else {
        node* newNode = d->head;
        deque* newD = NULL;
        node* Dnode = newD->head;
        while (newNode != NULL) {
            Dnode = copy_func(newNode);
            Dnode = Dnode->next;
            newNode = newNode->next;
        }
        return newD;
    }
}

/** size
  *
  * Gets the size of the deque
  *
  * @param d a pointer to the deque structure
  * @return The size of the deque
  */
int size(deque *d)
{
    return d-> size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns
  * true
  *
  * @param d a pointer to the deque structure
  * @param pred_func a pointer to a function that when it returns true, it
  *                  should remove the element from the deque.
  * @param free_func a pointer to a function that is responsible for freeing the
  *                  node's data
  * @return the number of nodes that were removed.
  */
int remove_if(deque *d, deque_pred pred_func, deque_op free_func)
{
  /// @todo Implement changing the return value!
  /// @note remember to also free all nodes you remove.
  /// @note be sure to call pred_func on the NODES DATA to check if the node
  ///       needs to be removed.
  /// @note free_func is a function that is responsible for freeing the node's
  ///       data only.
    int numberOfRemoved = 0;
    if (d == NULL || d->head == NULL) {
        return numberOfRemoved;
    } else {
        node* newNode = d->head;
        while (newNode != NULL) {
            if (pred_func(newNode->data) == 1) {
                if (d->size == 1) {
                    d->head = NULL;
                    d->tail = NULL;
                    d->size = 0;
                    free_func(newNode->data);
                    free(newNode);
                    newNode = NULL;
                } else if (newNode == d->head) {
                    newNode->next->prev = NULL;
                    d->head = newNode->next;
                    d->size = d->size - 1;
                    free_func(newNode->data);
                    free(newNode);
                    newNode = newNode->next;
                } else if (newNode == d->tail) {
                    newNode->prev->next = NULL;
                    d->tail = newNode->prev;
                    d->size = d->size - 1;
                    free_func(newNode->data);
                    free(newNode);
                    newNode = newNode->next;
                } else {
                    d->size --;
                    newNode->next->prev = newNode->prev;
                    newNode->prev->next = newNode->next;
                    free_func(newNode->data);
                    free(newNode);
                    newNode = newNode->next;
                }
                numberOfRemoved++;
            } else {
                newNode = newNode->next;
            }
        }
        return numberOfRemoved;
    }
}

/** is_empty
  *
  * Checks to see if the deque is empty.
  *
  * @param d a pointer to the deque structure
  * @return 1 if the deque is indeed empty, or 0 otherwise.
  */
int is_empty(deque *d)
{

    int isEmpty = 0;
    if (d == NULL || d->head == NULL || d->size == 0) {
        isEmpty = 1;
    }
    return isEmpty;
}

/** empty_deque
  *
  * Empties the deque. After this is called, the deque should be empty.
  * This does not free the deque struct itself, just all nodes and data within.
  *
  * @param d a pointer to the deque structure
  * @param free_func function used to free the nodes' data.
  */
void empty_deque(deque *d, deque_op free_func)
{
  /// @todo Implement
  /// @note Free all of the nodes, not the deque structure itself.
  /// @note do not free the deque structure itself.
    d->size = 0;
    if (d == NULL || d->head == NULL) {
        return;
    } else {
        node *newNode = d -> head;
        while (newNode != NULL) {
            // d -> head = newNode -> next;
            node *record = newNode;
            free_func(newNode -> data);
            free(newNode);
            newNode = record -> next;
        }
        d -> head = NULL;
        d -> tail = NULL;
        d -> size = 0;
        // node* newNode = d->head;
        // while (newNode -> next != NULL) {
        //   free_func(newNode->data);
        //   free(newNode);
        //   newNode = newNode->next;
        // }
        // free_func(newNode->data);
        // free(newNode);
        // d->size = 0;
    }
}

/** traverse
  *
  * Traverses the deque, calling a function on each node's data.
  *
  * @param d a pointer to the deque structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(deque *d, deque_op do_func)
{
  /// @todo Implement
    if (d == NULL) {
	return;
    }
    node* newNode = d->head;
    // do_func(newNode->data);
    while (newNode != NULL) {
        do_func(newNode -> data);
        newNode = newNode -> next;
    }
    // while (newNode->next != NULL) {
    //     newNode = newNode->next;
    //     do_func(newNode->data);
    // }
}
