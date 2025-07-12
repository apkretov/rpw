#include <sstream>
#include "../test_runner.h"
#include "../../stdafx.h"
#include "Canvas.h"
using namespace std;

void TestSimple() {
	Canvas canvas;
	canvas.SetSize({5, 3});

	canvas.AddShape(ShapeType::Rectangle, {1, 0}, {3, 3}, nullptr);

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"#######\n"
		"# ... #\n"
		"# ... #\n"
		"# ... #\n"
		"#######\n";

	ASSERT_EQUAL(answer, output.str());
}

#ifdef OFF
void TestSmallTexture() {
	Canvas canvas;
	canvas.SetSize({6, 4});

	canvas.AddShape(ShapeType::Rectangle, {1, 1}, {4, 2}, MakeTextureSolid({3, 1}, '*'));

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"########\n"
		"#      #\n"
		"# ***. #\n"
		"# .... #\n"
		"#      #\n"
		"########\n";

	ASSERT_EQUAL(answer, output.str());
}

void TestCow() {
	Canvas canvas;
	canvas.SetSize({18, 5});

	canvas.AddShape(ShapeType::Rectangle, {1, 0}, {16, 5}, MakeTextureCow());

	stringstream output;
	canvas.Print(output);

	// Ð—Ð´ÐµÑÑŒ ÑƒÐ¼ÐµÑÑ‚Ð½Ð¾ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ ÑÑ‹Ñ€Ñ‹Ðµ Ð»Ð¸Ñ‚ÐµÑ€Ð°Ð»Ñ‹, Ñ‚.Ðº. Ð² Ñ‚ÐµÐºÑÑ‚ÑƒÑ€Ðµ ÐµÑÑ‚ÑŒ ÑÐ¸Ð¼Ð²Ð¾Ð»Ñ‹ '\'
	const auto answer =
		R"(####################)""\n"
		R"(# ^__^             #)""\n"
		R"(# (oo)\_______     #)""\n"
		R"(# (__)\       )\/\ #)""\n"
		R"(#     ||----w |    #)""\n"
		R"(#     ||     ||    #)""\n"
		R"(####################)""\n";

	ASSERT_EQUAL(answer, output.str());
}

void TestCpp() {
	Canvas canvas;
	canvas.SetSize({77, 17});

	// Ð‘ÑƒÐºÐ²Ð° "C" ÐºÐ°Ðº Ñ€Ð°Ð·Ð½Ð¾ÑÑ‚ÑŒ Ð´Ð²ÑƒÑ… ÑÐ»Ð»Ð¸Ð¿ÑÐ¾Ð², Ð¾Ð´Ð¸Ð½ Ð¸Ð· ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ñ… Ð½Ð°Ñ€Ð¸ÑÐ¾Ð²Ð°Ð½ Ñ†Ð²ÐµÑ‚Ð¾Ð¼ Ñ„Ð¾Ð½Ð°
	canvas.AddShape(ShapeType::Ellipse, {2, 1}, {30, 15},
		MakeTextureCheckers({100, 100}, 'c', 'C'));
	canvas.AddShape(ShapeType::Ellipse, {8, 4}, {30, 9},
		MakeTextureSolid({100, 100}, ' '));

	// Ð“Ð¾Ñ€Ð¸Ð·Ð¾Ð½Ñ‚Ð°Ð»ÑŒÐ½Ñ‹Ðµ Ñ‡Ñ‘Ñ€Ñ‚Ð¾Ñ‡ÐºÐ¸ Ð¿Ð»ÑŽÑÐ¾Ð²
	auto h1 = canvas.AddShape(ShapeType::Rectangle, {54, 7}, {22, 3},
		MakeTextureSolid({100, 100}, '+'));
	auto h2 = canvas.DuplicateShape(h1, {30, 7});

	// Ð’ÐµÑ€Ñ‚Ð¸ÐºÐ°Ð»ÑŒÐ½Ñ‹Ðµ Ñ‡Ñ‘Ñ€Ñ‚Ð¾Ñ‡ÐºÐ¸ Ð¿Ð»ÑŽÑÐ¾Ð²
	auto v1 = canvas.DuplicateShape(h1, {62, 3});
	canvas.ResizeShape(v1, {6, 11});
	auto v2 = canvas.DuplicateShape(v1, {38, 3});

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"###############################################################################\n"
		"#                                                                             #\n"
		"#            cCcCcCcCcC                                                       #\n"
		"#        CcCcCcCcCcCcCcCcCc                                                   #\n"
		"#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
		"#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
		"#   CcCcCcCcC                          ++++++                  ++++++         #\n"
		"#   cCcCcCc                            ++++++                  ++++++         #\n"
		"#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#  CcCcCc                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#   cCcCcCc                            ++++++                  ++++++         #\n"
		"#   CcCcCcCcC                          ++++++                  ++++++         #\n"
		"#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
		"#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
		"#        CcCcCcCcCcCcCcCcCc                                                   #\n"
		"#            cCcCcCcCcC                                                       #\n"
		"#                                                                             #\n"
		"###############################################################################\n";

	ASSERT_EQUAL(answer, output.str());
}
#endif //OFF

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestSimple);
#ifdef OFF
	RUN_TEST(tr, TestSmallTexture);
	RUN_TEST(tr, TestCow);
	RUN_TEST(tr, TestCpp);
#endif //OFF

	return 0;
}