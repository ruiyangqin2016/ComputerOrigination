#include <stdlib.h>
#include <stdio.h>

#define MENU_STOP_CODE 5

// Data structures
typedef struct carType Car;

struct carType {
  int vehicleID;	// Unique identifier for a car
  char make[20];	// Manufacturer
  char model[20];	// Model name
  int year;		// Year of manufacture
  int mileage;		// in miles
  double cost;		// in dollars

  Car *next;		// Points to a car_node
};

// Prototypes
Car *ScanList(Car *headPointer, int searchID);
void AddEntry(Car *headPointer);
void DeleteEntry(Car *headPointer);
void Search(Car *headPointer);
void DisplayBase(Car *headPointer);

// Main and supporting functions
int main() {
  int op = 0;  /* Current operation to be perform.        */
  Car carBase; /* carBase an empty head node              */

  carBase.next = NULL;   /* Initialize the list to empty  */

  printf("=========================\n");
  printf("=== Used car database ===\n");
  printf("=========================\n\n");

  while (op != MENU_STOP_CODE) {
    printf("Enter an operation:\n");
    printf("1 - Car acquired. Add a new entry for it.\n");
    printf("2 - Car sold. Remove its entry.\n");
    printf("3 - Query. Look up a car's information.\n");
    printf("4 - Inspect. Display the database contents and structure.\n");
    printf("5 - Quit.\n");
    scanf("%d", &op);

    if (op == 1) 
         AddEntry(&carBase);
    else if (op == 2) 
         DeleteEntry(&carBase);
    else if (op == 3)
         Search(&carBase);
    else if (op == 4)
         DisplayBase(&carBase);
    else if (op == 5)
         printf("Good bye.\n\n");
    else 
         printf("Invalid option.  Try again.\n\n");
  }
}

Car *ScanList(Car *headPointer, int searchID) {
  Car *previous;
  Car *current;

  /* Point to start of list */
  previous = headPointer;
  current = headPointer->next;

  /* Traverse list -- scan until we find a node with a    */
  /* vehicleID greater than or equal to searchID          */
  while ((current != NULL) && 
         (current->vehicleID < searchID)) {
    previous = current;
    current  = current->next;
  }

  /* The variable previous points to node prior to the    */
  /* node being searched for. Either current->vehicleID   */  
  /* equals searchID or the node does not exist.          */
  return previous;
}

void AddEntry(Car *headPointer) {
  Car *newNode;       /* Points to the new car info       */
  Car *nextNode;      /* Points to car to follow new one  */
  Car *prevNode;      /* Points to car before this one    */
  
  /* Dynamically allocate memory for this new entry.      */
  newNode = (Car *) malloc(sizeof(Car));

  if (newNode == NULL) {
     printf("Error: could not allocate a new node\n");
     exit(1);
  }

  printf("Enter the following info about the car.\n");
  printf("Separate each field by whitespace:\n");
  printf("vehicle_id make model year mileage cost\n");

  scanf("%d %s %s %d %d %lf", 
        &newNode->vehicleID, newNode->make, newNode->model,
        &newNode->year, &newNode->mileage, &newNode->cost);

  prevNode = ScanList(headPointer, newNode->vehicleID);
  nextNode = prevNode->next;

  if ((nextNode == NULL) || 
      (nextNode->vehicleID != newNode->vehicleID)) {
    prevNode->next = newNode;
    newNode->next = nextNode;
    printf("Entry added.\n\n");
  }
  else {
    printf("That car already exists in the Database!\n");
    printf("Entry not added.\n\n");
    free(newNode);
  }
}

void DeleteEntry(Car *headPointer) {
  int vehicleID;
  Car *delNode;       /* Points to node to delete         */
  Car *prevNode;      /* Points to node prior to delNode  */

  printf("Enter the vehicle ID of the car to delete:\n");
  scanf("%d", &vehicleID);

  prevNode = ScanList(headPointer, vehicleID);
  delNode  = prevNode->next;

  /* Either there is the car does not exist or            */  
  /* delNode points to the car to be deleted.             */
  if (delNode != NULL && delNode->vehicleID == vehicleID) {
    prevNode->next = delNode->next;
    printf("Vehicle with id %d deleted.\n\n", vehicleID);    
    free(delNode);
  }
  else 
    printf("The vehicle was not found in the database.\n");
}

void Search(Car *headPointer) {
  int vehicleID;
  Car *searchNode;    /* Points to node to delete to follow */
  Car *prevNode;      /* Points to car before one to delete */

  printf("Enter the vehicle ID number of the car to search for:\n");
  scanf("%d", &vehicleID);

  prevNode = ScanList(headPointer, vehicleID);
  searchNode  = prevNode->next;

  /* Either there is the car does not exist in the list or      */  
  /* searchNode points to the car we are looking for.           */
  if (searchNode != NULL && searchNode->vehicleID == vehicleID) {
    printf("vehicle ID : %d\n", searchNode->vehicleID);
    printf("make       : %s\n", searchNode->make);
    printf("model      : %s\n", searchNode->model);
    printf("year       : %d\n", searchNode->year);
    printf("mileage    : %d\n", searchNode->mileage);

    /* The following printf has a field width specification on  */
    /* %f specification.  The 10.2 indicates that the floating  */
    /* point number should be printed in a 10 character field   */
    /* with two units after the decimal displayed.              */
    printf("cost       : $%10.2f\n\n", searchNode->cost);
  }
  else {
    printf("The vehicle id %d was not found in the database.\n\n", 
           vehicleID);
  }
}

void DisplayBase(Car *headPointer) {
  Car *displayNode;

  // Point to start of list
  displayNode = headPointer->next;

  // Traverse the list and display the contents and links for each node
  while (displayNode != NULL) {
    printf("%p | %d, %s, %s, %d, %d, %10.2f | --> %p\n", displayNode, displayNode->vehicleID,
displayNode->make, displayNode->model, displayNode->year, displayNode->mileage,
displayNode->cost, displayNode->next);
    displayNode = displayNode->next;
  }

  printf("\n");
}

