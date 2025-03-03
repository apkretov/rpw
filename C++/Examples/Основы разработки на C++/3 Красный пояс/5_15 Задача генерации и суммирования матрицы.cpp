#if 0

#include "../../stdafx.h"
#include "5_15 Задача генерации и суммирования матрицы.h"

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	LOG_DURATION("Total");
	const size_t matrix_size = 7000;
	vector<vector<int>> matrix;
	{
		LOG_DURATION("Single thread generation");
		matrix = GenerateSingleThread(matrix_size);
	}
	{
		LOG_DURATION("Multi thread generation"); //MINE: Instead, this is longer on my PC...
		matrix = GenerateMultiThread(matrix_size, 2000);
	}
	{
		LOG_DURATION("Single thread sum");
		cout << AS_KV(SumSingleThread(matrix)) << endl;
	}

	return 0;
}
#endif //1