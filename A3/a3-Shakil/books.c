#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define C_OK       0
#define C_NOK     -1

#define MAX_STR   64
#define MAX_CAP  128
/*
  Function:  initBooks
  Purpose:   function that initializes every field of the given BookType structure, using the values 
  found in the given parameters.
       in:   id, title, author, year, rating
      out:   initialized book
   return:   void
*/
void initBook(BookType* b, int idn, char* t, char* a, int y, float r){
    b -> id = idn;
    strcpy(b -> title, t);
    strcpy(b -> author, a);
    b -> year = y;
    b -> rating = r;
}

/*
  Function:  initBookArray
  Purpose:   function that initializes every field of the given BookArrayType structure, using the values 
  found in the given parameters.
       in:   order type
      out:   initialized book array
   return:   void
*/
void initBookArray(BookArrayType* arr, OrderType o){
    arr -> size = 0;
    arr -> order = o;

    for (int i = 0; i < MAX_CAP; i++) {
        arr->elements[i] = NULL;
    }
}
/*
  Function:  addBookToArray
  Purpose:   function that stores the given book directly into its correct position in the given book collection.
       in:   book
   in-out:   updated array
   return:   result flag
*/
int  addBookToArray(BookArrayType* arr, BookType* b){
    int insPt = 0;

    if(findInsPt(arr, b, &insPt) == C_NOK){
        return C_NOK;
    }

    
    for(int i=arr->size; i > insPt; i--){
        arr->elements[i] = arr->elements[i-1];
    }

    arr->size++;
    arr->elements[insPt] = b;

    return C_OK;
}

/*
  Function:  findInsPt
  Purpose:   function that searches an array to find the index where a new book should be inserted
       in:   array, book
      out:   insPt
   return:   result flag
*/
int findInsPt(BookArrayType* arr, BookType* b, int* insPt){
    if (arr->size >= MAX_CAP){
        return C_NOK;
    }
   

    if(arr->order == ORDER_BY_AUTHOR){
        int comp = 0;

        for (int i = 0; i < arr->size; i++) {
            comp = strcmp((b->author),(arr->elements[i]->author));

            if(comp > 0){
                (*insPt)++;
            }else if(comp == 0){
                if(strcmp((b->title),(arr->elements[i]->title)) > 0){
                    (*insPt)++;
                }
            }else{
                break;
            }

        }
        return C_OK;
    } else if (arr->order == ORDER_BY_RATING){
        for (int i = 0; i < arr->size; i++) {
            if (b->rating < arr->elements[i]->rating) {
                (*insPt)++;
            } else {
                break;
            }
        }
        return C_OK;
    }
    return C_NOK;
}


/*
  Function:  printBook
  Purpose:   prints 1 book
       in:   book
   return:   void
*/
void printBook(const BookType* b){
    printf("%-5d: %-40s: %-30s: %-5d: %-5.2f\n", b->id, b->title, b->author, b->year, b->rating);
}

/*
  Function:  printBookArray
  Purpose:   prints array of books
       in:   book array
   return:   void
*/
void printBookArray(BookArrayType* arr){
    for (int i = 0; i<arr->size; i++){
        printBook(arr->elements[i]);
    }
}

/*
  Function:  cleanUpBookArray
  Purpose:   deallocates memory from book array
       in:   book array
   return:   void
*/
void cleanupBookArray(BookArrayType* arr){
    for (int i = 0; i<arr->size; i++){
        free(arr->elements[i]);
    }
}