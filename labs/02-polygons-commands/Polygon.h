#ifndef POLYGON_H
#define POLYGON_H
#include "Point.h"
#include "OtherStructures.h"

#include <vector>
#include <algorithm>

struct Polygon
{
	std::vector< Point > points;
};

size_t getNumOfVertexes(const Polygon& polygon);
double getArea(const Polygon& polygon);

bool operator==(const Polygon& left, const Polygon& right);
std::istream& operator>>(std::istream& in, Polygon& dest);
std::ostream& operator<<(std::ostream& out, const Polygon& dest);

#endif
