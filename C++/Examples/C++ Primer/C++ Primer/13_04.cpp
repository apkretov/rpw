#ifdef ON

#include <iostream>
#include <set>
#include "../../stdafx.h"
using namespace std;

#ifndef The_Message_Class
class Message {
	friend class Folder;
public: // folders is implicitly initialized to the empty set
	explicit Message(const string &str = "") : contents(str) {}
	Message(const Message &); // copy control to manage pointers to this Message // copy constructor
	Message &operator=(const Message &); // copy assignment
	~Message(); // destructor
	void save(Folder &); // add/remove this Message from the specified Folder’s set of messages
	void remove(Folder &);
	//ORIG private:
	string contents; // actual message text
	set<Folder *> folders; // Folders that have this Message
private: //MINE 
	void add_to_Folders(const Message &); // utility functions used by copy constructor, assignment, and destructor // add this Message to the Folders that point to the parameter
	void remove_from_Folders(); // remove this Message from every Folder in folders
};
#endif

class Folder {
	friend class Message;
public:
	void addMsg(Message *);
	void remMsg(Message *);
private:
	set<Message *> messages;
};

#ifndef The_save_and_remove_Members
void Message::save(Folder &f) {
	folders.insert(&f); // add the given Folder to our list of Folders
	f.addMsg(this); //TEST! //																																										add this Message to f’s set of Messages
}

void Message::remove(Folder &f) {
	folders.erase(&f); // take the given Folder out of our list of Folders
	f.remMsg(this); // remove this Message to f’s set of Messages
}
#endif

#ifndef Copy_Control_for_the_Message_Class
void Message::add_to_Folders(const Message &m) { // add this Message to Folders that point to m
	for (auto f : m.folders) //TEST! //																																								for each Folder that holds m
		f->addMsg(this); // add a pointer to this Message to that Folder
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
	add_to_Folders(m); // add this Message to the Folders that point to m
}
#endif

#ifndef The_Message_Destructor
void Message::remove_from_Folders() {
	for (auto f : folders) // for each pointer in folders
		f->remMsg(this); // remove this Message from that Folder
	folders.clear(); // no Folder points to this Message
}

Message::~Message() {
	remove_from_Folders();
}
#endif

#ifndef Message_Copy_Assignment_Operator
Message &Message::operator=(const Message &rhs) { // handle self-assignment by removing pointers before inserting them
	remove_from_Folders(); // update existing Folders
	contents = rhs.contents; // copy message contents from rhs
	folders = rhs.folders; // copy Folder pointers from rhs
	add_to_Folders(rhs); // add this Message to those Folders
	return *this;
}
#endif

#ifndef A_swap_Function_for_Message
void swap(Message &lhs, Message &rhs) { //TEST!
	using std::swap; // not strictly needed in this case, but good habit
	
	for (auto f : lhs.folders) // remove pointers to each Message from their (original) respective Folders
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	
	swap(lhs.folders, rhs.folders); // swap the contents and Folder pointer sets // uses swap(set&, set&)
	swap(lhs.contents, rhs.contents); // swap(string&, string&)
	
	for (auto f : lhs.folders) // add pointers to each Message to their (new) respective Folders
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
#endif

void Folder::addMsg(Message *m) {
	messages.insert(m);
}

void Folder::remMsg(Message *m) {
	messages.erase(m);
}

void mine() {
	Folder inbox;
	Folder outbox;
	
	Message m1("Message 1");
	m1.save(inbox);

	Message m2(m1);
	cout << "m1.contents: " << m1.contents << '\n';
	cout << "m2.contents: " << m2.contents << '\n';

	m2.remove(inbox);
	m2.save(outbox);
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	mine();

	return 0;
}
#endif
