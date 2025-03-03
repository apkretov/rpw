#pragma once
#include "datetime.h"

namespace mtqc {
	class candlesByIndex {
		const std::string cstrTag; //tag Ц строковый идентификатор графика или индикатора
		const int cintLine; //line Ц номер линии графика или индикатора.ѕерва€ лини€ имеет номер 0
		const int cintCount; //count Ц количество запрашиваемых свечек.
		const int cintOffset; //The price offset given Alligator, otherwise = 0.

		lua_State* L;

		int cintT; //t Ц таблица, содержаща€ запрашиваемые свечки. getCandlesByIndex @ QLUA.chm.
		int cintN; //n Ц количество свечек в таблице t.

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