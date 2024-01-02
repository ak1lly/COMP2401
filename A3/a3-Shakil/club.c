#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initBookClub(BookClubType* club, char* n){
    strcpy(club->name, n);

    OrderType author = ORDER_BY_AUTHOR;
    OrderType rating = ORDER_BY_RATING;

    initBookArray(&club->byAuthor, author);
    initBookArray(&club->byRating, rating);
}
/*
  Function:  addBookToClub
  Purpose:    function that takes as parameters a new book id, title, author's first name, 
  author's last name, year of publication, and rating. The function then creates a new book and 
  adds it to the given book club's collection.
       in:   id, title, author, year, rating
      out:   updated book club
   return:   result flag
*/
int  addBookToClub(BookClubType* club, int id, char* t, char* af, char* al, int y, float r){
    if(t == NULL || af == NULL || al == NULL || id<0 || y<0 || r<0 || r>5){
        return C_NOK;
    }

    char fullAuthor[MAX_STR];
    sprintf(fullAuthor, "%s, %s", al, af);

    BookType b;
    BookType* ptr = &b;

    ptr = malloc(sizeof(BookType));

    initBook(ptr, id, t, fullAuthor, y, r);

    addBookToArray(&club->byAuthor, ptr);
    addBookToArray(&club->byRating, ptr);

    return C_OK;
}

/*
  Function:  printBooks
  Purpose:   prints book
       in:   book club
   return:   void
*/
void printBooks(BookClubType* club){
    printf("Books for %s: \n", club->name);
    printBookArray(&club->byAuthor);
} 


/*
  Function:  printBooks
  Purpose:   prints top 20% of books by rating
       in:   book club
   return:   void
*/
void printTopRatedBooks(BookClubType* club){
    BookArrayType topRated;
    OrderType o = ORDER_BY_RATING;
    initBookArray(&topRated, o);

    int topSize = ((&club->byRating) -> size) * 0.2;

    for(int i = 0; i < topSize; i++){
        BookType* cur = (&club->byRating) -> elements[i];
        addBookToArray(&topRated, cur);
    }
    printf("\nTop Rated Books for %s:\n", club->name);
    printBookArray(&topRated);
}
