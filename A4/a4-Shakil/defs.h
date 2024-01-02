#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C_OK            0
#define C_NOK          -1
#define C_TRUE          1
#define C_FALSE         0

#define MAX_STR        64
#define MAX_CAP       128

#define PATRON_IDS   1001
#define RES_IDS      4001

typedef struct {
  int   id;
  char  name[MAX_STR];
} PatronType;

typedef struct {
  int day;
  int month;
  int year;
  int hours;
  int minutes;
} ResvTimeType;

typedef struct {
  int           id;
  PatronType   *patron;
  ResvTimeType *resvTime;
} ResvType;

typedef struct{
  PatronType *elements;
  int size;
  int nextId;
}PatronArrayType;

typedef struct Node{
  struct Node* next;
  struct Node* prev;
  ResvType* data;
}NodeType;

typedef struct{
  NodeType* head;
  int nextId;
}ResvListType;

typedef struct{
  char name[MAX_STR];
  ResvListType reservations;
  PatronArrayType patrons;
}RestaurantType; 

void initRestaurant(RestaurantType*, char*);
void createResv(RestaurantType*, int, int, int, int, int, int);
void printResByPatron(RestaurantType*, int);
void cleanupRestaurant(RestaurantType*);
int validateResvTime(int, int, int, int, int);

void initResvList(ResvListType*);
void initResv(ResvType **, PatronType *, ResvTimeType *);
void initResvTime(ResvTimeType **, int, int, int, int, int);
void addResv(ResvListType *, ResvType *);
int lessThan(ResvTimeType *, ResvTimeType *);
void printReservation(ResvType *);
void printReservations(ResvListType *);
void cleanupResvList(ResvListType *);

void initPatronArray(PatronArrayType *);
void addPatron(PatronArrayType *, char *);
int findPatron(PatronArrayType *, int, PatronType **);
void printPatrons(PatronArrayType *);
void cleanupPatronArray(PatronArrayType * );

void printMenu(int*);
void loadPatronData(RestaurantType*);
void loadResData(RestaurantType*);

