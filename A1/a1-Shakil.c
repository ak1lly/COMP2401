#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_ROW       15
#define MAX_COL       60
#define MAX_BIRDS    128
#define BIRD_FREQ     90

#define C_TRUE         1
#define C_FALSE        0
#define PLACEHOLDER   -1

void initHollow(char (*hollow)[MAX_COL]);
void printHollow(char (*hollow)[MAX_COL]);
int escapeOver(char tAvatar, char hAvatar, int tCol, int hCol);
int isDone(char avatar, int col);
int  moveHero(char avatar, int oldPos);
void moveBird(int index, int *rows, int *cols);
void moveInHollow(char avatar, int oldRow, int oldCol, int newRow, int newCol, char (*hollow)[MAX_COL]);
void printResult(char tAvatar, char hAvatar, int tCol, int hCol);
int  randomInt(int);

int main()
{
  srand(time(NULL));
  char present[MAX_ROW][MAX_COL], next[MAX_ROW][MAX_COL];

  int birdRow[MAX_BIRDS], birdCol[MAX_BIRDS];
  int baseRow = MAX_ROW-1;
  int birdCount = 0;

  for(int r = 0; r < MAX_BIRDS; r++){
    birdCol[r] = PLACEHOLDER;
    birdRow[r] = PLACEHOLDER;
  }

  char heroT = 'T', heroH = 'H', bird = 'v', grave = '+', completed = ' ';
  int oldPosT = 0, oldPosH = 0, newPosT = 0, newPosH = 0, check = C_FALSE; 

  initHollow(present);
  
  present[MAX_ROW-1][oldPosH] = heroH;
  present[MAX_ROW-1][oldPosT] = heroT;

  printHollow(present);

  while(check == C_FALSE){
    if(birdCount >= MAX_BIRDS){
      birdCount = 0;
    }
    initHollow(next);

    check = escapeOver(heroT, heroH, newPosT, newPosH);

    oldPosT = newPosT;
    oldPosH = newPosH;

    int birdProb; 
    birdProb = randomInt(100);

    if(oldPosT == MAX_COL-1){
      heroT = completed;
    }

    newPosT=moveHero(heroT, oldPosT);
    moveInHollow(heroT, baseRow, oldPosT, baseRow, newPosT, next);

    if(oldPosH == MAX_COL-1){
      heroH = completed;
    } 

    newPosH=moveHero(heroH, oldPosH);
    moveInHollow(heroH, baseRow, oldPosH, baseRow, newPosH, next);
    
    if(birdProb<BIRD_FREQ){
      birdRow[birdCount] = 0;
      birdCol[birdCount] = randomInt(MAX_COL); 
      birdCount++;
    }

    for(int b = 0; b <= MAX_BIRDS; b++){
      if(birdRow[b] != PLACEHOLDER || birdCol[b] != PLACEHOLDER){
        moveBird(b, birdRow, birdCol);
        if(next[birdRow[b]][birdCol[b]] == 'T'){
          next[birdRow[b]][birdCol[b]] = grave;
          heroT = grave; 
        }else if(next[birdRow[b]][birdCol[b]] == 'H'){
          next[birdRow[b]][birdCol[b]] = grave;
          heroH = grave; 
        }else{
          next[birdRow[b]][birdCol[b]] = bird;
        }
      }
    }

    for(int r = 0; r < MAX_ROW; r++){
      for(int c = 0; c < MAX_COL; c++){
        present[r][c] = next[r][c];
      }
    }


    printHollow(present);

    usleep(300000);
  }

  printHollow(present);


  printResult(heroT, heroH, newPosT, newPosH);

  return 0;
}
/*
  Function:  initHollow
  Purpose:   intitalize hollow game grid
  Parameters:
    out:  hollow array
*/

void initHollow(char (*hollow)[MAX_COL])
{
  for(int r = 0; r < MAX_ROW; r++){
    for(int c = 0; c < MAX_COL; c++){
      hollow[r][c] = ' ';
    }
  }
}
/*
  Function:  printHollow
  Purpose:   print hollow game grid
  Parameters:
    in:      hollow array
    return:  void, print grid to screen 
*/

void printHollow(char (*hollow)[MAX_COL])
{
  system("clear");
  printf("--------------------------------------------------------------\n");
  for(int r = 0; r < MAX_ROW; r++){
    if(r==MAX_ROW-1){
      printf("%c",'=');
    }else{
      printf("%c",'|');
    }
    for(int c = 0; c < MAX_COL; c++){
      printf("%c",hollow[r][c]);
    }
    if(r==MAX_ROW-1){
      printf("%c",'=');
    }else{
      printf("%c",'|');
    }
    printf("\n");
  }
  printf("--------------------------------------------------------------\n");
}

