#pragma once

#include "terminal.h"

namespace mtqc {
	namespace MT4QuikConnector {
		extern terminal gobjTerminal;

		void srvMessageToQuik(const char* const chrMessage);
		void keyPressedOperation(int intOperation);
}	}