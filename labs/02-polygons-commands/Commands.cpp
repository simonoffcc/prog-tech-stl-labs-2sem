#include "Commands.h"

double areaEven(const std::vector< Polygon >& polygons)
{
	double result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
		[](double res, const Polygon& polygon)
		{
			res += ((polygon.points.size() % 2 == 0) ? getArea(polygon) : 0.0);
			return res;
		}
	);
	return result;
}

double areaOdd(const std::vector< Polygon >& polygons)
{
	double result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
		[](double res, const Polygon& polygon)
		{
			res += ((polygon.points.size() % 2 == 1) ? getArea(polygon) : 0.0);
			return res;
		}
	);
	return result;
}

double areaMean(const std::vector< Polygon >& polygons)
{
	double areaOfAll = std::accumulate(polygons.begin(), polygons.end(), 0.0,
		[](double res, const Polygon& polygon)
		{ return res + getArea(polygon); }
	);
	return areaOfAll / polygons.size();
}

double areaVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes)
{
	double result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
		[numOfVertexes](double res, const Polygon& polygon)
		{
			res += (polygon.points.size() == numOfVertexes) ? getArea(polygon) : 0.0;
			return res;
		}
	);
	return result;
}

double maxArea(const std::vector< Polygon >& polygons)
{
	auto largest = std::max_element(
		polygons.begin(),
		polygons.end(),
		std::bind(
			std::less<double>(),
			std::bind(getArea, std::placeholders::_1),
			std::bind(getArea, std::placeholders::_2)
		)
	);
	return getArea(*largest);
}

size_t maxVertexes(const std::vector< Polygon >& polygons)
{
	auto largest = std::max_element(
		polygons.begin(),
		polygons.end(),
		std::bind(
			std::less<double>(),
			std::bind(getNumOfVertexes, std::placeholders::_1),
			std::bind(getNumOfVertexes, std::placeholders::_2)
		)
	);
	return getNumOfVertexes(*largest);
}

double minArea(const std::vector< Polygon >& polygons)
{
	auto smallest = std::min_element(
		polygons.begin(),
		polygons.end(),
		std::bind(
			std::less<double>(),
			std::bind(getArea, std::placeholders::_1),
			std::bind(getArea, std::placeholders::_2)
		)
	);
	return getArea(*smallest);
}

size_t minVertexes(const std::vector< Polygon >& polygons)
{
	auto smallest = std::min_element(
		polygons.begin(),
		polygons.end(),
		std::bind(
			std::less<double>(),
			std::bind(getNumOfVertexes, std::placeholders::_1),
			std::bind(getNumOfVertexes, std::placeholders::_2)
		)
	);
	return getNumOfVertexes(*smallest);
}

size_t countEven(const std::vector< Polygon >& polygons)
{
	return std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon)
		{ return polygon.points.size() % 2 == 0; });
}

size_t countOdd(const std::vector< Polygon >& polygons)
{
	return std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon)
		{ return polygon.points.size() % 2 == 1; });
}

size_t countNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes)
{
	return std::count_if(polygons.begin(), polygons.end(), [numOfVertexes](const Polygon& polygon)
		{ return polygon.points.size() == numOfVertexes; });
}

size_t echo(std::vector< Polygon >& polygons, Polygon argument)
{
	if (polygons.size() == 0)
	{
		return 0;
	}
	std::vector<Polygon> copies;
	std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(copies), [&argument](const Polygon& polygon)
		{ return polygon == argument; });
	size_t result = copies.size();
	if (result > 0)
	{
		std::vector<Polygon> newPolygons;
		std::transform(polygons.begin(), polygons.end(), std::back_inserter(newPolygons),
			[&argument, &newPolygons](Polygon& object)
			{
				if (object == argument)
				{
					newPolygons.push_back(object);
				}
				return object;
			});
		std::swap(polygons, newPolygons);
	}
	return result;
}

bool inFrame(const std::vector< Polygon >& polygons, Polygon argument)
{
	struct frame_t
	{
		int xMax;
		int xMin;
		int yMax;
		int yMin;
	};
	Point firstPoint = polygons[0].points[0];
	frame_t mainFrame
	{
		firstPoint.x_,
		firstPoint.x_,
		firstPoint.y_,
		firstPoint.y_
	};
	mainFrame = std::accumulate(polygons.begin(), polygons.end(), mainFrame,
		[](frame_t frame, const Polygon& polygon)
		{
			return std::accumulate(polygon.points.begin(), polygon.points.end(), frame,
				[](frame_t frame, const Point& point)
				{
					frame.xMax = std::max(frame.xMax, point.x_);
					frame.xMin = std::min(frame.xMin, point.x_);
					frame.yMax = std::max(frame.yMax, point.y_);
					frame.yMin = std::min(frame.yMin, point.y_);
					return frame;
				}
			);
		});

	return std::all_of(argument.points.begin(), argument.points.end(),
		[mainFrame](const Point& point)
		{return point.x_ >= mainFrame.xMin && point.x_ <= mainFrame.xMax && point.y_ >= mainFrame.yMin && point.y_ <= mainFrame.yMax;}
	);
}
