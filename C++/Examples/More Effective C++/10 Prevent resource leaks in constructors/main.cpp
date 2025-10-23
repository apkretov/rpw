#include <list>
#include <memory>
#include <string>
using namespace std;

class Image { // for image data
public:
	Image(const string& imageDataFileName);
	//...
};

class AudioClip { // for audio data
public:
	AudioClip(const string& audioDataFileName);
	//...
};

class PhoneNumber { /*...*/ }; // for holding phone numbers

#ifdef ORIG
class BookEntry { // for each entry in the
public: // address book
	BookEntry(const string& name, const string& address = "", const string& imageFileName = "", const string& audioClipFileName = "");
	~BookEntry();
	void addPhoneNumber(const PhoneNumber& number); // phone numbers are added via this function
	//...
private:
	string theName; // person’s name
	string theAddress; // their address
	list<PhoneNumber> thePhones; // their phone numbers
	Image* theImage; // their image
	AudioClip* theAudioClip; // an audio clip from them
};

BookEntry::BookEntry(const string& name, const string& address, const string& imageFileName, const string& audioClipFileName) :
	theName(name),
	theAddress(address),
	theImage(0),
	theAudioClip(0) {
	if (imageFileName != "") {
		theImage = new Image(imageFileName);
	}
	if (audioClipFileName != "") {
		theAudioClip = new AudioClip(audioClipFileName);
	}
}

BookEntry::~BookEntry() {
	delete theImage;
	delete theAudioClip;
}

void testBookEntryClass_1() {
	BookEntry b("Addison-Wesley Publishing Company", "One Jacob Way, Reading, MA 01867");
	//...
}

void testBookEntryClass_2() {
	BookEntry* pb = 0;
	try {
		pb = new BookEntry("Addison-Wesley Publishing Company", "One Jacob Way, Reading, MA 01867");
		//...
	}
	catch (...) { // catch all exceptions
		delete pb; // delete pb when an exception is thrown
		throw; // propagate exception to caller
	}
	delete pb; // delete pb normally
}
#endif // ORIG

#ifndef PERPLEXITY //Example: Modern Revision. Meyers’ auto_ptr<Image> / auto_ptr<AudioClip> example would now be written as :
class BookEntry { 
public:
	BookEntry(string name, string address, string imageFileName, string audioClipFileName) :
		theName(move(name)),
		theAddress(move(address)),
		theImage(imageFileName.empty() ? nullptr : make_unique<Image>(imageFileName)),
		theAudioClip(audioClipFileName.empty() ? nullptr : make_unique<AudioClip>(audioClipFileName)) {
	}
private:
	string theName;
	string theAddress;
	unique_ptr<Image> theImage;
	unique_ptr<AudioClip> theAudioClip;
};
#endif // PERPLEXITY
