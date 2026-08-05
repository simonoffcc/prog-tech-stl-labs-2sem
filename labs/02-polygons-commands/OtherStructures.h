#ifndef OTHERSTRUCTURES_H
#define OTHERSTRUCTURES_H
#include "Point.h"
#include "iofmtguard.h"

struct DelimiterIO
{
	public:
		explicit DelimiterIO(char exp);
		friend std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

	private:
		char exp_;
};

struct PointIO
{
	public:
		explicit PointIO(Point& ref);
		friend std::istream& operator>>(std::istream& in, PointIO&& dest);
	private:
		Point& ref_;
};

std::istream& operator>>(std::istream&, DelimiterIO&&);
std::istream& operator>>(std::istream&, PointIO&&);

#endif
