#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  Function:  initRestaurant
  Purpose:   function that initializes the three fields of the given restaurant structure
       in:   name
      out:   initialized restaurant
   return:   void
*/
void initRestaurant(RestaurantType* r, char* n){
    strcpy(r->name, n);
    initResvList(&(r->reservations));
    initPatronArray(&(r->patrons));
}

/*
  Function:  createResv
  Purpose:   function that creates a new reservation and adds it to the given restaurant
       in:   patron ID, year, month, day hour, min
      out:   updated restaurant
   return:   void
*/
void createResv(RestaurantType* r, int pId, int yr, int mth, int day, int hr, int min){
    int validDate = validateResvTime(yr, mth, day, hr, min);

    PatronType p;
    PatronType* pPtr = &p;
    int validId = findPatron(&r->patrons, pId, &pPtr);

    if(validDate==C_NOK || validId==C_NOK){
        if(validDate==C_NOK){printf("ERROR: Date %d-%02d-%02d @ %02d:%02d is invalid\n", yr, mth, day, hr, min);}
        if(validId==C_NOK){printf("ERROR: Patron ID %d is not found\n", pId);}
    }else{
        ResvTimeType rt;
        ResvTimeType* rtPtr = &rt;
        initResvTime(&rtPtr, yr, mth, day, hr, min);

        ResvType resv;
        ResvType* rPtr = &resv;
        initResv(&rPtr, pPtr, rtPtr);

        addResv(&r->reservations, rPtr);
    }
}

/*
  Function:  findResByPatron
  Purpose:   function that prints out the details of every reservation made by the patron with the given id
       in:   restaurant, id
   return:   all resv under given id
*/
void printResByPatron(RestaurantType* r, int id){
    NodeType* curNode = (&r->reservations)->head;
    NodeType* nextNode;
    printf("\nRESERVATIONS BY PATRON ID %d at %s:\n", id, r->name);
    while (curNode != NULL) {
        nextNode = curNode->next;

        if(curNode->data->patron->id == id){
            printReservation(curNode->data);
        }

        curNode = nextNode;
    }
}

/*
  Function:  cleanupRestaurant
  Purpose:   function that cleans up all the dynamically allocated memory for the given restaurant
       in:   restaurant
   return:   void
*/
void cleanupRestaurant(RestaurantType* r){
    cleanupResvList(&r->reservations);
    cleanupPatronArray(&r->patrons);
}

/*
  Function:  validateResvTime
  Purpose:   function that checks that the parameters represent a valid date and time
       in:   year, month, day hour, min
   return:   flag
*/
int validateResvTime(int yr, int mth, int day, int hr, int min){
    if(yr<2023 || mth<1 || mth>12 || day<1 || day>31 || hr<0 || hr>23 || min<0 || min>59){
        return C_NOK;
    }
    return C_OK;
}
