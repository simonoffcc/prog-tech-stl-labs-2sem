#ifndef OTHERSTRUCTURES_H
#define OTHERSTRUCTURES_H
#include <string>
#include <complex>
#include <iostream>

namespace simonenko {
	struct DelimeterIO {
	public:
		explicit DelimeterIO(char exp);
		friend std::istream& operator>>(std::istream& in, DelimeterIO&& dest);

	private:
		char exp_;
	};

	struct LabelIO {
	public:
		explicit LabelIO(std::string exp);
		friend std::istream& operator>>(std::istream& in, LabelIO&& dest);

	private:
		std::string exp_;
	};

	struct StringIO {
	public:
		explicit StringIO(std::string& ref);
		friend std::istream& operator>>(std::istream& in, StringIO&& dest);

	private:
		std::string& ref_;
	};

	struct UllOctIO {
	public:
		explicit UllOctIO(unsigned long long& ref);
		friend std::istream& operator>>(std::istream& in, UllOctIO&& dest);

	private:
		unsigned long long& ref_;
	};

	struct ComplexIO {
	public:
		explicit ComplexIO(std::complex<double>& ref);
		friend std::istream& operator>>(std::istream& in, ComplexIO&& dest);

	private:
		std::complex<double>& ref_;
	};

	std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
	std::istream& operator>>(std::istream& in, LabelIO&& dest);
	std::istream& operator>>(std::istream& in, StringIO&& dest);
	std::istream& operator>>(std::istream& in, UllOctIO&& dest);
	std::istream& operator>>(std::istream& in, ComplexIO&& dest);
}

#endif
