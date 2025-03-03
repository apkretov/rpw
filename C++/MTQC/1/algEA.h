#pragma once
#include "enumerators.h"
#include "trend.h"

namespace mtqc {
	namespace algEA {
		extern int JawsReverseRange;

		extern std::unique_ptr<trend> gobjTrend;

		double distance(double dblFrom, double dblTo, enmDirec intDirec);
		int distance_pts(double dblFrom, double dblTo, enmDirec intDirec);
		void OnTickAlg();
	}
}
