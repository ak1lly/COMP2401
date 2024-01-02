#include <stdio.h>
#include <string.h>
#include "defs.h"

#define MAX_STR   64


int main()
{
  BookClubType club;
  BookClubType* clubPtr = &club;
  initBookClub(clubPtr, "Shakil's Book Club");

  loadBookData(clubPtr);

  int choice = -1;

  while (choice != 0){
    printMenu(&choice);
    if(choice == 1){
      printBooks(clubPtr);
    }else if(choice == 2){
      printTopRatedBooks(clubPtr);
    }else if(choice == 3){
      int id, year;
      char title[MAX_STR], authorF[MAX_STR], authorL[MAX_STR];
      float rating;

      printf("\nEnter book ID: ");
      scanf("%d", &id);
      printf("Enter book title: ");
      while (getchar() != '\n');
      scanf("%[^\n]", title);
      printf("Enter author first and last name: ");
      scanf("%s %s", authorF, authorL);
      printf("Enter publication year: ");
      scanf("%d", &year);
      printf("Enter rating: ");
      scanf("%f", &rating);

      if(addBookToClub(clubPtr, id, title, authorF, authorL, year, rating)==C_NOK){
        printf("\nERROR: Book could not be added");
      }else{
        printf("\nBook successfully added!");
      }
    }
  }

  cleanupBookArray(&clubPtr->byAuthor);
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
  printf("  (1) Print all books\n");
  printf("  (2) Print top rated books\n");
  printf("  (3) Add a book\n");
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

