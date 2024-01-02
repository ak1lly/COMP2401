#include "defs.h"

/*
  Purpose:  dynamically allocates and initializes one flyer, and 
            adds it to escape's flyer collection 
       in:  escape type, avatar, row, col, strength
      out:  updated flyer array
*/
void spawnFlyer(EscapeType* e, char a, int r, int c, int s){
    if(e->flyers.size+1<MAX_ARR){
        FlyerType* tempFly;
        tempFly = malloc(sizeof(FlyerType));

        tempFly->partInfo.pos.row=r;
        tempFly->partInfo.pos.col=c;

        tempFly->partInfo.avatar=a;

        tempFly->strength=s;

        addFlyer(&e->flyers, tempFly);
    }
}

/*
  Purpose:  adds flyer to escape's flyer collection
       in:  flyer type
      out:  updated array
*/
void addFlyer(FlyerArrayType* arr, FlyerType* f){
    if(arr->size<MAX_ARR){
        arr->elements[arr->size] = f;
        arr->size++;
    }
}

/*
  Purpose:  computes flyer's next move in accordance to instruction 3.4, 
            updates flyer's position, and deals with collisions with heroes
       in:  flyer type, escape type
      out:  updated flyer type
*/
void moveFlyer(FlyerType* f, EscapeType* e){
    int row = f->partInfo.pos.row;
    int col = f->partInfo.pos.col;
    if(f->partInfo.avatar == '@'){
        int vertRoll=randomInt(2);
        int distRoll=randomInt(3)+1;

        if(vertRoll==0){
            vertRoll=distRoll;
        }else{
            vertRoll=-(distRoll);
        }

        int heroDir = 0;
        computeHeroDir(e, f, &heroDir);
        int horiRoll = heroDir*distRoll;

        
        setPos(&f->partInfo.pos, row+vertRoll, col+horiRoll);
    }

    if(f->partInfo.avatar == 'v'){
        int colRoll = randomInt(3);


        if(colRoll==0){
            setPos(&f->partInfo.pos, row+1, col+1);
        }else if(colRoll == 1){
            setPos(&f->partInfo.pos, row+1, col-1);
        }else{
            setPos(&f->partInfo.pos, row+1, col);
        }
    }
}

/*
  Purpose:  determines if a flyer has reached the ground
       in:  flyer type
      out:  truth value
*/
int  flyerIsDone(FlyerType* f){
    if(f->partInfo.pos.row>=MAX_ROW-1){
        return C_TRUE;
    }
    return C_FALSE;
}