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

#pragma region Perplexity
class BookEntry { //Example: Modern Revision. Meyers’ auto_ptr<Image> / auto_ptr<AudioClip> example would now be written as :
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
#pragma endregion //Perplexity
