#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week1/06%20Programming%20Assignment

#include "1_EX_06 ��������� ������ � ���� ������ 1.h"
#include "1_EX_06 ��������� ������ � ���� ������ 2.h"
#include "../../stdafx.h"

int main() {
	PRINT_FILE_LINE();
	TestRunner tr;
	{
		LOG_DURATION("All tests");
		RUN_TEST(tr, TestRangeBoundaries);
		RUN_TEST(tr, TestSameUser);
		RUN_TEST(tr, TestReplacement);
	}

	return 0;
}
#endif //1

/*
��������� ������ � ���� ������

����� �� ��������� ������ ��������� ������� ����� �� ������ ����. ��� ����� �������������� ��������������� ��������� ������, ���������� �����, ��� ���������� ���������� ��������� (secondary index). ���������� ����� ��������� ��� ������ ���� Record ����:

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

class Database {
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;
};

����������:

	�������� Put ������ ���������� true, ���� ������� �������, � false, ���� ������� �� �������, ������ ��� � ���� ������ ��� ���� ������ � ����� �� id. � ��������� ������ ��������� ���� ������ �� ������ ��������.

	�������� GetById ������ ���������� nullptr, ���� � ���� ������ ��� ������ � ��������� id.

	�������� Erase ������ ���������� true, ���� ������� ������� ������� � �������� id, � false, ���� ������� � �������� id �� ��� ������. � ��������� ������ ��������� ���� ������ �� ������ ��������.

	�������� RangeByTimestamp, RangeByKarma � AllByUser ��������� ������� callback. ���������������, ��� �� ����� �������� (), ����������� � �������� ��������� ������ ���� Record � ������������ bool.

	�������� RangeByTimestamp ������ �������� ��� ������, � ������� ���� timestamp ��������� � ��������� [low, high] (��� ������� ��������), � ��� ������ �� ��� ���� ��� �������� callback. ���� ��������� ����� callback ������ false, �������� ������������.

	�������� RangeByKarma ������ �������� ��� ������, � ������� ���� karma ��������� � ��������� [low, high].

	�������� AllByUser ������ �������� ��� ������ � ��������� ������, � ������� ���� user ����� �������� ��������� user.

	��� ��, ��� � RangeByTimestamp, ������ RangeByKarma � AllByUser ������ �������� callback ��� ������ ������, �� ������� ��� �����������, � ���������� ��������, ���� callback ������ false.

	�������� callback ��������� ��������� ��������� ������: �� ������ ���������� true, ���� ��������� ���������� ����� ��������� �������, � false � ��������� ������. ��������, ��� �������� ������� ������ 10 ������� ��� ����� ������ ������, ��������������� ��������������� ��������.

	����� ���������� ���� �������� ������ ����� � ������� ����������� (��������, ����������� ��� ���������������) ����������� �� ������ ����� ������� � ���� ������.

	��� ������� ���������� - �������������, [low, high] � ��� �������� ������������� ������������ ������, ���������, ��� � ������� ���� �������� ������� ���� x < high, x > low, x = x_0.

	��� ������� ���� ������ �� ������ �������, ��� bad_alloc �������� �� �����.

����������
� ���� ������ ����� ��������� ������� ��������� multimap. �� �� ������������� ��� � �������, ������ ��� �� �������� ����� � �� ����������� � �� ���������� �� �������� map ������ ���, ��� ����� ������� ������������� �����.
*/
