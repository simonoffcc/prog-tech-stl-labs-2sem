#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include "iofmtguard.h"
#include "OtherStructures.h"

namespace simonenko {
	struct DataStruct {
		unsigned long long key1 = 0;
		std::complex<double> key2;
		std::string key3;
	};

	std::istream& operator>>(std::istream& in, DataStruct& dest);
	std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
	bool comparator(const DataStruct& left, const DataStruct& right);
}

#endif
