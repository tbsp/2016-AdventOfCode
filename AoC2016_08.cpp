/*

 Advent of Code 2016
 Day 8: Two-Factor Authentication

*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

//#define DEBUG

/********************************************************
 ** Method to read commands
 ********************************************************/
std::vector<std::string> readCommands(std::string &fileName)
{
	std::vector<std::string> vect;

	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vect.push_back(line);
		}
		myfile.close();
	}

#ifdef DEBUG
	std::cout << "Read " << vect.size() << " commands." << std::endl;
#endif

	return vect;
}


/********************************************************
 ** Screen object
 ********************************************************/
class Screen {
public:
	Screen(int, int);
	void ProcessCommand(std::string);
	int GetLitPixels();
	void Print();

private:
	void rectangle(int, int);
	void rotateColumn(int, int);
	void rotateRow(int, int);

	int w;
	int h;
	char* matrix;
};

Screen::Screen(int width, int height)
{
	w = width;
	h = height;
	matrix = new char[width * height];

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			matrix[i + j * w] = ' ';
}

//
// Process the specified command
//
void Screen::ProcessCommand(std::string command)
{
	if (command[1] == 'e')
	{
		std::size_t xPos = command.find("x");
		int width = stoi(command.substr(5, xPos - 5));
		int height = stoi(command.substr(xPos + 1, std::string::npos));

#ifdef DEBUG
		std::cout << "Rectangle " << width << " x " << height << std::endl;
#endif
		rectangle(width, height);
	}
	else if (command[7] == 'c')
	{
		std::size_t byPos = command.find(" by");
		int column = stoi(command.substr(16, byPos - 16));
		int steps = stoi(command.substr(byPos + 4, std::string::npos));

#ifdef DEBUG
		std::cout << "Column rotate: " << column << " by " << steps << std::endl;
#endif
		rotateColumn(column, steps);
	}
	else if (command[7] == 'r')
	{
		std::size_t byPos = command.find(" by");
		int row = stoi(command.substr(13, byPos - 13));
		int steps = stoi(command.substr(byPos + 4, std::string::npos));

#ifdef DEBUG
		std::cout << "Row rotate: " << row << " by " << steps << std::endl;
#endif
		rotateRow(row, steps);
	}
	else
		std::cout << "Unknown command: " << command << std::endl;
}

//
// Return the number of lit pixels
//
int Screen::GetLitPixels()
{
	int litPixels = 0;

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (matrix[i + j * w] == '*') litPixels++;

	return litPixels;
}

//
// Print the screen to the console
//
void Screen::Print()
{
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
			std::cout << matrix[i + j * w];
		std::cout << std::endl;
	}
}


//
// Light up a rectangle on the screen
//
void Screen::rectangle(int width, int height)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			matrix[i + j * w] = '*';
}

//
// Rotate a column on the screen
//
void Screen::rotateColumn(int column, int steps)
{
	// copy column to string
	std::string columnCopy = "";
	for (int j = 0; j < h; j++)
		columnCopy += matrix[column + j * w];

	int trueSteps = steps % h;
	std::rotate(columnCopy.rbegin(), columnCopy.rbegin() + trueSteps, columnCopy.rend());

	// copy string back to matrix
	for (int j = 0; j < h; j++)
		matrix[column + j * w] = columnCopy[j];
}

//
// Rotate a row on the screen
//
void Screen::rotateRow(int row, int steps)
{
	// copy row to string
	std::string rowCopy = "";
	for (int i = 0; i < w; i++)
		rowCopy += matrix[i + row * w];

	int trueSteps = steps % w;
	std::rotate(rowCopy.rbegin(), rowCopy.rbegin() + trueSteps, rowCopy.rend());

	// copy string back to matrix
	for (int i = 0; i < w; i++)
		matrix[i + row * w] = rowCopy[i];
}

/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string fileName = "AoC2016_08_input.txt";
	std::vector<std::string> commands = readCommands(fileName);

	Screen myScreen(50, 6);

	for (auto itr : commands)
		myScreen.ProcessCommand(itr);

	std::cout << "Lit pixel count (part 1): " << myScreen.GetLitPixels() << std::endl;

	myScreen.Print();

	return 0;
}