/*
  Function:  escapeOver
  Purpose:   returns the constant equivalent to true if the escape has concluded, or the constant that
  represents false otherwise
  Parameters:
  in:      timmy, harold, timmy pos, harold pos
  return:  truth value to game state
*/
int escapeOver(char tAvatar, char hAvatar, int tCol, int hCol){
  if(isDone(tAvatar, tCol) == C_TRUE && isDone(hAvatar, hCol) == C_TRUE){
    return C_TRUE;
  }
  else{
    return C_FALSE;
  }
}

/*
  Function:  isDone
  Purpose:   function that returns the predefined constant equivalent to true if the hero 
  with the given avatar and column position is dead or has escaped the hollow
  Parameters:
  in:      avatar, avatar col
  return:  truth value to game state
*/

int isDone(char avatar, int col){
  if(col == MAX_COL-1){
    return C_TRUE;
  }if(avatar == '+'){
    return C_TRUE;
  }else{
    return C_FALSE;
  }
}


/*
  Function:  printResult
  Purpose:   prints to the screen the outcome of the escape, as one of the three possibilities: both heroes are
  dead, or both heroes have escaped, or one hero is dead and the other escaped; if the last case
  has occurred, the function must indicate by name which hero died and which one escaped
  Parameters:
  in:      timmy, harold, timmy pos, harold pos
  return:  summary of game state
*/

void printResult(char tAvatar, char hAvatar, int tCol, int hCol){
  if(hCol==MAX_COL-1&&tCol==MAX_COL-1){
    printf("Both Heroes have made their escape!");
  }else if(hCol == MAX_COL-1 && tAvatar == '+'){
    printf("Harold has made his escape, but Timmy has DIED!");
  }else if(tCol == MAX_COL-1 && hAvatar == '+'){
    printf("Timmy has made his escape, but Harold has DIED!");
  }else{
    printf("Both our heros have died!");
  }
}

/*
  Function:  moveBird
  Purpose: computes a new position for the bird found at the given index in the 
  given rows and columns arrays, in accordance with the probabilistic bird moves  
  Parameters:
  in:      index of parallel array, array of bird row locations, array of bird col locations
  out:     updated values at index in parallel arrays, updated parallel arrays
*/

void moveBird(int index, int *row, int *col){

  int roll = randomInt(6);

  if(roll==0){
    row[index] = row[index] + 1;
    col[index] = col[index] - 1;
  }else if(roll==1){
    row[index] = row[index] + 1;
    col[index] = col[index] + 1;
  }else if(roll==2){
    row[index] = row[index] + 2;
    col[index] = col[index] - 1;
  }else if(roll==3){
    row[index] = row[index] + 2;
    col[index] = col[index] + 1;
  }else if(roll==4){
    row[index] = row[index] + 1;
  }else{
    row[index] = row[index] + 2;
  }

  if(col[index]<0){
    col[index] = 0;
  }else if(col[index] > MAX_COL-1){
    col[index] = MAX_COL-1;
  }
  
  if(row[index]>MAX_ROW-1){
    row[index] = PLACEHOLDER;
    col[index] = PLACEHOLDER;
  }
}

/*
  Function:  moveHero
  Purpose: function computes a new position (a new column) for a hero, in accordance 
  with the probabilistic hero moves
  Parameters:
  in:      hero avatar, current hero position
  return:  new hero position
*/

int moveHero(char avatar, int oldPos){
  srand(time(NULL));
  int roll = randomInt(10);
  int newPos;

  if(oldPos==MAX_COL-1 || avatar == '+'){
    return oldPos;
  }

  if(avatar == 'T'){
    if(roll<5){
      newPos = oldPos + 3;
    }
    if(5<=roll&&roll<7){
      newPos = oldPos - 2;
    }
    if(7<=roll&&roll<10){
      newPos = oldPos + 1;
    }
  }
  if(avatar == 'H'){
    if(roll>2){
      newPos = oldPos;
    }
    if(2<=roll&&roll<3){
      newPos = oldPos + 6;
    }
    if(3<=roll&&roll<4){
      newPos = oldPos - 4;
    }
    if(4<=roll&&roll<7){
      newPos = oldPos + 4;
    }
    if(7<=roll&&roll<10){
      newPos = oldPos - 2;
    }
  }
  if(newPos<0){
    newPos = 0;
  }else if(newPos>=MAX_COL-1){
    newPos= MAX_COL-1;
  }
  
  return newPos;
}

/*
  Function:  moveInHollow
  Purpose: moves a avatar within the given hollow from its old pos to new pos
  Parameters:
    in:      avatar, old row, old col, new row, new col
    out:  hollow
*/


void moveInHollow(char avatar, int oldRow, int oldCol, int newRow, int newCol, char (*hollow)[MAX_COL]){
  hollow[oldRow][oldCol] = ' ';
  hollow[newRow][newCol] = avatar;


}

/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return(rand() % max);
}



