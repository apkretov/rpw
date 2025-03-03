#pragma once

#include <iostream>

namespace Smart_Pointers_and_Dumb_Classes {
	//ORIG struct destination; // represents what we are connecting to
	//ORIG struct connection; // information needed to use the connection
	struct destination {}; //MINE

	struct connection { //MINE
		connection() { 
			std::cout << "connection constructor\n";	
		}
		
		connection(const connection &c) : i(c.i) { 
			std::cout << "connection copy-constructor\n"; 
		}

		connection &operator=(const connection &c) { 
			i = c.i;
			std::cout << "copy-assignment operator\n"; 
			return *this;
		}

		connection(connection &&c) noexcept : i(c.i) { 
			std::cout << "connection move-constructor\n"; 
		}

		connection &operator=(connection &&c) noexcept { 
			i = c.i;
			std::cout << "move-assignment operator\n"; 
			return *this;
		}

		~connection() { 
			std::cout << "connection destructor\n"; 
		}

		int i{};
	}; 

	connection connect(destination *); // open the connection
	void disconnect(connection); // close the given connection
	void f1(destination &d);
}

namespace Using_Our_Own_Deletion_Code {
	void end_connection(Smart_Pointers_and_Dumb_Classes::connection *p);
	void f1(Smart_Pointers_and_Dumb_Classes::destination &d);
}
