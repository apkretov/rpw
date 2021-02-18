#pragma once
#include "order.h"
#include <vector>
using std::vector;

#ifndef ORDERS_H
#define ORDERS_H
class Orders {
	vector<Order> orders;
public:
	void Orders::add(const Order& order) {orders.push_back(order);} //add a created order
	int getCount(void) const {return orders.size();} //Returns market and pending orders count
	void refresh(double); // refresh the orders on a tick
};
#endif