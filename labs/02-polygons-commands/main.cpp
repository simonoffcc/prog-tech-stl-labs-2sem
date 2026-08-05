#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <iomanip>
#include "Polygon.h"
#include "OtherStructures.h"
#include "Commands.h"

void doCommands(std::vector< Polygon >&, std::istream&);

int main()
{
	std::string line;
	std::stringstream streamLine;
	std::vector< Polygon > data;

	std::string fileName;
	std::cout << "Enter file name: ";
	std::cin >> fileName;

	std::ifstream figures(fileName);
	if (!figures.is_open()) {
		std::cerr << "\nNo such file in directory.\n";
		return -1;
	}

	while (!figures.eof())
	{
		std::getline(figures, line);
		streamLine.clear();
		streamLine << line;
		Polygon polygon;
		streamLine >> polygon;
		if (streamLine)
		{
			data.push_back(polygon);
		}
		else
		{
			streamLine.clear();
			streamLine.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::cout << "\n=================Shapes===================\n";
	std::copy(
		std::begin(data),
		std::end(data),
		std::ostream_iterator< Polygon >(std::cout, "\n")
	);

	std::ifstream commands("commands.txt");
	if (!commands.is_open()) {
		std::cerr << "Error opening a file with commands.\n";
		return -1;
	}

	std::cout << "\n=================Commands=================\n";

	iofmtguard guard(std::cout);
	std::cout << std::fixed << std::setprecision(1);
	while (!commands.eof())
	{
		try {
			doCommands(data, commands);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what() << "\n";
			commands.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	std::cout << "\n=================Result===================\n";
	std::copy(
		std::begin(data),
		std::end(data),
		std::ostream_iterator< Polygon >(std::cout, "\n")
	);

	return 0;
}

void doCommands(std::vector< Polygon >& polygons, std::istream& in)
{
	std::string command;
	in >> command;
	if (command == "AREA")
	{
		std::string argument;
		in >> argument;
		if (argument == "EVEN")
		{
			std::cout << "AREA EVEN: " << areaEven(polygons) << '\n';
		}
		else if (argument == "ODD")
		{
			std::cout << "AREA ODD: " << areaOdd(polygons) << '\n';
		}
		else if (argument == "MEAN")
		{
			if (polygons.size() == 0)
			{
				throw std::invalid_argument("NOT ENOUGH FIGURES TO GET MEAN AREA\n");
			}
			std::cout << "AREA MEAN: " << areaMean(polygons) << '\n';
		}
		else
		{
			size_t vertexes = 0;
			try
			{
				vertexes = std::stoull(argument);
			}
			catch (...)
			{
				throw std::invalid_argument("INVALID COMMAND");
			}
			std::cout << "AREA " << vertexes << ": " << areaVertexes(polygons, vertexes) << '\n';
		}
	}
	else if (command == "MAX")
	{
		if (polygons.size() == 0)
		{
			throw std::invalid_argument("NOT ENOUGH FIGURES TO GET MAX\n");
		}
		std::string argument;
		in >> argument;
		if (argument == "AREA")
		{
			std::cout << "MAX AREA: " << maxArea(polygons) << '\n';
		}
		else if (argument == "VERTEXES")
		{
			std::cout << "MAX VERTEXES: " << maxVertexes(polygons) << '\n';
		}
		else
		{
			throw std::invalid_argument("INVALID COMMAND");
		}
	}
	else if (command == "MIN")
	{
		if (polygons.size() == 0)
		{
			throw std::invalid_argument("NOT ENOUGH FIGURES TO GET MIN\n");
		}
		std::string argument;
		in >> argument;
		if (argument == "AREA")
		{
			std::cout << "MIN AREA: " << minArea(polygons) << '\n';
		}
		else if (argument == "VERTEXES")
		{
			std::cout << "MIN VERTEXES: " << minVertexes(polygons) << '\n';
		}
		else
		{
			throw std::invalid_argument("INVALID COMMAND");
		}
	}
	else if (command == "COUNT")
	{
		std::string argument;
		in >> argument;
		if (argument == "EVEN")
		{
			std::cout << "COUNT EVEN: " << countEven(polygons) << '\n';
		}
		else if (argument == "ODD")
		{
			std::cout << "COUNT ODD: " << countOdd(polygons) << '\n';
		}
		else
		{
			size_t vertexes = 0;
			try
			{
				vertexes = std::stoull(argument);
			}
			catch (...)
			{
				throw std::invalid_argument("INVALID COMMAND");
			}
			std::cout << "COUNT " << vertexes << ": " << countNumOfVertexes(polygons, vertexes) << '\n';
		}
	}
	else if (command == "ECHO")
	{
		Polygon argument;
		in >> argument;
		if (!in)
		{
			throw std::invalid_argument("INVALID COMMAND");
		}
		std::cout << "ECHO  " << argument << ": " << echo(polygons, argument) << '\n';
	}
	else if (command == "INFRAME")
	{
		if (polygons.size() == 0)
		{
			throw std::invalid_argument("NOT ENOUGH FIGURES TO GET FRAME\n");
		}
		Polygon argument;
		in >> argument;
		if (!in)
		{
			throw std::invalid_argument("INVALID COMMAND");
		}
		std::cout << "INFRAME  " << argument << ": " << (inFrame(polygons, argument) ? "<TRUE>" : "<FALSE>") << '\n';
	}
	else
	{
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
