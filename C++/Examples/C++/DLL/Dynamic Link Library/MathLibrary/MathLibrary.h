#pragma once //Walkthrough: Creating and Using a Dynamic Link Library (C++) @ https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp

#ifdef MATHLIBRARY_EXPORTS  
#define MATHLIBRARY_API __declspec(dllexport)   
#else  
#define MATHLIBRARY_API __declspec(dllimport)   
#endif  

namespace MathLibrary {
	class Functions { // This class is exported from the MathLibrary.dll  
	public:
		static MATHLIBRARY_API double Add(double a, double b); // Returns a + b  
		static MATHLIBRARY_API double Multiply(double a, double b); // Returns a * b
		static MATHLIBRARY_API double AddMultiply(double a, double b); // Returns a + (a * b)  
};	}
