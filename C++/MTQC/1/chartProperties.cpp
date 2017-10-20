#include "chartProperties.h"
using namespace mtqc;

/*inline*/ enmDirec chartProperties::getDirec() const { return cintDirec; }
/*inline*/ enmDirec chartProperties::setGetDirec(int intIdx) const { return enmDirec::direc_down; }
//bool time_frame_shift(ENUM_TIMEFRAMES intTimeFrame) { return direc_flat; } //shift the time frame; return true, if the new time frame works in accordance with the prior one +
