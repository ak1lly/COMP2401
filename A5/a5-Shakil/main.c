#include "defs.h"

int main(int argc, char *argv[])
{
  if (argc == 1) {
    runEscape();
  } else if (argc == 2) {
    viewEscape(argv[1]);
  } else {
    exit(EXIT_FAILURE);
  }

  return(0);
}

/* 
  Purpose:  generate random int
       in:  max
   return:  random int between 0-max
*/
int randomInt(int max)
{
  return(rand() % max);
}

