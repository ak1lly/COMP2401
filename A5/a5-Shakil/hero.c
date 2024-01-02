#include "defs.h"

/*
  Purpose:  dynamically allocates and initializes one hero 
       in:  hero type, avatar, position, name
      out:  updated hero 
*/
void initHero(HeroType** h, char a, int p, char* n){
    HeroType* tempHero;
    
    tempHero = malloc(sizeof(HeroType));
    
    tempHero->partInfo.pos.col=p;
    tempHero->partInfo.pos.row=MAX_ROW-1;

    tempHero->partInfo.avatar=a;

    strcpy(tempHero->name,n);
    tempHero->health=MAX_HEALTH;
    tempHero->dead=C_FALSE;
    
    *h = tempHero;
}

/*
  Purpose:  adds hero to escape's hero collection 
       in:  hero array, hero type
      out:  updated hero array 
*/
void addHero(HeroArrayType* arr, HeroType* h){
    arr->elements = realloc(arr->elements, (arr->size+1)*sizeof(HeroType*));
    arr->elements[arr->size] = h;
    arr->size++;
}

/*
  Purpose:  determines if a hero has successfully escaped the Hollow 
       in:  hero type
      out:  truth value
*/
int heroIsSafe(HeroType* h){
    if(h->partInfo.pos.col==-1 && h->health>0){
        return C_TRUE;
    }else{
        return C_FALSE;
    }
}

/*
  Purpose:  computes flyer's next move in accordance to instruction 3.4, 
            updates flyer's position, and deals with collisions with heroes
       in:  hero type, escape
      out:  updated hero type
*/
void moveHero(HeroType* h, EscapeType* e){
    srand(time(NULL));    
    int roll=randomInt(10);
    int col = h->partInfo.pos.col;

    if(h->partInfo.pos.col != -1){
        if(h->partInfo.avatar=='T'){
            if(roll<5){
                col+=2;
            }
            if(5<=roll&&roll<7){
                col-=1;
            }
            if(7<=roll&&roll<10){
                col+=1;
            }
        }
        if(h->partInfo.avatar == 'H'){
            if(2<=roll&&roll<3){
                col+=5;
            }
            if(3<=roll&&roll<4){
                col-=4;
            }
            if(4<=roll&&roll<8){
                col+=3;
            }
            if(8<=roll&&roll<10){
                col-=2;
            }
        }

        setPos(&h->partInfo.pos, MAX_ROW-1, col);
        if(h->partInfo.pos.col==MAX_COL-1){h->partInfo.pos.col=-1;}        
    }
}

