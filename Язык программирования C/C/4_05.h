#pragma once

#define NUMBER '0' /* signal that number found */
#define TOOBIG '9' /* signal that string is too big */

getch();
ungetch(int);
getop(char s[], int lim);