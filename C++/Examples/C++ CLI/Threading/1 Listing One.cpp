#include "stdafx.h" //C++/CLI Threading: Part I @ http://www.drdobbs.com/cpp/ccli-threading-part-i/184402018
using namespace System;
using namespace System::Threading;

public ref class ThreadX {
	int loopStart;
	int loopEnd;
	int dispFrequency;
public:
	ThreadX(int startValue, int endValue, int frequency) {
		loopStart = startValue;
		loopEnd = endValue;
		dispFrequency = frequency;
	}

	void ThreadEntryPoint() { /*1*/
		String^ threadName = Thread::CurrentThread->Name; /*2*/
		for (int i = loopStart; i <= loopEnd; ++i) {
			if (i % dispFrequency == 0) Console::WriteLine("{0}: i = {1,10}", threadName, i);
		}
		Console::WriteLine("{0} thread terminating", threadName);
}	};

int main() {
	ThreadX^ o1 = gcnew ThreadX(0, 1000000, 200000); /*3a*/
	Thread^ t1 = gcnew Thread(gcnew ThreadStart(o1, &ThreadX::ThreadEntryPoint)); /*3b*/
	t1->Name = "t1"; /*3c*/

	ThreadX^ o2 = gcnew ThreadX(-1000000, 0, 200000); /*4a*/
	Thread^ t2 = gcnew Thread(gcnew ThreadStart(o2, &ThreadX::ThreadEntryPoint)); /*4b*/
	t2->Name = "t2"; /*4c*/

	t1->Start(); /*5*/
	t2->Start(); /*6*/
	Console::WriteLine("Primary thread terminating");
}