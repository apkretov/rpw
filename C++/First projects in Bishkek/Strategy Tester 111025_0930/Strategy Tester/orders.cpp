#include "StdAfx.h"
#include "orders.h"
#include "globals.h"

void Orders::refresh(double price) { // refresh the orders on a tick
	//for (size_t i = 0; i <= orders.size(); i++) {
	for (size_t i = 0; i < orders.size(); i++) {
		//Order const *order = &orders[i]; //the pointer to a current order
		//switch (order->getTypeOrder()) {
		//case OP_BUY:
		//	break;
		//}
		orders[i].refresh(price); // refresh on a tick
	}
}
