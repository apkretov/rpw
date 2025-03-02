#include "4_05.h"

#define MAXOP 20 /* max size of operand, operator */

#undef ON
#ifdef ON
main() { /* reverse polish desk calculator */
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    int tupe;
    char s[MAXOP];
    double op2, atof_4_02(), pop(), push();

    while ((tupe = getop(s, MAXOP)) != EOF) {
        switch (tupe) {
        case NUMBER:
            push(atof_4_02(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("zero divisor popped\n");
            break;
        case '=':
            printf("\t%f\n", push(pop()));
            break;
        case 'c':
            clear();
            break;
        case TOOBIG:
            printf("%.20s ... is too long\n", s);
            break;
        }
    }
}
#endif

#define MAXVAL 100 /* maximum depth of val stack */

static int sp = 0; /* stack pointer */
static double val[MAXVAL]; /*value stack */

static double push(f) /* push f onto value stack */
double f; 
{
    if (sp < MAXVAL)
        return(val[sp++] = f);
    else {
        printf("error: stack full\n");
        clear();
        return(0);
    }
}

static double pop() { /* pop top value from steack */
    if (sp > 0)
        return(val[--sp]);
    else {
        printf("error: stack empty\n");
        clear();
        return(0);
    }
}

static clear() { /* clear stack */
    sp = 0;
}