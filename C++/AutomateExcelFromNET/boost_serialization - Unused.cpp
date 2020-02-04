#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <sstream>
//#include <string>

namespace boost_serialization {
	//void save(int i = 1) {
	//template <typename T> void save(T var = 1) {
	template <typename T> void save(T var) {
	  std::ofstream file{"archive.txt"};
	  boost::archive::text_oarchive oa{file};
	  //int i = 1;
	  //oa << i;
	  oa << var;
	}

	void save2(std::wstring str) {
	  std::ofstream file{"archive.txt"};
	  boost::archive::text_oarchive oa{file};
	  //int i = 1;
	  //oa << i;
	  oa << str;
	}

	template <typename T> void load(T& var) {
	  std::ifstream file{"archive.txt"};
	  boost::archive::text_iarchive ia{file};
	  //int i = 0;
	  //ia >> i;
	  ia >> var;
	}

	////stringstream ss;
	//
	////class animal {
	//struct animal {
	//	int legs_;
	//	int weight_ = 100; //TEST
	//	friend class boost::serialization::access;
	//	template <typename Archive> void serialize(Archive &ar, const unsigned int version) { ar & legs_; }
	//	//public:
	//	//	animal() = default;
	//	//	animal(int legs) : legs_{ legs } {}
	//	//	int legs() const { return legs_; }
	//	//	int weight() const { return weight_; } //TEST
	//};
	//
	//void saveStruct() {
	//	//boost::archive::text_oarchive oa{ ss };
	//	std::ofstream file{ "archive.txt" };
	//	boost::archive::text_oarchive oa{ file };
	//	/////////////animal *a = new animal{ 4 };
	//
	//	/////////////oa << a;
	//	/////////////delete a;
	//}
	//
	//void loadStruct() {
	//	//boost::archive::text_iarchive ia{ ss };
	//	std::ifstream file{ "archive.txt" };
	//	boost::archive::text_iarchive ia{ file };
	//	animal *a;
	//	ia >> a;
	//	delete a;
	//}
}