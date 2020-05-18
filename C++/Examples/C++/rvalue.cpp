#include "stdafx.h"
#include <string>
#include <memory>
#include <cassert>
using namespace std;

template<typename T> class Buffer {
   string _name;
   size_t _size;
   unique_ptr<T[]> _buffer;
public:
   Buffer() : _size(16), _buffer(new T[16]) { } // default constructor
   Buffer(const string& name, size_t size) : _name(name), _size(size), _buffer(new T[size]) { } // constructor

   Buffer(const Buffer& copy) : _name(copy._name), _size(copy._size), _buffer(new T[copy._size]) { // copy constructor
      T* source = copy._buffer.get();
      T* dest = _buffer.get();
      std::copy(source, source + copy._size, dest);
   }

   Buffer(Buffer&& temp) : _name(move(temp._name)), _size(temp._size), _buffer(move(temp._buffer)) { // move constructor
      temp._buffer = nullptr;
      temp._size = 0;
   }

   Buffer& operator=(const Buffer& copy) { // copy assignment operator
      if (this != &copy) {
         _name = copy._name;
         if (_size != copy._size) {
            _buffer = nullptr;
            _size = copy._size;
            _buffer = (_size > 0)? new T[_size] : nullptr;
         }
         T* source = copy._buffer.get();
         T* dest = _buffer.get();
         copy(source, source + copy._size, dest);
      }
      return *this;
   }

   Buffer& operator=(Buffer&& temp) { // move assignment operator
      assert(this != &temp); // assert if this is not a temporary
      _buffer = nullptr;
      _size = temp._size;
      _buffer = move(temp._buffer);
      _name = move(temp._name);
      temp._buffer = nullptr;
      temp._size = 0;
      return *this;
	}	
};

template<typename T> Buffer<T> getBuffer(const string& name) {
   Buffer<T> b(name, 128);
   return b;
}

int main(){
   Buffer<int> b1;
   Buffer<int> b2("buf2", 64);
   Buffer<int> b3 = b2; //The copy constructor is called.
   Buffer<int> b4 = getBuffer<int>("buf4"); //вызываетс€ конструктор перемещени€. ѕричина Ч значение, возвращаемое функцией getBuffer() Ч rvalue. @ https://habrahabr.ru/post/182920/ //In solution explorer, right click the project, select "properties". The project property page will open. Expand the ">C/C++" entry in the tree on the left and select "Preprocessor" under that. The top entry in the right pane should be "Preprocessor Definitions". In that edit box, add _SCL_SECURE_NO_WARNINGS, separating it from the other entries with a ; //What does Уuse -D_SCL_SECURE_NO_WARNINGSФ mean? @ http://stackoverflow.com/questions/25046829/what-does-use-d-scl-secure-no-warnings-mean
   b1 = getBuffer<int>("buf5"); //вызвызываетс€ оператор присваивани€ перемещени€. ѕричина Ч значение, возвращаемое функцией getBuffer() Ч rvalue. @ https://habrahabr.ru/post/182920/ 
   //ERROR Buffer<int> b5;	b5 = b1; //copy assignment operator is called (there is an error in it);
	return 0;
}