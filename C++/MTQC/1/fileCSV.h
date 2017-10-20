#pragma once //TO DO: Disassamble this class.
#include <fstream>

namespace mtqc{
	class fileCSV {
		std::string cstrFileName;
		//std::ofstream cobjFile;
	public:
		fileCSV();
		fileCSV(const std::string& strFileName_, const std::string strHeader);
		//~fileCSV();
		//void open(const std::string& strFileName_, const std::string& strHeader);
		void initialise(const std::string& strFileName_, const std::string& strHeader);
		void addLine(const std::string& strLine, bool blnDatedTimed);
};	}
