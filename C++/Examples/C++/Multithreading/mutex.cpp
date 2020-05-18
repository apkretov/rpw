#include "stdafx.h"
#include <iostream>
#include <thread> //C++ Multithreading @ https://www.tutorialcup.com/cplusplus/multithreading.htm
using namespace std;

void threadFunc() { cout << "Welcome to Multithreading\n"; } //Initializing thread with a function.

void detach() { //Detaching thread.
	thread funcTest1(threadFunc); //pass a function to thread
	funcTest1.detach(); //detach funcTest1 from main thread
	if (funcTest1.joinable()) { 
		funcTest1.join(); //main is blocked until funcTest1 is not finished
		cout << "functTest1 is joined\n";
	}else cout << "functTest1 is detached\n";
}

void treadId() { //Thread ID.
	thread t1(threadFunc); //create 3 different threads
	thread t2(threadFunc);
	thread t3(threadFunc);
	thread::id id1 = t1.get_id(); //get id of all the threads
	thread::id id2 = t2.get_id();
	thread::id id3 = t3.get_id();
	cout << endl;
	if (t1.joinable()) { //join all the threads
		t1.join();
		cout << "Thread with id " << id1 << " is terminated" << endl;
	}
	if (t2.joinable()) {
		t2.join();
		cout << "Thread with id " << id2 << " is terminated" << endl;
	}
	if (t3.joinable()) {
		t3.join();
		cout << "Thread with id " << id3 << " is terminated" << endl;
}	}

#include <iomanip> 
#include <chrono>
#include <ctime>
using namespace std;
using std::chrono::system_clock;
#pragma warning(disable: 4996) 
void thisThread() { //this_thread Namespace.
	cout << "The id of current thread is " << this_thread::get_id << endl;
	time_t timet = system_clock::to_time_t(system_clock::now()); //sleep while next minute is not reached //get current time
	struct tm * time = localtime(&timet); //convert it to tm struct
	cout << "Current time: " << put_time(time, "%X") << '\n';
	std::cout << "Waiting for the next minute to begin...\n";
	time->tm_min++; time->tm_sec = 0;
	this_thread::sleep_until(system_clock::from_time_t(mktime(time))); //sleep until next minute is not reached
	cout << std::put_time(time, "%X") << " reached!\n";
	this_thread::sleep_for(chrono::seconds(5)); //sleep for 5 seconds
	timet = system_clock::to_time_t(system_clock::now()); //get current time
	time = std::localtime(&timet); //convert it to tm struct
	cout << "Current time: " << put_time(time, "%X") << '\n';
}

#include <vector>
vector<int> vec;
void push() {
	for (int i = 0; i != 10; ++i) {
		cout << "Push " << i << endl;
		_sleep(500);
		vec.push_back(i);
}	}

void pop() {
	for (int i = 0; i != 10; ++i) {
		if (vec.size() > 0) {
			int val = vec.back();
			vec.pop_back();
			cout << "Pop " << val << endl;
		}
		_sleep(500);
}	}

void concurrentAccess() { //Concurrent access to resources
	thread push(push); //create two threads
	thread pop(pop);
	if (push.joinable())	push.join();
	if (pop.joinable()) pop.join();
}

#include <mutex>
mutex m;
void pushMutex() {
	cout << "pushMutex() started\n"; //TEST
	m.lock();
	cout << "pushMutex() inside m.lock()\n"; //TEST
	for (int i = 0; i != 10; ++i) {
		cout << "Push " << i << endl;
		_sleep(500);
		vec.push_back(i);
	}
	m.unlock();
	cout << "pushMutex() outside m.lock()\n"; //TEST
}

void popMutex() {
	cout << "popMutex() started\n"; //TEST
	m.lock();
	cout << "popMutex() inside m.lock()\n"; //TEST
	for (int i = 0; i != 10; ++i) {
		if (vec.size() > 0) {
			int val = vec.back();
			vec.pop_back();
			cout << "Pop " << val << endl;
		}
		_sleep(500);
	}
	m.unlock();
	cout << "popMutex() outside m.lock()\n"; //TEST
}

