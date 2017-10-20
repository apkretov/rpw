#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.
#include "fileCSV.h"
using std::string;
using std::ios;
#include <ctime> //The date/time functions.
using std::string;
using namespace mtqc;
#include "constants.h"
using namespace mtqc::constants;

//extern const string gstrMTQC;

fileCSV::fileCSV() {} 
fileCSV::fileCSV(const string& strFileName_, const string strHeader) { initialise(strFileName_, strHeader); } 

//fileCSV::~fileCSV() { cobjFile.close(); } 
//fileCSV::~fileCSV() {} //CHECKED: Do not delete this empty distructor!

//void fileCSV::open(const string& strFileName_, const string& strHeader) { 
//	using std::streamoff;
//	cstrFileName = gstrMTQC + " - " + strFileName_ + ".csv";
//	cobjFile.open(cstrFileName, ios::app); //Open the file in the append mode (ios::app).
//	
//	cobjFile.seekp(0, ios::end); //How to check if there isn't data in file to read @ http://stackoverflow.com/questions/17865180/how-to-check-if-there-isnt-data-in-file-to-read //basic_ostream Class @ https://msdn.microsoft.com/library/5baadc65-b662-4fab-8c9f-94457c58cda1.aspx#basic_ostream__tellp
//	streamoff lngPosition = cobjFile.tellp();
//	if (lngPosition == 0) addLine(strHeader, false); //Если файл еще пустой
//}

//void fileCSV::open(const string& strFileName_, const string& strHeader) { 
void fileCSV::initialise(const string& strFileName_, const string& strHeader) { 
	cstrFileName = gstrMTQC + " - " + strFileName_ + ".csv";
	
	std::ofstream objFile;
	objFile.open(cstrFileName, ios::app); //Open the file in the append mode (ios::app).
	
	objFile.seekp(0, ios::end); //How to check if there isn't data in file to read @ http://stackoverflow.com/questions/17865180/how-to-check-if-there-isnt-data-in-file-to-read //basic_ostream Class @ https://msdn.microsoft.com/library/5baadc65-b662-4fab-8c9f-94457c58cda1.aspx#basic_ostream__tellp
	std::streamoff lngPosition = objFile.tellp();
	objFile.close();
	if (lngPosition == 0) 
		addLine(strHeader, false); //Если файл еще пустой

	//cobjFile.close();
}

void fileCSV::addLine(const string& strLine, bool blnDatedTimed) { 
	std::ofstream objFile;
	objFile.open(cstrFileName, ios::app); //Open the file in the append mode (ios::app).

	if (!blnDatedTimed) 
		objFile << strLine << "\n"; // Добавляет строку
	else {
		time_t dtmRawtime; //Current date and time as string @ http://stackoverflow.com/questions/16357999/current-date-and-time-as-string
		struct tm* sttTimeinfo;
		const int intSize = 20;
		char chrBufferDate[intSize], chrBufferTime[intSize];
		time(&dtmRawtime);
		sttTimeinfo = localtime(&dtmRawtime);
		strftime(chrBufferDate, intSize, "%d.%m.%Y", sttTimeinfo);
		strftime(chrBufferTime, intSize, "%H:%M:%S", sttTimeinfo);
		objFile << chrBufferDate << "," << chrBufferTime << "," << strLine << "\n"; // Добавляет строку
	}	

	objFile.close();
}
