
#include "llist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Test your character list code here!
int main()
{
  LLIST* llist = create_list();

  printf("TEST CASE 1: create_list()\n");
  assert(!(llist -> head));
  assert(!(llist -> tail));
  assert(!(llist -> size));

  push_front(llist, 'o');

  printf("TEST CASE 2: push_front(llist, 'o')\n");

  assert((llist -> head -> data) == 'o');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 2);

  push_front(llist, 'l');

  printf("TEST CASE 3: push_front(llist, 'l')\n");

  assert((llist -> head -> data) == 'l');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 3);

  push_front(llist, 'l');

  printf("TEST CASE 4: push_front(llist, 'l')\n");

  assert((llist -> head -> data) == 'l');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 4);

  push_front(llist, 'e');

  printf("TEST CASE 5: push_front(llist, 'e')\n");

  assert((llist -> head -> data) == 'e');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 5);

  push_front(llist, 'h');

  printf("TEST CASE 6: push_front(llist, 'h')\n");

  assert((llist -> head -> data) == 'h');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 6);

  char c0 = pop_front(llist);

  printf("TEST CASE 7: pop_front(llist)\n");

  assert((llist -> head -> data) == 'e');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 5);
  assert(c0 == 'h');

  char c1 = pop_front(llist); // Pop 'e'
  char c2 = pop_front(llist); // Pop 'l'
  char c3 = pop_front(llist); // Pop 'l'
  char c4 = pop_front(llist); // Pop 'o'
 
  printf("TEST CASE 8: pop_front() all characters except \'\\0\'\n");

  assert((llist -> head -> data) == '\0');
  assert((llist -> tail -> data) == '\0');
  assert(llist -> size == 1);
  assert(c1 == 'e');
  assert(c2 == 'l');
  assert(c3 == 'l');
  assert(c4 == 'o');

  char c5 = pop_front(llist); // Pop '\0'

  printf("TEST CASE 9: Pop the \'\\0\'\n");

  assert(!(llist -> head));
  assert(!(llist -> tail));
  assert(!(llist -> size));
  assert(c5 == '\0');

  char c6 = pop_front(llist); // Pop

  printf("TEST CASE 10: Popping an empty list returns -1\n");

  assert(!(llist -> head));
  assert(!(llist -> tail));
  assert(!(llist -> size));
  assert(c6 == -1);

  push_front(llist, 'y');
  push_front(llist, 'e');
  push_front(llist, 'h');

  printf("TEST CASE 11: Create a list for \"hey\"\n");

  assert((llist -> head -> data) == 'h');
  assert((llist -> tail -> data) == '\0');
  assert((llist -> size) == 4);

  char *message = get_string(llist);

  printf("TEST CASE 12: get_string() returns \"hey\"\n");

  assert(!strcmp(message, "hey"));

  free(message);

  printf("TEST CASE 13: Destroy the list\n");

  destroy_list(llist);

  printf("TEST CASE 14: pop_front() on a NULL list\n");

  LLIST *null_list = NULL;

  char c7 = pop_front(null_list);

  assert(c7 == -1);

  // Implement your own tests here!
  // Don't forget to free everything the functions might return when you finish.

  
  return 0;
}
