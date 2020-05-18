#include "stdafx.h" //C++/CLI Threading: Part I @ http://www.drdobbs.com/cpp/ccli-threading-part-i/184402018
using namespace System;
using namespace System::Threading;

public ref class Point {
	int x;
	int y;
public:

	property int X { // define read-write instance properties X and Y
		int get() { return x; }
		void set(int val) { x = val; }
	}

	property int Y	{
		int get() { return y; }
		void set(int val) { y = val; }
	}

	void Move(int xor, int yor) {
		Monitor::Enter(this); /*1a*/
		X = xor;
		Y = yor;
		Monitor::Exit(this); /*1b*/
	}

	virtual bool Equals(Object^ obj) override	{
		if (GetType() == obj->GetType()) {
			int xCopy1, xCopy2, yCopy1, yCopy2;
			Point^ p = static_cast<Point^>(obj);

			Monitor::Enter(this); /*2a*/
			xCopy1 = X;
			xCopy2 = p->X;
			yCopy1 = Y;
			yCopy2 = p->Y;
			Monitor::Exit(this); /*2b*/

			return (xCopy1 == xCopy2) && (yCopy1 == yCopy2);
		}
		return false;
	}

	virtual int GetHashCode() override {
		int xCopy;
		int yCopy;

		Monitor::Enter(this); /*3a*/
		xCopy = X;
		yCopy = Y;
		Monitor::Exit(this); /*3b*/
		return xCopy^ (yCopy << 1);
	}

	virtual String^ ToString() override	{
		int xCopy;
		int yCopy;

		Monitor::Enter(this); /*4a*/
		xCopy = X;
		yCopy = Y;
		Monitor::Exit(this); /*4b*/

		return String::Concat("(", xCopy, ",", yCopy, ")");
}	};

public ref class ThreadY {
	Point^ pnt;
	bool mover;
public:
	ThreadY(bool isMover, Point^ p) {
		mover = isMover;
		pnt = p;
	}

	void StartUp()	{
		if (mover) {
			for (int i = 1; i <= 10000000; ++i) pnt->Move(i, i); /*1*/
		}else{
			for (int i = 1; i <= 10; ++i) {
				Console::WriteLine(pnt); // calls ToString /*2*/
				Thread::Sleep(10);
}	}	}	};

int main() {
	Point^ p = gcnew Point;

	ThreadY^ o1 = gcnew ThreadY(true, p); /*1*/
	Thread^ t1 = gcnew Thread(gcnew ThreadStart(o1, &ThreadY::StartUp)); /*2*/

	ThreadY^ o2 = gcnew ThreadY(false, p); /*3*/
	Thread^ t2 = gcnew Thread(gcnew ThreadStart(o2, &ThreadY::StartUp)); /*4*/

	t1->Start();
	t2->Start();

	Thread::Sleep(100);
	Console::WriteLine("x: {0}", p->X); /*5*/
	Console::WriteLine("y: {0}", p->Y); /*6*/

	t1->Join(); /*7*/
	t2->Join();
}