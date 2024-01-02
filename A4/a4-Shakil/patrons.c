#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  Function:  initPatronArray
  Purpose:   function that initializes every field of the given patron collection to default values
       in:   array
   return:   void
*/
void initPatronArray(PatronArrayType* arr){
    arr->elements = calloc(MAX_CAP, sizeof(PatronType));
    arr->size=0;
    arr->nextId=PATRON_IDS;
}

/*
  Function:  addPatron
  Purpose:   function that adds a new patron to the back of the given patron collection
       in:   array, name
   return:   void
*/
void addPatron(PatronArrayType* arr, char* name){
    PatronType newPat;
    PatronType* ptr = &newPat;
    strcpy(ptr->name,name);
    ptr->id = arr->nextId;

    arr->elements[arr->size]=newPat;
    arr->size++;
    arr->nextId++;
}

/*
  Function:  findPatron
  Purpose:   function that searches through the given patron collection to find the 
  patron with the given id
       in:   array, patron ID
      out:   patron
   return:   flag
*/
int findPatron(PatronArrayType* arr, int id, PatronType** p){
    for(int i=0; i<arr->size; i++){
        PatronType* cur = &(arr->elements[i]);
        if(cur->id == id){
            *p = cur;
            return C_OK;
        }
    }
    return C_NOK;
}

/*
  Function:  printPatrons
  Purpose:   function that prints out to the screen all the details of every 
  patron in the given patron collection.
       in:   array
   return:   void
*/
void printPatrons(PatronArrayType* arr){
    for(int i=0; i<arr->size; i++){
        PatronType* cur = &(arr->elements[i]);
        printf("Patron #%d %s\n", cur->id, cur->name);
    }
}

/*
  Function:  cleanupPatronArray
  Purpose:   function that deallocates all the required dynamically allocated 
  memory for the given patron collection
       in:   array
   return:   void
*/
void cleanupPatronArray(PatronArrayType *arr){
    free(arr->elements);
}