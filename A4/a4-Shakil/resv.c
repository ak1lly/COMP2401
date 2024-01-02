#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  Function:  initResvList
  Purpose:   function that initializes both fields of the given list parameter to default values
      out:   initialized ResvList
   return:   void
*/
void initResvList(ResvListType* list){
    list->head = NULL;
    list->nextId = RES_IDS;
}

/*
  Function:  initResv
  Purpose:   function that dynamically allocates memory for a ResvType structure
       in:   patron, resvtime
      out:   initialized Resv
   return:   void
*/
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt){
    ResvType* tempR;

    tempR = malloc(sizeof(ResvType));
    tempR->patron = p;
    tempR->resvTime = rt;

    *r=tempR;
}

/*
  Function:  initResvTime
  Purpose:   function that dynamically allocates memory for a ResvTimeType structure, initializes 
  its fields to the given parameters
       in:   year, month, day hour, min
      out:   initialized ResvTime
   return:   void
*/
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min){
    ResvTimeType* tempRt;

    tempRt = malloc(sizeof(ResvTimeType));
    tempRt->day=day;
    tempRt->month=mth;
    tempRt->year=yr;
    tempRt->hours=hr;
    tempRt->minutes=min;

    *rt=tempRt;
}

/*
  Function:  addResv
  Purpose:   function that adds the reservation r in its correct position in the given list
       in:   resv
      out:   updated list
   return:   void
*/
void addResv(ResvListType* list, ResvType* r){
    NodeType* newNode;
    NodeType* curNode;
    NodeType* prevNode;

    newNode = malloc(sizeof(NodeType));
    newNode->data = r;
    newNode->next = NULL;
    newNode->prev = NULL;

    curNode = list->head;
    prevNode = NULL;

    while(curNode != NULL){
        if(lessThan(newNode->data->resvTime, curNode->data->resvTime) == C_TRUE){
            break;}
        prevNode= curNode;
        curNode = curNode->next;
    }

    if(prevNode==NULL){
        list->head = newNode;
    }else{
        prevNode->next = newNode;
        newNode->prev  = prevNode;
    }

    newNode->next  = curNode;
    newNode->data->id = list->nextId;
    list->nextId++;

    if (curNode != NULL) {
        curNode->prev = newNode;
    }
}

/*
  Function:  lessThan
  Purpose:   function that compares two reservation times
       in:   r1, r2
   return:   truth flag
*/
int lessThan(ResvTimeType* r1, ResvTimeType* r2){
    if (r1->year < r2->year) {
        return C_TRUE;
    } else if (r1->year > r2->year) {
        return C_FALSE;
    }

    if (r1->month < r2->month) {
        return C_TRUE;
    } else if (r1->month > r2->month) {
        return C_FALSE;
    }

    if (r1->day < r2->day) {
        return C_TRUE;
    } else if (r1->day > r2->day) {
        return C_FALSE;
    }

    if (r1->hours < r2->hours) {
        return C_TRUE;
    } else if (r1->hours > r2->hours) {
        return C_FALSE;
    }

    if (r1->minutes < r2->minutes) {
        return C_TRUE;
    } else if (r1->minutes > r2->minutes) {
        return C_FALSE;
    }

    return C_FALSE;
}

/*
  Function:  printReservation
  Purpose:   function that prints out all the details of the given reservation
       in:   resv
   return:   void
*/
void printReservation(ResvType* r){
    printf("%04d :: %d-%02d-%02d @ %02d:%02d :: %s\n", r->id, r->resvTime->year, r->resvTime->month, 
        r->resvTime->day, r->resvTime->hours, r->resvTime->minutes, r->patron->name);
}

/*
  Function:  printReservations
  Purpose:   function that prints out the details of every reservation in the given list.
       in:   list
   return:   void
*/
void printReservations(ResvListType* list){
    NodeType *curNode = list->head;
    NodeType *prevNode = NULL;

    printf("->FORWARD:\n");
    while (curNode != NULL) {
        printReservation(curNode->data);
        prevNode = curNode;
        curNode = curNode->next;
    }

    printf("->BACKWARD:\n");
    curNode = prevNode;

    while (curNode != NULL) {
        printReservation(curNode->data);
        curNode = curNode->prev;
    }
}

/*
  Function:  cleanupResvList
  Purpose:   function that deallocates all the required dynamically allocated memory for the given list
       in:   list
   return:   void
*/
void cleanupResvList(ResvListType* list){
    NodeType* curNode = list->head;
    NodeType* nextNode;

    while (curNode != NULL) {
        nextNode = curNode->next;

        free(curNode->data->resvTime);
        free(curNode->data);
        free(curNode);

        curNode = nextNode;
    }
}