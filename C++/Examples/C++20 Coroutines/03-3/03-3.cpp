#pragma region MINE

#include "demo_01_lazy_generator.h"
#include "demo_01b_no_yield_suspend.h"
#include "demo_02_eager_generator.h"
#include "demo_03_task_return.h"
#include "demo_04_task_void.h"
#include "demo_05_manual_await.h"
#include "demo_06_nested_await.h"
#include "demo_07_exception_across_suspend.h"
#include "../../stdafx.h"

int main() {
	print_file_line();

	run_demo_01();
#if 1
	run_demo_01b();
	run_demo_02();
	run_demo_03();
	run_demo_04();
	run_demo_05();
	run_demo_06();
	run_demo_07();
#endif //1

	return 0;
}
#pragma endregion //MINE
