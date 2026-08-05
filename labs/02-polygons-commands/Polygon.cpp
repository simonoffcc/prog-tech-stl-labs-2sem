#include "Polygon.h"

size_t getNumOfVertexes(const Polygon& polygon)
{
	return polygon.points.size();
}

double getArea(const Polygon& polygon)
{
	size_t n = polygon.points.size();
	double area = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		size_t j = (i + 1) % n;
		area += polygon.points[i].x_ * polygon.points[j].y_;
		area -= polygon.points[j].x_ * polygon.points[i].y_;
	}
	area = std::abs(area) / 2.0;
	return area;
}

bool operator==(const Polygon& left, const Polygon& right)
{
	if (left.points.size() == right.points.size())
	{
		auto iterator = std::mismatch(left.points.begin(), left.points.end(),
			right.points.begin(), right.points.end(), isEqualPoint);
		return (iterator.first == left.points.end());
	}
	else
	{
		return false;
	}
}

std::istream& operator>>(std::istream& in, Polygon& dest)
{
	std::istream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	Polygon input;
	size_t numberOfPoints = 0;
	size_t count = 0;
	in >> numberOfPoints;
	if (numberOfPoints < 1)
	{
		in.setstate(std::ios::failbit);
	}
	for (size_t i = 0; i < numberOfPoints && in; i++)
	{
		Point point;
		in >> PointIO{ point };
		if (in)
		{
			count++;
			input.points.push_back(point);
		}
	}
	if (in && count == numberOfPoints)
	{
		dest = input;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& src)
{
	std::ostream::sentry sentry(out);
	if (!sentry)
	{
		return out;
	}
	iofmtguard fmtguard(out);
	out << src.points.size() << " ";
	for (size_t i = 0; i < src.points.size(); i++)
	{
		out << "(" << src.points[i].x_ << ";" << src.points[i].y_ << ") ";
	}
	return out;
}
