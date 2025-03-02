#undef ON
#ifdef ON

main() { /* count characters in input */
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

#undef VER1
#define VER2
#ifdef VER1
   long nc;
   nc = 0;
   while (getchar() != EOF)
      ++nc;
   printf("%ld\n", nc);
#endif
#ifdef VER2
   double nc;
   for (nc = 0; getchar() != EOF; ++nc)
      ;
   printf("%.0f\n", nc);
#endif
}

#endif //ON