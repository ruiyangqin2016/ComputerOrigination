#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Here we are going to write some functions to support a deque that stores
 * person data (name, age)
 */
struct person {
  char *name;
  int age;
};

/* Example functions given to you. If you want to truly grasp these concepts,
 * try writing your own structs and functions as well!
 */

// Create a new person
struct person *create_person(const char *name, int age) {
  struct person *p = (struct person*) malloc(sizeof(struct person));
  p->name = malloc(strlen(name) + 1);
  strcpy(p->name, name);
  p->age = age;
  return p;
}

static int print_count;
static char *last_printed;

// Print a person
void print_person(void *data) {
  struct person *p = (struct person*) data;
  ++print_count;
  last_printed = p->name;
  printf("%s, %d\n", p->name, p->age);
}

// Copy a person
void *copy_person(const void *data) {
  struct person *p = (struct person*) data;
  return create_person(p->name, p->age);
}

// Free a person
void free_person(void *data) {
  // This is safe because we should only be passing in person struct pointers
  struct person *p = (struct person*) data;
  // free any malloc'd pointers contained in the person struct (just name)
  free(p->name);
  // Now free the struct itself; this takes care of non-malloc'd data, like age.
  free(p);
}

// Compare people by age
int person_age_comp(const void *data1, const void *data2) {
  struct person *p1 = (struct person*) data1;
  struct person *p2 = (struct person*) data2;
  return p1->age - p2->age;
}

// Compare people by name
int person_name_comp(const void *data1, const void *data2) {
  struct person *p1 = (struct person*) data1;
  struct person *p2 = (struct person*) data2;
  return strcmp(p1->name, p2->name);
}

// Tell if a person is age 50
int is_age_50(const void *data) {
  struct person *p = (struct person*) data;
  return p->age == 50;
}

// Tell if a person is 23 or older
int is_age_23_or_greater(const void *data) {
  struct person *p = (struct person*) data;
  return p->age >= 23;
}

/* This main function does a little testing. Like all good CS Majors, you should
 * test your code here. There is no substitute for testing and you should be
 * sure to test for all edge cases, like calling empty_deque on an empty deque.
 */
int main(void) {

  printf("\nTEST CASE 1\nAn empty deque should have size 0:\n");
  deque *d1 = create_deque();
  printf("Size: %d\n", size(d1));
  assert(!size(d1));
  assert(!d1->head);
  assert(!d1->tail);
  assert(is_empty(d1));

  printf("\nTEST CASE 2\nAfter adding one element, size should be 1:\n");
  push_front(d1, create_person("Preston", 26));
  printf("Size: %d\n", size(d1));
  assert(size(d1) == 1);
  assert(!is_empty(d1));

  printf("\nTEST CASE 3\nTraversal should print the one element:\n");
  print_count = 0;
  last_printed = NULL;
  traverse(d1, print_person);
  assert(!strcmp(last_printed, "Preston") && print_count == 1);

  printf("\nTEST CASE 4\nThe one element should be the front:\n");
  print_count = 0;
  last_printed = NULL;
  print_person(front(d1));
  assert(!strcmp(last_printed, "Preston") && print_count == 1);

  printf("\nTEST CASE 5\nThe one element should be the back:\n");
  print_count = 0;
  last_printed = NULL;
  print_person(back(d1));
  assert(!strcmp(last_printed, "Preston") && print_count == 1);

  printf("\nTEST CASE 6\nPreston should be contained in the deque:\n");
  struct person *preston = create_person("Preston", 50);
  printf("Preston %s in deque\n", contains(d1, preston, person_name_comp) ?
      "is" : "isn\'t");
  struct person *ptemp = (struct person*) contains(d1, preston, person_name_comp);
  assert(ptemp->age == 26);

  printf("\nTEST CASE 7\nYuuna should not be contained in the deque:\n");
  struct person *yuuna = create_person("Yuuna", 23);
  printf("Yuuna %s in deque\n", contains(d1, yuuna, person_name_comp) ?
      "is" : "isn\'t");
  assert(!contains(d1, yuuna, person_name_comp));

  printf("\nTEST CASE 8\nPop Preston from the front...\n");
  ptemp = (struct person*) pop_front(d1);
  assert(!size(d1));
  assert(!person_name_comp(preston, ptemp));
  printf("Success!\n");
  free_person(ptemp);

  printf("\nTEST CASE 9\nAdd Yuuna, pop from the back...\n");
  push_back(d1, yuuna);
  assert(size(d1) == 1);
  ptemp = pop_back(d1);
  assert(ptemp == yuuna);
  assert(!size(d1));
  printf("Success!\n");

  // Free these people because we are done using them
  free_person(preston);
  free_person(yuuna);

  // Free this deque because we are done using it
  free(d1);

  return 0;
}
