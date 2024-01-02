#include "defs.h"

/*
  Purpose:  initializes the escape, contains game loop, handles escape result, cleans up 
*/
void runEscape(){
    srand(time(NULL));    
    char hollow[MAX_BUFF];
    EscapeType e;
    EscapeType* ptr = &e;
    setupServerSocket(&e.listenSocket);
    acceptConnection(e.listenSocket, &e.viewSocket);
    initEscape(ptr);

    while(escapeIsOver(ptr) == C_FALSE){
        serializeHollow(ptr, hollow);
        printf("%s", hollow);
        sendData(e.viewSocket, hollow);

        int bRoll = randomInt(100);
        int mRoll = randomInt(100);
        
        if(bRoll<BIRD_SPAWN_RATE){
            spawnFlyer(&e, 'v', randomInt(4), randomInt(MAX_COL), 3+randomInt(3));
        }

        if(mRoll<MONKEY_SPAWN_RATE){
            spawnFlyer(&e, '@', randomInt(MAX_ROW), randomInt(MAX_COL), 8+randomInt(5));
        }

        for(int i=0; i<ptr->flyers.size; i++){
            moveFlyer(ptr->flyers.elements[i], &e);
            HeroType* hit = checkForCollision(&ptr->flyers.elements[i]->partInfo.pos, ptr);
            if(hit!=NULL){
                incurDamage(hit, ptr->flyers.elements[i]);
            }
        }

        for(int i=0; i<e.heroes.size; i++){
            moveHero(ptr->heroes.elements[i], &e);
        }

        usleep(OUTPUT_INTERVAL);
    }
    
    serializeHollow(ptr, hollow);
    sendData(e.viewSocket, hollow);
    printf("%s", hollow);
    handleEscapeResult(ptr);
    close(e.viewSocket);
    close(e.listenSocket);
    cleanupEscape(ptr);

}

/*
  Purpose:  sends connection request to server at given IP address, loops and
            waits for data that it prints out, until quit message is received 
*/
void viewEscape(char* ip){
    char hollow[MAX_BUFF];
    int viewSocket;

    setupClientSocket(&viewSocket, ip);
    while (1) {
        int bytesReceived = rcvData(viewSocket, hollow);
        if (bytesReceived <= 0) {
            break;
        }
        printf("%s\n", hollow);
    }

    close(viewSocket);
}

/*
  Purpose:  initializes 2D grid with participant avatars in current positions 
       in:  escape
      out:  2d array hollow
*/
void initHollow(EscapeType* e, char(*hollow)[MAX_COL]){
    for(int r = 0; r < MAX_ROW; r++){
        for(int c = 0; c < MAX_COL; c++){
            hollow[r][c] = ' ';
        }
    }


    for(int i=0; i<e->heroes.size; i++){
        int row = e->heroes.elements[i]->partInfo.pos.row;
        int col = e->heroes.elements[i]->partInfo.pos.col;
        if(e->heroes.elements[i]->partInfo.pos.col!=-1){
            hollow[row][col] = e->heroes.elements[i]->partInfo.avatar;
        }
    }

    for(int i=0; i<e->flyers.size; i++){
        int row = e->flyers.elements[i]->partInfo.pos.row;
        int col = e->flyers.elements[i]->partInfo.pos.col;
        if(flyerIsDone(e->flyers.elements[i])==C_FALSE){
            hollow[row][col] = e->flyers.elements[i]->partInfo.avatar;
        }
    }
}

/*
  Purpose:  constructs 1D array with formatted Hollow output, containing all avatars
            in their positions, with borders, spacing and newlines
       in:  escape
      out:  hollow
*/
void serializeHollow(EscapeType* e, char* hollow){
    char temp[MAX_ROW][MAX_COL];
    initHollow(e, temp);

    char arr[MAX_BUFF];
    int count = 0;

    for(int i=0; i<MAX_COL+2; i++){
        arr[count++] = '-';
    }
    arr[count++] = '\n';
    for(int r=0; r<MAX_ROW-1; r++){ 
        arr[count++] = '|';
        for(int c=0; c<MAX_COL; c++){
            arr[count++] = temp[r][c];
        }
        arr[count++] = '|';
        arr[count++] = '\n';
    }
    arr[count-1] = ' ';

    char h[MAX_BUFF];

    HeroType* hero = e->heroes.elements[0];

    sprintf(h, "%7s : %2d", hero->name, hero->health);
    int c = 0;

    while(h[c] != '\0'){
        arr[count++] = h[c];
        c++;
    }

    arr[count++] = '\n';

    arr[count++] = '=';
    for(int c=0; c<MAX_COL; c++){
        arr[count++] = temp[MAX_ROW-1][c];
    }
    arr[count++] = '=';
    arr[count++] = ' ';

    char t[MAX_BUFF];

    hero = e->heroes.elements[1];

    sprintf(t, "%7s : %2d", hero->name, hero->health);

    c=0;
    while(t[c] != '\0'){
        arr[count++] = t[c];
        c++;
    }

    arr[count++] = '\n';

    for(int i=0; i<MAX_COL+2; i++){
        arr[count++] = '-';
    }
    
    arr[count++] = '\n';
    arr[count++] = '\0';

    strcpy(hollow, arr);
}