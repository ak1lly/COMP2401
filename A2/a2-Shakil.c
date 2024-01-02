#include <stdio.h>
#include <string.h>

#define BYTE 8
#define NIBBLE 4
#define MAX_BUF  256
#define IV 0b11001011

unsigned char initKey();
unsigned char processKey(unsigned char);
unsigned char updateKey(unsigned char);

void encode(unsigned char*, unsigned char*, unsigned char, int);
void decode(unsigned char*, unsigned char*, unsigned char, int);

unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);
unsigned char cShiftRight(unsigned char);
unsigned char cShiftLeft(unsigned char);

int readBytes(unsigned char*, int);
unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);


int main()
{
  char str[8];
  int  choice;

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  What is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);


  switch (choice) {

    case 1:
        unsigned char ptIn[MAX_BUF];
        unsigned char ctOut[] = {IV};
        unsigned char eKey;
        

        eKey = initKey();
        printf("  Enter plain text:\n ");
        fgets((char*)ptIn, MAX_BUF, stdin);

        int numBytesEn = readBytes(ptIn, MAX_BUF);

        encode(ptIn,ctOut,eKey,numBytesEn);

        printf("  Encrypted code:\n");
        for(int i=1; i<=numBytesEn; i++){
            printf(" %03d",ctOut[i]);
        }
        break;

    case 2:
        unsigned char ptOut[MAX_BUF];
        unsigned char ctIn[MAX_BUF+1];
        unsigned char dKey;

        dKey = initKey();
        printf("  Enter encrypted code:\n ");

        int byte = IV;
        int j = 0;
        while(byte != -1){
            ctIn[j] = (unsigned char)byte;
            scanf("%d", &byte);
            j++;
        }
        int numBytesDe = j-1;
        decode(ctIn,ptOut,dKey, numBytesDe);

        printf("  Decrypted text: \n");
        
        int k=0;
        while(ptOut[k]!='\0'){
            printf("%c",ptOut[k]);
            k++;
        }
        break;

    case 0:

        break;

    default:
        printf("  Please enter a valid selection, aborting program.");

        break;
  }

  return(0);
}

/*
  Function:  decode
  Purpose:   decrypts an array of cipher text bytes with key and previously encrypted byte
       in:   array of cipher text bytes, initial processed key, size of encoded message
      out:   array of plain text bytes
   return:   plain text byte
*/
void decode(unsigned char *ct , unsigned char *pt, unsigned char key, int numBytes){
    for(int i=0; i < numBytes; i++){
        key = updateKey(key);
        pt[i]=decryptByte(ct[i+1], key, ct[i]);
    }
}
/*
  Function:  decryptByte
  Purpose:   decrypts single cipher text byte with key and previously encrypted byte
       in:   cipher text byte, updated key, previous cipher text
   return:   plain text byte
*/

unsigned char decryptByte(unsigned char ct, unsigned char key, unsigned char prev){
    unsigned char temp = 0;

    for(int i=0; i<BYTE; i++){
        int mirrori = ((BYTE - 1) - i);

        if(getBit(key, i) == 1){
            prev=cShiftRight(prev);
        }

        if(((getBit(ct, i)) ^ (getBit(prev, mirrori))) == 1){
            temp = setBit(temp, i);
        }
    }
    return temp;

}
/*
  Function:  encode
  Purpose:   encrypts an array of cipher text bytes with key and previously encrypted byte
       in:   array of plain text bytes, initial processed key, size of plain message
      out:   array of cipher text bytes
   return:   plain text byte
*/

void encode(unsigned char *pt , unsigned char *ct, unsigned char key, int numBytes){
    for(int i=0; i < numBytes; i++){
        key = updateKey(key);
        ct[i+1]=encryptByte(pt[i], key, ct[i]);
    }
}


/*
  Function:  encryptByte
  Purpose:   encrypt single plain text byte with key and previously encrypted byte
       in:   plain text byte, updated key, previous cipher text
   return:   encrypted byte
*/
unsigned char encryptByte(unsigned char pt, unsigned char key, unsigned char prev){
    unsigned char temp = 0;

    for(int i=0; i<BYTE; i++){
        int mirrori = ((BYTE - 1) - i);

        if(getBit(key, i) == 1){
            prev=cShiftRight(prev);
        }

        if(((getBit(pt, i)) ^ (getBit(prev, mirrori))) == 1){
            temp = setBit(temp, i);
        }
    }
    return temp;
}

/*
  Function:  initKey
  Purpose:   get intended key input as long as it exists within bounds 1-15, if not re-request input
   return:   valid key value
*/
unsigned char initKey(){
    unsigned char key;
    int input;
   
    printf("  Please enter a partial key value (1-15):");
    scanf("%d", &input);
    key = (unsigned char) input;

    if(1<=key && key<=15){
        key = processKey(key);
        return key;
    }else{
        return initKey();
    } 
}

/*
  Function:  processKey
  Purpose:   process key value according to outlined initialization steps
       in:   raw key value
   return:   processed key value
*/
unsigned char processKey(unsigned char oKey){
    unsigned char pKey;
    pKey = oKey << NIBBLE;
    for(int i=BYTE-1; i>=NIBBLE; i--){
        if(getBit(pKey, i) == 0){
            pKey = setBit(pKey, ((i-1)%4));
        }
    }

    return pKey;
}

/*
  Function:  cShiftRight
  Purpose:   circular shift any byte by one bit to the right without losing data
   in/out:   any byte (unsigned char)
*/
unsigned char cShiftRight(unsigned char u){
    int lostData = getBit(u, 0);
    unsigned char shiftedData = u >> 1;

    if(lostData == 1){
        return setBit(shiftedData, 7);
    }
    return shiftedData;
}

/*
  Function:  cShiftLeft
  Purpose:   circular shift any byte by one bit to the left without losing data
   in/out:   any byte (unsigned char)
*/
unsigned char cShiftLeft(unsigned char u){
    int lostData = getBit(u, 7);
    unsigned char shiftedData = u << 1;

    if(lostData == 1){
        return setBit(shiftedData, 0);
    }
    return shiftedData;
}

/*
  Function:  updateKey
  Purpose:   updates key with each byte according to outlined criteria
       in:   last used key
   return:   newly updated key
*/
unsigned char updateKey(unsigned char key){
    if(key%3 == 0){
        for(int j=1; j<=3; j++){
            key=cShiftLeft(key);
        }
    }else{
        for(int j=1; j<=2; j++){
            key=cShiftLeft(key);
        }
    }
    return key;
}


/*
  Function:  readBytes
  Purpose:   reads characters from the standard output
      out:   the buffer containing the bytes read
       in:   the capacity of the buffer (maximum size)
   return:   the number of bytes actually read from the user
*/
int readBytes(unsigned char* buffer, int max)
{
  int num = 0;

  fgets((char*)buffer, max, stdin);
  num = strlen((char*)buffer) - 1;
  buffer[num] = '\0';

  return num;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
  return((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
  return (c|(1<<n));

}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
  return (c & (~(1<<n)));
}

