#if 0

#include <future>
#include "Listing 4.7.h"
#include "../../stdafx.h"

int main() { 
	print_file_line();

	X x;
	auto f1 = std::async(&X::foo, &x, 42, "hello"); // Calls p->foo(42,"hello") where p is &x
	auto f2 = std::async(&X::bar, x, "goodbye"); // Calls tmpx.bar("goodbye") where tmpx is a copy of x
	auto f2_2 = std::async(X{}); //MINE

	Y y;
	auto f3 = std::async(Y(), 3.141); // Calls tmpy(3.141) where tmpy is move - constructed from Y()
	auto f4 = std::async(std::ref(y), 2.718); // Calls y(2.718)
	auto f6 = std::async(baz, std::ref(x)); // Calls baz(x)

	auto f5 = std::async(move_only()); // Calls tmp() where tmp is constructed from std::move(move_only())
}
#endif //1

/*
auto f5 = std::async(move_only()); // Calls tmp() where tmp is constructed from std::move(move_only())
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ 
✦ The comment is explaining how std::async handles the argument you pass to it. Let's break it down.

   1. move_only(): This function call creates and returns a temporary, unnamed object. Based on the function's name and
	  common C++ patterns, this object is a "functor" (an object that can be called like a function) and it is "move-only"
	  (it can be moved, but not copied).

   2. std::async(...): This function takes a callable entity (like a function pointer, lambda, or functor) and its
	  arguments, and runs it asynchronously (potentially in a new thread).

   3. Passing the temporary: The temporary functor created by move_only() is passed as the callable entity to std::async.
	  Because it's a temporary (an rvalue), std::async can move it into its own internal storage for the new thread to use.

  Now let's look at the comment:
  // Calls tmp() where tmp is constructed from std::move(move_only())

   * tmp: This represents the internal variable inside the std::async machinery that holds the callable task.
   * constructed from std::move(move_only()): This describes how tmp gets its value. The result of move_only() is an rvalue
	 temporary, which is then moved to initialize tmp. The comment uses std::move() to explicitly describe this move
	 operation, even though it happens automatically for temporary objects.
   * Calls tmp(): Once the asynchronous task starts, it invokes the callable object it has stored. Since tmp now holds the
	 functor, the system executes tmp().

  In simple terms: std::async takes the move-only functor you created, moves it into its internal state, and then calls it
  in a separate thread. The comment is a condensed explanation of this internal mechanism.
*/