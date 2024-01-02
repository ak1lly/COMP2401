#include "defs.h"

/*
  Purpose:  decreases hero's health by flyer's strength (if health gets negative, reset to 0);
            if hero dies, its avatar is changed
       in:  hero type, flyer type
      out:  updated hero type
*/
void incurDamage(HeroType* h, FlyerType* f){
    h->health -= f->strength;

    if(h->health<=0){
        h->health=0;
        h->partInfo.avatar='+';
        h->dead=C_TRUE;
    }
}

/*
  Purpose:  computes direction (-1 for left, +1 for right, 0 for same) of closest hero
            that is still alive and participating; direction is returned using parameter
       in:  flyer type, escape
      out:  direction
*/
void computeHeroDir(EscapeType* e, FlyerType* f, int* dir){
    int dist = MAX_COL;

    for(int i=0; i<e->heroes.size; i++){
        int diff = (e->heroes.elements[i]->partInfo.pos.col)-(f->partInfo.pos.col);
        if(abs(diff)<dist && e->heroes.elements[i]->dead==C_FALSE){
            dist=diff;
        }
    }

    if(dist<0){
        *dir = DIR_LEFT;
    }else if(dist==0){
        *dir = DIR_SAME;
    }else{
        *dir = DIR_RIGHT;
    }
}

/*
  Purpose:  sets a participant's position to given row/col, with values reset
            to closest edge if outside of range
       in:  new row, new col
      out:  updated position type
*/
void setPos(PositionType* p, int r, int c){
    p->row = r;
    p->col = c;    
    if(r>=MAX_ROW){p->row = MAX_ROW-1;}
    if(r<0){p->row = 0;}
    if(c>=MAX_COL){p->col = MAX_COL-1;}
    if(c<0){p->col = 0;}

}

/*
  Purpose:  checks if a flyer with the given position has collided with a hero,
            and returns that hero as the return value (NULL if no collision)
       in:  position type, escape
   return:  collided hero type
*/
HeroType* checkForCollision(PositionType* p, EscapeType* e){
    for(int i=0; i<e->heroes.size; i++){
        if(e->heroes.elements[i]->partInfo.pos.row==p->row && e->heroes.elements[i]->partInfo.pos.col==p->col){
            return e->heroes.elements[i];
        }
    }
    return NULL;
}

