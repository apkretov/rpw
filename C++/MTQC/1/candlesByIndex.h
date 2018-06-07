#pragma once
#include "datetime.h"

namespace mtqc {
	class candlesByIndex {
		const std::string cstrTag; //tag � ��������� ������������� ������� ��� ����������
		const int cintLine; //line � ����� ����� ������� ��� ����������.������ ����� ����� ����� 0
		const int cintCount; //count � ���������� ������������� ������.
		const int cintOffset; //The price offset given Alligator, otherwise = 0.

		lua_State* L;

		int cintT; //t � �������, ���������� ������������� ������. getCandlesByIndex @ QLUA.chm.
		int cintN; //n � ���������� ������ � ������� t.

		int cintBars;
		int iBars() const;
		void setBars();
		int getBars() const { return cintBars; }

		void setCandlesByIndex();
		void deleteCandlesByIndex();
		double OHLC(const std::string& strOHLC, int intShift) const;

	public:
		candlesByIndex(lua_State* L_, const std::string& strTag, int intLine, int intCount, int intOffset);
		~candlesByIndex();

		void refresh();
		int getN() const { return cintN; } //BACK: Incapsulate in in cpp.

		double getOpen(int intShift) const;
		double getHigh(int intShift) const;
		double getLow(int intShift) const;
		double getClose(int intShift) const;

		datetime getDatetime(int intShift) const;
	};
}