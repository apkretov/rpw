#pragma once
#include "enumerators.h"

namespace mtqc {
	class chartProperties {
	protected:
		enmDirec cintDirec;
		ENUM_TIMEFRAMES cintTimeFrame;
	public:
		enmDirec getDirec() const;
		virtual enmDirec setGetDirec(int intIdx) const;
		virtual enmDirec getSetSaveDirec(int intIdx) = 0;
		virtual bool time_frame_shift(ENUM_TIMEFRAMES intTimeFrame) { return (bool)enmDirec::direc_flat; } //shift the time frame; return true, if the new time frame works in accordance with the prior one
};	}
