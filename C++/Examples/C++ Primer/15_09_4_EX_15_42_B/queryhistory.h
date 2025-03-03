#ifndef _QUERYHISTORY_H
#define _QUERYHISTORY_H

#include <memory>
using std::shared_ptr;
#include <vector>
using std::vector;
#include "query.h"

class QueryHistory {
public:
	Query& operator[](size_t n)	{
		return *(query_vec[n]);
	}

	size_t add_query(const Query&); //return the assigned number of the  new query
private:
	vector<shared_ptr<Query>> query_vec;
};

#endif
