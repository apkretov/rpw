//TO DO: Disassamble this class.

#pragma once
#include <fstream>

namespace mtqc{

	class fileCSV {
		std::string cstrFileName;
	
	public:
		fileCSV();
		fileCSV(const std::string& strFileName_, const std::string strHeader);

		void initialise(const std::string& strFileName_, const std::string& strHeader);
		void addLine(const std::string& strLine, bool blnDatedTimed);
	};	
}
