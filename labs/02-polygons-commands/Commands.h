#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.h"

#include <functional>
#include <numeric>

double areaEven(const std::vector< Polygon >& polygons);
double areaOdd(const std::vector< Polygon >& polygons);
double areaMean(const std::vector< Polygon >& polygons);
double areaVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
double maxArea(const std::vector< Polygon >& polygons);
size_t maxVertexes(const std::vector< Polygon >& polygons);
double minArea(const std::vector< Polygon >& polygons);
size_t minVertexes(const std::vector< Polygon >& polygons);
size_t countEven(const std::vector< Polygon >& polygons);
size_t countOdd(const std::vector< Polygon >& polygons);
size_t countNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
size_t echo(std::vector< Polygon >& polygons, Polygon argument);
bool inFrame(const std::vector< Polygon >& polygons, Polygon argument);
void doCommands(std::vector< Polygon >& polygons, std::istream& in);

#endif
