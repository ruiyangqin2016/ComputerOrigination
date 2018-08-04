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

// Tell if a person is age 21

int is_age_21(const void *data) {
  struct person *p = (struct person*) data;
  return p->age == 21;
}

int is_age_22(const void *data) {
  struct person *p = (struct person*) data;
  return p->age == 22;
}

int is_age_40(const void *data) {
  struct person *p = (struct person*) data;
  return p->age == 40;
}



int is_age_18_or_less(const void *data) {
  struct person *p = (struct person*) data;
  return p->age <= 18;
}

// Tell if a person is 23 or older
int is_age_24_or_greater(const void *data) {
  struct person *p = (struct person*) data;
  return p->age >= 24;
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
  printf("Last printed %s\n",last_printed);
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

  printf("\nTEST CASE 10\nAn empty deque should have size 0:\n");
  deque *d2 = create_deque();
  printf("Size: %d\n", size(d2));
  assert(!size(d2));
  assert(!d2->head);
  assert(!d2->tail);
  assert(is_empty(d2));

  printf("\nTEST CASE 12\nAfter adding 9 element, size should be 9:\n");
  push_front(d2, create_person("Jackie", 20));
  push_front(d2, create_person("Evan", 22));
  push_back(d2, create_person("Riley", 17));
  push_front(d2, create_person("Bryce", 19));
  push_back(d2, create_person("Sarah", 22));
  push_front(d2, create_person("Abby", 21));
  push_back(d2, create_person("Teegan", 18));
  push_back(d2, create_person("Zach", 25));
  push_front(d2, create_person("Aaron", 28));
  printf("Size: %d\n", size(d2));
  assert(size(d2) == 9);
  assert(!is_empty(d2));

  printf("\n testing get functions\n");

  printf("\n testing index 0\n");
  last_printed = NULL; 
  print_person(get(d2, 0));
  assert(!strcmp(last_printed, "Aaron"));

  printf("\n testing index 2\n");
  last_printed = NULL; 
  print_person(get(d2, 2));
  assert(!strcmp(last_printed, "Bryce")); 

  printf("\n testing index 4\n");
  last_printed = NULL; 
  print_person(get(d2, 4));
  assert(!strcmp(last_printed, "Jackie"));

  printf("\n testing index 6\n");
  last_printed = NULL; 
  print_person(get(d2, 6));
  assert(!strcmp(last_printed, "Sarah"));

  printf("\n testing index 8\n");
  last_printed = NULL; 
  print_person(get(d2, 8));
  assert(!strcmp(last_printed, "Zach"));

  //out of range make sure return null
  last_printed = NULL; 
  assert(!get(d2, 9));

  struct person *evan = create_person("Evan", 22);
  printf("Evan %s in deque\n", contains(d2, evan, person_name_comp) ?
      "is" : "isn\'t");
  struct person *ptemp2 = (struct person*) contains(d2, evan, person_name_comp);
  assert(ptemp2->age == 22);

  struct person *zach = create_person("Zach_22", 22);
  printf("Zach_22 %s in deque\n", contains(d2, zach, person_name_comp) ?
      "is" : "isn\'t");

  printf("\nThis is the original deque\n");
  traverse(d2, print_person);

  printf("\nThis is the deque after removing people who are 22\n");
  assert(remove_if(d2, is_age_22, free_person) == 2);
  traverse(d2, print_person);

  printf("\nThis is the deque after removing people who are younger then 18\n");
  assert(remove_if(d2, is_age_18_or_less, free_person) == 2);
  traverse(d2, print_person);

  printf("\nThis is the deque after removing people who are 23 or older\n");
  assert(remove_if(d2, is_age_24_or_greater, free_person) == 2);
  traverse(d2, print_person);

  printf("\nThis is the deque after removing the head (Abby)\n");
  assert(remove_if(d2, is_age_21, free_person) == 1);
  traverse(d2, print_person);


  printf("\nAdding 5 more elements:\n");
  push_front(d2, create_person("Amy", 12));
  push_front(d2, create_person("Caroline", 32));
  push_back(d2, create_person("Sammy", 22));
  push_front(d2, create_person("Adam", 22));
  push_back(d2, create_person("Timmy", 22));
  printf("Size: %d\n", size(d2));
  assert(size(d2) == 7);

  printf("\nUpdated deque\n");
  traverse(d2, print_person);

  printf("\nThis is the deque after removing people who are 22\n");
  assert(remove_if(d2, is_age_22, free_person) == 3);
  traverse(d2, print_person);

  printf("\nThis is the deque after removing people who are 40 (should not change)\n");
  assert(remove_if(d2, is_age_40, free_person) == 0);
  traverse(d2, print_person);

  printf("\nEmptying the dequqe\n");
  empty_deque(d2, free_person);
  traverse(d2, print_person);
  assert(size(d2)==0);
  printf("Success emptied the deque\n");

  printf("\nAdding 3 elements to the deque:\n");
  push_front(d2, create_person("Jimmy", 21));
  // push_back(d2, create_person("Mallory", 22));
  // push_back(d2, create_person("Pooja", 18));
  printf("Size: %d\n", size(d2));
  assert(size(d2) == 1);

  printf("The current deque\n");
  traverse(d2, print_person);

  //printf("\nCopying the deque\n");

  // printf("\nIntiate new deque\n");
  // deque *d3 = copy_deque(d2, copy_person);
  // traverse(d3, print_person);

  // printf("Size: %d\n", size(d3));
  // assert(size(d3) == 0);
  // assert(!d3->head);
  // assert(!d3->tail);
  // assert(is_empty(d3));

  //assert(size(copy_deque(d2, copy_person)) == 1);


  printf("\nEmptying the dequqe\n");
  empty_deque(d2, free_person);
  traverse(d2, print_person);
  assert(size(d2)==0);
  printf("Success emptied the deque\n");

  // printf("\nEmptying the copied dequqe\n");
  // empty_deque(d3, free_person);
  // traverse(d3, print_person);
  // assert(size(d3)==0);
  // printf("Success emptied the copied deque\n");

  free_person(evan);
  free_person(zach);
  //free_person(jimmy);
  free(d2);
  //free(d3);

  printf("\nPassed All tests\n");

  return 0;
}
