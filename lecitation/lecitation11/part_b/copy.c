/**********************************************************
 * Lecitation 11 (Part B): Shallow vs. Deep Copy
 * copy.c
 * 
 * Author: 
 * Semester: Summer 2018
 *********************************************************/

#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define COUNT 30

struct position_t {
  int x;
  int y;
};

struct person_t {
  int age;
  char *name;
};

void scale_by_2(struct position_t p) {
  p.x *= 2;
  p.y *= 2;
}

struct person_t copy_person(struct person_t orig) {
  struct person_t new;
  new.age = orig.age;
  new.name = orig.name;
  return new;
}

int main() {
  
  int nums[COUNT];

  // @todo: There is something wrong with this loop. Set the values of nums
  // to [0, ..., COUNT - 1] without using the symbol COUNT

  for(unsigned int i = 0; i < sizeof(nums); ++i) {
    nums[i] = i;
  }

  printf("--------------------------------\n");
  printf("Values in nums:\n");
  for(int i = 0; i < COUNT; ++i) {
    printf("%d ", nums[i]);
  }
  printf("\n");
  printf("--------------------------------\n");

  struct position_t pos;
  pos.x = 40;
  pos.y = 35;

  printf("--------------------------------\n");
  printf("Position values: (%d, %d)\n", pos.x, pos.y);

  // @todo: Fix the scale_by_2 function so that it scales the position of the
  // struct passed into it, by 2. You may not change the struct definition on
  // lines 11 - 14, but you may change anything in that function and this call

  scale_by_2(pos);

  printf("Scaled by 2 now: (%d, %d)\n", pos.x, pos.y);
  printf("--------------------------------\n");

  printf("--------------------------------\n");
  const char *name = "Hello";

  // This creates a buffer for us to hold "Hello"
  char *buf = malloc(strlen(name) + 1);
  strcpy(buf, name);
  struct person_t p1;
  p1.age = 26;
  p1.name = buf;

  struct person_t p2 = copy_person(p1);

  printf("Person 1: (%d, %s)\n", p1.age, p1.name);
  printf("Person 2: (%d, %s)\n", p2.age, p2.name);
  printf("Now, let's modify the age and name of Person 1...\n");

  p1.age = 30;
  p1.name[0] = 'J';

  // @todo: Fix the copy_person function so that person 1 and person 2 will
  // have different names if you change the name for only 1 of them

  printf("Person 1: (%d, %s)\n", p1.age, p1.name);
  printf("Person 2: (%d, %s)\n", p2.age, p2.name);

  printf("--------------------------------\n");

  // Assertions to verify your solution. Do not modify!
  FILE *p = popen("grep lab21.c -e COUNT -c", "r");
  char buf2[500];
  fgets(buf2, 500, p);
  fclose(p);
  assert(atoi(buf2) == 6); /* Did not use COUNT symbol in part 1 */
  assert(pos.x == 80 && pos.y == 70);
  assert(strcmp(p1.name, p2.name)); /* Fails if names are the same */
  printf("Passed the tests!\n");

  free(p1.name);
}

