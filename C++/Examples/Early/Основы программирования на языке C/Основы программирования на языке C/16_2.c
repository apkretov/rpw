#undef ON
#ifdef ON

// Построить матрицу А(15x15) таким образом: 
// А(7,7)=1, затем, по спирали против часовой стрелки, увеличивая значение очередного элемента на единицу и выделяя все простые числа красным цветом заполнить матрицу
#include <stdio.h>
#include <conio.h>
void main(void) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	//OFF clrscr();
	int mas[15][15];
	int n = 1, x = 6, y = 6, k = 1;
	int i, j;

	while (1) {
		mas[x][y] = k++;
		switch (n) {
			case 1:
				x++;
				break;
			case 2:
				y--;
				break;
			case 3:
				x--;
				break;
			case 4:
				y++;
				break;
		}
		if (x == 15)
			break;
		if (x == y && x < 6)
			n = 4;
		else if (x + y == 12 && x < 6)
			n = 1;
		else if (x + y == 12 && x > 6)
			n = 3;
		else if (x == y + 1 && x > 6)
			n = 2;
	}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			//OFF textcolor(12);
			if (mas[j][i] > 2)
				for (k = 2; k < mas[j][i]; k++)
					if (mas[j][i] % k == 0)
						/*ORIG textcolor(15)*/;
			printf("%3d ", mas[j][i]); //ORIF cprintf("%3d ", mas[j][i]);
		}
		printf("\n");
	}
	
	//OFF getch();
	(void)getchar();
}
#endif