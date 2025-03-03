#pragma once

namespace mtqc {

	enum struct ENUM_TIMEFRAMES : int { 
		/*KTB PERIOD_CURRENT,*/ 
		PERIOD_TICK, 
		PERIOD_M1, 
		PERIOD_M5 = 5, 
		PERIOD_M15 = 15, 
		PERIOD_M30 = 30, 
		PERIOD_H1 = 60, 
		PERIOD_H4 = 240, 
		PERIOD_D1 = 1440, 
		PERIOD_W1 = 10080, 
		PERIOD_MN1 = 43200 
	};
	
	enum struct ENUM_POINTER_TYPE : int { 
		POINTER_INVALID, 
		POINTER_DYNAMIC
		/*KTB, POINTER_AUTOMATIC*/ 
	};
	
	//DO NOT CHANGE THE CONSTANTS W/O ADAPTING THE ALGORITHM!!!
	enum struct enmDirec : int { 
		direc_down = -1, 
		direc_flat, 
		direc_up
		/*, direc_trend*/ 
	}; 
	
	enum struct enmPhases : int { 
		phase_beginning, 
		phase_signal_appeared, 
		phase_signal_triggered, 
		/*
		phase_impulse_fixed, 
		phase_impulse_resumed, 
		phase_middle, 
		trade_closed, 
		phase_shifted,
		*/ 
		phase_end 
	};
	
	/*KTB 
	//Список констант для передачи в параметр interval функции CreateDataSource. //CreateDataSource @ QLUA.chm.
	enum enmInterval { 
		INTERVAL_TICK, 
		INTERVAL_M1, 
		INTERVAL_M2, 
		INTERVAL_M3 = 3, 
		INTERVAL_M4, 
		INTERVAL_M5, 
		INTERVAL_M6, 
		INTERVAL_M10 = 10, 
		INTERVAL_M15 = 15, 
		INTERVAL_M20 = 20, 
		INTERVAL_M30 = 30, 
		INTERVAL_H1 = 60, 
		INTERVAL_H2 = 120, 
		INTERVAL_H4 = 240, 
		INTERVAL_D1 = 1440, 
		INTERVAL_W1 = 10080, 
		INTERVAL_MN1 = 23200 //I doubt that this is correct. It seems to be PERIOD_MN1 = 43200.
	};
	*/
}