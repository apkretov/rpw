#pragma once

#ifdef Initializers_for_Data_Members_of_Class_Type

#include <string>
#include <vector>
#include "07_03_1_1.h"

#ifndef WINDOW_MGR_H__INITIALIZERS_FOR_DATA_MEMBERS_OF_CLASS_TYPE
#define WINDOW_MGR_H__INITIALIZERS_FOR_DATA_MEMBERS_OF_CLASS_TYPE

class Window_mgr__Initializers_for_Data_Members_of_Class_Type {
private:
	// Screens this Window_mgr is tracking
	// by default, a Window_mgr has one standard sized blank Screen
	std::vector<Screen__mutable_Data_Members> screens{Screen__mutable_Data_Members(24, 80, ' ')};
};
#endif
#endif