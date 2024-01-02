#include <stdio.h>
#include <string.h>
#include "defs.h"

int main()
{
  RestaurantType r;
  RestaurantType* rPtr = &r;
  initRestaurant(rPtr, "Shakil's Restaurant");
  loadPatronData(rPtr);
  loadResData(rPtr);

  int choice = -1;

  while(choice != 0){
    printMenu(&choice);
    if(choice == 1){
      printf("\nPATRONS OF %s:\n", rPtr->name);
      printPatrons(&rPtr->patrons);
    }else if(choice == 2){
      printf("\nRESERVATIONS AT %s:\n", rPtr->name);
      printReservations(&rPtr->reservations);
    }else if(choice == 3){
      int pId;
      printf("Enter patron ID: ");
      scanf("%d", &pId);
      PatronType* p;
      if(findPatron(&rPtr->patrons, pId, &p)==C_NOK){
        printf("\nERROR: Patron ID %d is not found\n", pId);
      }else{
        printResByPatron(rPtr, pId);
      }
    }
  }  

  cleanupRestaurant(rPtr);

  return(0);
}

/*
  Function:  printMenu
  Purpose:   prints menu
   in-out:   choice
   return:   void
*/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print patrons\n");
  printf("  (2) Print reservations\n");
  printf("  (3) Print reservations by patron\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

