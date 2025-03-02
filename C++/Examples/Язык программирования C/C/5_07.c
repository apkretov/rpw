#include <stdio.h>

static int day_tab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

#undef ON
#ifdef ON
int main(int argc, char* argv[]) {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    int month, day;

    printf("day_of_year(2022, 1, 1): %d\n", day_of_year(2022, 1, 1));
    printf("day_of_year(2022, 12, 31): %d\n", day_of_year(2022, 12, 31));

    month_day(2022, 1, &month, &day);
    printf("\nmonth_day(2022, 1): month %d, day %d\n", month, day);
    month_day(2022, 365, &month, &day);
    printf("month_day(2022, 365): month %d, day %d\n", month, day);
    return 0;
}
#endif

static day_of_year(year, month, day) /* set day of year */
int year, month, day;         /* from month & day */
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += day_tab[leap][i];
    return(day);
}

static month_day(year, yearday, pmonth, pday) /*set month,day */
    int year, yearday, *pmonth, *pday; /* from day of year */
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > day_tab[leap][i]; i++)
        yearday -= day_tab[leap][i];
    *pmonth = i;
    *pday = yearday;
}