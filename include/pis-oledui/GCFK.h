#ifndef GCFK
#define GCFK
 
#include <stdio.h>
#include <stdlib.h>
  
#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "
  
int GetChar();
 
#endif
