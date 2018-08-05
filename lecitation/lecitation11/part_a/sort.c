/**********************************************************
 * Lecitation 11 (Part A): Function Pointers
 * sort.c
 * 
 * Author: 
 * Semester: Summer 2018
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int verify_age_sort(void);
int verify_name_sort(void);
int verify_length_sort(void);
void shuffle(void);

typedef struct {
  int age;
  const char *name;
} Person;

#define NUMPEOPLE 10
Person people[NUMPEOPLE] = {
  {32, "Jonathan"},
  {51, "Amelia"  },
  {22, "Marcus"  },
  {25, "Ashley"  },
  {37, "Xavier"  },
  {73, "Ellen"   },
  {26, "Ricardo" },
  {40, "Tanaka"  },
  {68, "Mitchell"},
  {19, "Roy"     }
};

// @todo write any additional functions you may need here
// We even gave you the beginning of one to start!

// Sorts by age
int sort_by_age(const void *data1, const void *data2) {
  Person *p1 = (Person*) data1;
  Person *p2 = (Person*) data2;

  int age1 = p1->age;
  int age2 = p2->age;

  if (age1 > age2) {
    return 1;
  } else if (age1 < age2) {
    return -1;
  } else {
    return 0;
  }
}

int main(void) {
  srand(time(NULL));
  shuffle();

  // @todo Use qsort to sort people by age in ascending order

  // Print people sorted by age
  printf("---[Age sort]----------------------------\n");
  for(int i = 0; i < NUMPEOPLE; ++i) {
    printf("\t%-10s %-2d\n", people[i].name, people[i].age);
  }
  assert(verify_age_sort());
  shuffle();

  // @todo Use qsort to sort people by name

  // Print people sorted by name
  printf("---[Name alphabetical sort]--------------\n");
  for(int i = 0; i < NUMPEOPLE; ++i) {
    printf("\t%-10s %-2d\n", people[i].name, people[i].age);
  }
  assert(verify_name_sort());
  shuffle();

  // @todo Use qsort to sort people by the length of their name, ascending
  // If two names are the same length, alphabetically sort the two

  // Print people sorted by name length
  printf("---[Name length sort]--------------------\n");
  for(int i = 0; i < NUMPEOPLE; ++i) {
    printf("\t%-10s %-2d\n", people[i].name, people[i].age);
  }
  assert(verify_length_sort());

  printf("Passed the tests!\n");
  return 0;
}

// Verification functions: DO NOT MODIFY!

int verify_age_sort(void) {
  for (int i = 1; i < NUMPEOPLE; ++i) {
    if (people[i - 1].age > people[i].age) {
      return 0;
    }
  }
  return 1;
}

int verify_name_sort(void) {
  for (int i = 1; i < NUMPEOPLE; ++i) {
    if (strcmp(people[i - 1].name, people[i].name) > 0) {
      return 0;
    }
  }
  return 1;
}

int verify_length_sort(void) {
  for (int i = 1; i < NUMPEOPLE; ++i) {
    int diff = strlen(people[i - 1].name) - strlen(people[i].name);
    if (diff > 0) {
      return 0;
    } else if (!diff) {
      if (strcmp(people[i - 1].name, people[i].name) > 0) {
        return 0;
      }
    }
  }
  return 1;
}

void shuffle(void) {
  for (int i = NUMPEOPLE - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    Person temp;
    memcpy(&temp, people + i, sizeof(Person));
    memcpy(people + i, people + j, sizeof(Person));
    memcpy(people + j, &temp, sizeof(Person));
  }
}
