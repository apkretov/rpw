#include<stdlib.h>
#include<string.h>

#undef ON
#ifdef ON
int main() { // System() Function in C/C++ @ https://www.tutorialspoint.com/system-function-in-c-cplusplus
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   char cmd[10];
   strcpy_s(cmd, 9, "dir");
   system(cmd);
   
   return 0;
}
#endif