#include "stdafx.h"
#include "IClass.h" //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/
#include <iostream>
#include <windows.h>
using namespace std;

typedef IClass* (__cdecl *iclass_factory)(); // A factory of IClass-implementing objects looks thus

int main() {
    HINSTANCE dll_handle = ::LoadLibrary(TEXT("MyClass.dll")); // Load the DLL
    if (!dll_handle) {
        cerr << "Unable to load DLL!\n";
        return 1;
    }

    iclass_factory factory_func = reinterpret_cast<iclass_factory>(::GetProcAddress(dll_handle, "create_class")); // Get the function from the DLL
    if (!factory_func) {
        cerr << "Unable to load create_class from DLL!\n";
        ::FreeLibrary(dll_handle);
        return 1;
    }

    IClass* instance = factory_func(); // Ask the factory for a new object implementing the IClass interface

    int t = instance->do_stuff(5); // Play with the object
    cout << "t = " << t << endl;
    instance->do_something_else(100.3);
    int t2 = instance->do_stuff(0);
    cout << "t2 = " << t2 << endl;

    instance->destroy(); // Destroy it explicitly
    ::FreeLibrary(dll_handle);
	 
	 cin.get();
    return 0;
}