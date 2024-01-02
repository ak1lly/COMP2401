#include "defs.h"

/* 
  Purpose:  initializes escape, including seeding PRNG, initializing the hero and flyer arrays,
            allocating and initializing both heroes and adding them to the heroes array, 
            initializing sockets and blocking until client connection request is received
       in:  escape
      out:  initalized escape
*/
void initEscape(EscapeType* e){
    srand(time(NULL));    
    e->heroes.size = 0;
    (&e->heroes)->elements = malloc(sizeof(HeroType*));
    
    HeroType h, t;
    HeroType* ptrH;
    HeroType* ptrT;
    ptrH = &h;
    ptrT = &t;
    int hPos = 0;
    int tPos = 0;

    while(hPos==tPos){
        hPos = randomInt(4);
        tPos = randomInt(4);
    }

    initHero(&ptrH, 'H', hPos, "Harold");
    initHero(&ptrT, 'T', tPos, "Timmy");

    addHero(&e->heroes, ptrH);
    addHero(&e->heroes, ptrT);

    e->flyers.size = 0;
}

/* 
  Purpose:  cleans up escape, including deallocating required memory, sending termination
            (quit) message to client, and closing sockets
       in:  escape
*/
void cleanupEscape(EscapeType* e){
    for(int i=0; i<e->heroes.size; i++){
        free(e->heroes.elements[i]);
    }
    free(e->heroes.elements);
    for(int i=0; i<e->flyers.size; i++){
        free(e->flyers.elements[i]);
    }
}

/* 
  Purpose:  determines if both heroes are dead or have escaped
       in:  escape
   return:  truth value
*/
int escapeIsOver(EscapeType* e){
    int count = 0;

    for(int i=0; i<e->heroes.size; i++){
        if(e->heroes.elements[i]->partInfo.avatar == '+' || heroIsSafe(e->heroes.elements[i]) == C_TRUE){
            count++;
        }
    }

    if(count == e->heroes.size){
        return C_TRUE;
    }else{
        return C_FALSE;
    }
}

/* 
  Purpose:  prints out and sends to client the outcome of the escape
       in:  escape type
      out:  escape result
*/
void handleEscapeResult(EscapeType* e){
    char hRes[MAX_BUFF];
    char tRes[MAX_BUFF];
    for(int i=0; i<e->heroes.size; i++){
        if(heroIsSafe(e->heroes.elements[i]) == C_TRUE){
            if(e->heroes.elements[i]->partInfo.avatar == 'H'){
                strcpy(hRes, "\nHAROLD ESCAPED !!!");
            }else{
                strcpy(tRes, "\nTIMMY ESCAPED !!!\n");                
            }
        }else{
            if(strcmp(e->heroes.elements[i]->name, "Harold") == 0){
                strcpy(hRes, "\nHAROLD IS DEAD ... ");
            }else{
                strcpy(tRes, "\nTIMMY IS DEAD ... \n");
            }
        }
    }

    char result[MAX_BUFF];
    strcpy(result, hRes);
    strcat(result, tRes);
    sendData(e->viewSocket, result);
    printf("%s", result);
}
