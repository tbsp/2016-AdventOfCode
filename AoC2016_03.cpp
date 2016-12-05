/*

 Advent of Code 2016
 Day 3: Squares With Three Sides

*/


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

//#define DEBUG

/********************************************************
 ** Method to split a string on char delimiter
 ** (source: http://stackoverflow.com/questions/236129/split-a-string-in-c/236803#236803)
 ********************************************************/
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

/********************************************************
 ** Method to read triangle input
 ********************************************************/
std::vector<std::vector<int>> readTriangles(std::string &fileName)
{
	std::vector<std::vector<int>> vect;

	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::vector<std::string> edges = split(line, ' ');
			std::vector<int> edgeInts;

			for (std::vector<std::string>::const_iterator i = edges.begin(); i != edges.end(); ++i)
				edgeInts.push_back(stoi(*i));

			vect.push_back(edgeInts);
		}
		myfile.close();
	}

#ifdef DEBUG
	std::cout << "Read " << vect.size() << " triangles." << std::endl;
#endif

	return vect;
}

//
// Reorganize triangles based on column ordering
//
std::vector<std::vector<int>> columnizeTriangles(std::vector<std::vector<int>> triangles)
{
	std::vector<std::vector<int>> columnTriangles;
	std::vector<int> tri1, tri2, tri3;

	std::vector<std::vector<int>>::iterator it;
	for (it = triangles.begin(); it < triangles.end(); it++)
	{
		tri1.push_back((*it)[0]);
		tri2.push_back((*it)[1]);
		tri3.push_back((*it)[2]);

		if (tri1.size() == 3)
		{
			columnTriangles.push_back(tri1);
			columnTriangles.push_back(tri2);
			columnTriangles.push_back(tri3);

			tri1.clear();
			tri2.clear();
			tri3.clear();
		}
	}

	return columnTriangles;
}

//
// Return how many of the triangles are possible
//
int checkTriangles(std::vector<std::vector<int>> triangles)
{
	int validTriangles = 0;

	std::vector<std::vector<int>>::iterator it;
	for (it = triangles.begin(); it < triangles.end(); it++)
	{
#ifdef DEBUG
		std::cout << (*it)[0] << " " << (*it)[1] << " " << (*it)[2] << ": ";
#endif
		if ((((*it)[0] + (*it)[1]) >(*it)[2]) &&
			(((*it)[0] + (*it)[2]) > (*it)[1]) &&
			(((*it)[1] + (*it)[2]) > (*it)[0]))
		{
			validTriangles += 1;
#ifdef DEBUG
			std::cout << "Valid" << std::endl;
#endif
		}
		else
		{
#ifdef DEBUG
			std::cout << "Invalid" << std::endl;
#endif
		}
	}

	return validTriangles;
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{
	// Read input file contents
	std::string fileName = "AoC2016_03_input.txt";
	std::vector<std::vector<int>> triangles = readTriangles(fileName);

	// Check triangles in part 1 format
	std::cout << "Valid triangles (part 1): " << checkTriangles(triangles) << std::endl;

	// Reorganize triangle data
	std::vector<std::vector<int>> columnTriangles = columnizeTriangles(triangles);

	// Check triangles in part 2 format
	std::cout << "Valid triangles (part 2): " << checkTriangles(columnTriangles) << std::endl;

	return 0;
}