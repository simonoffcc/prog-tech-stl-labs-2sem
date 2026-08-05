#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main() {
	std::vector<simonenko::DataStruct> data;
	std::ifstream in("test.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			in.clear();
			std::copy(
				std::istream_iterator<simonenko::DataStruct>(in),
				std::istream_iterator<simonenko::DataStruct>(),
				std::back_inserter(data)
			);
		}
		std::sort(data.begin(), data.end(), simonenko::comparator);
		std::copy(
			std::begin(data),
			std::end(data),
			std::ostream_iterator<simonenko::DataStruct>(std::cout, "\n")
		);
	}
	else {
		std::cout << "file is not open";
	}
	return 0;
}