void concurrentAccessMutex() { //Concurrent access to resources
	thread push(pushMutex); //create two threads
	thread pop(popMutex);
	if (push.joinable())	push.join();
	if (pop.joinable()) pop.join();
}

bool mblnLoop = true;
void myFncFlagStopped() { //A loop stopped by the mblnLoop flag.
	while (mblnLoop) {
		cout << "thread id: " << this_thread::get_id() << "   Welcome to Multithreading" << endl;
		this_thread::sleep_for(chrono::nanoseconds(500000000));
}	}

void myTestFlagStopped() { //It returns after myFncFlagStopped has gotten stopped by the mblnLoop flag.
	thread objThread(myFncFlagStopped); 
	thread::id objID = objThread.get_id(); 
	this_thread::sleep_for(chrono::nanoseconds(2000000000));
	mblnLoop = false; //Stopping by the flag.
	if (objThread.joinable()) { 
		objThread.join();
		cout << "Thread with id " << objID << " is terminated" << endl;
}	}

void myTestInfinit() { //myFncFlagStopped is infite because myFncFlagStopped doesn't get stopped by the mblnLoop flag.
	thread objThread(myFncFlagStopped); 
	thread::id objID = objThread.get_id(); 
	if (objThread.joinable()) { 
		objThread.join();
		cout << "Thread with id " << objID << " is terminated" << endl;
}	}

void myFncInfinite() { //An infinite loop.
	while (1) {
		cout << "Welcome to Multithreading" << endl;
		this_thread::sleep_for(chrono::nanoseconds(500000000));
}	}

void myTestDetachStopped() { //It returns because myFncInfinite's trhead gets detached. myFncInfinite is infinite but stopps on objThread termination when this function returns.
	thread objThread(myFncInfinite); 
	thread::id objID = objThread.get_id(); 
	cout << "\nmyFncDetach thread id: " << objID << endl;
	objThread.detach();
	if (objThread.joinable()) { 
		objThread.join();
		cout << "Thread with id " << objID << " is terminated" << endl;
	} else cout << "myFncInfinite is detached" << endl;
}

void myTestSleepAndDetachStopped() { //myFncInfinite runs while the this function is sleeping. Then the scenario of myTestDetachStopped unwinds.
	thread objThread(myFncInfinite); 
	thread::id objID = objThread.get_id(); 
	cout << "\nmyFncDetach thread id: " << objID << endl;
	objThread.detach();
	this_thread::sleep_for(chrono::seconds(2));
	if (objThread.joinable()) { 
		objThread.join();
		cout << "Thread with id " << objID << " is terminated" << endl;
	}
	else cout << "myFncInfinite is detached" << endl;
}

thread* mobjThread;
void myFncDeleteThread( void (*myFnc)() ) { //Unlike myFncFlagStopped stopped with the flag, myFncInfinite doesn't get stopped by mobjThread termination. It contunues within the 1st thread sumultaneosly with that of the 2nd thread. Both myFncInfinite processes get stopped only on the programme termination.
	cout << "Create a new thread." << endl;
	mblnLoop = true; //Setting the flag before using it.
	mobjThread = new thread(myFnc);
	mobjThread->detach();
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Delete the thread." << endl << endl;
	mblnLoop = false; //Stopping myFncFlagStopped with this flag.
	delete mobjThread;
}

void myTestDeleteThread(void(*myFnc)()) { //Call myFncDeleteThread twice sleeping in-between.
	cout << "Call myTestDeleteThread the 1st time." << endl;
	myFncDeleteThread(myFnc);
	cout << "Sleeping after the 1st call." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << endl << "Call myTestDeleteThread the 2nd time." << endl;
	myFncDeleteThread(myFnc);
}

int main() {
	detach();
	//treadId();
	//thisThread();
	//concurrentAccess();
	//concurrentAccessMutex();
	//myTestFlagStopped();
	//myTestInfinit();
	//myTestDetachStopped();
	//myTestSleepAndDetachStopped();
	//myTestDeleteThread(myFncInfinite);
	//myTestDeleteThread(myFncFlagStopped);
}
