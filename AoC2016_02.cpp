/*

Advent of Code 2016
Day 2: Bathroom Security

*/


#include <string>
#include <iostream>
#include <fstream>
#include <vector>

//#define DEBUG

/********************************************************
 ** Method to read keypad movement input
 ********************************************************/
std::vector<std::vector<char>> readMovements(std::string &fileName)
{
	std::vector<std::vector<char>> vect;

	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::vector<char> v(line.begin(), line.end());
			vect.push_back(v);
		}
		myfile.close();
	}

#ifdef DEBUG
	std::cout << "Read " << vect.size() << " rows of movements." << std::endl;
#endif

	return vect;
}


/*******************************************************
 ** Keypad object
 *******************************************************/
class Keypad {
public:
	Keypad(int);
	void Move(char);
	char getButton();

	int x, y;

private:
	bool isValidMove(int, int);

	int mapWidth;
	std::string buttonMap;
};

Keypad::Keypad(int keypadType)
{
	// A keypadType is defined by the width of the buttonMap and the 
	//  map itself. Entries of - are invalid locations, all other
	//  entries are possible button labels.

	if (keypadType == 0)
	{
		x = 2;
		y = 2;

		mapWidth = 5;
		buttonMap = "------123--456--789------";
	}
	else
	{
		x = 1;
		y = 3;

		mapWidth = 7;
		buttonMap = "----------1-----234---56789---ABC-----D----------";
	}
}

//
// Move in the specified direction
//
void Keypad::Move(char direction)
{
	if      (direction == 'U' && isValidMove(0,-1)) y -= 1;
	else if (direction == 'D' && isValidMove(0, 1)) y += 1;
	else if (direction == 'L' && isValidMove(-1, 0)) x -= 1;
	else if (direction == 'R' && isValidMove(1, 0)) x += 1;

#ifdef DEBUG
	std::cout << "x: " << x << " y: " << y << std::endl;
#endif
}

//
// Return which button the finger is over
//
char Keypad::getButton()
{
	return buttonMap[x + y * mapWidth];
}

//
// Return if the specified x/y offset is valid
//
bool Keypad::isValidMove(int xOff, int yOff)
{
	int newX = x + xOff;
	int newY = y + yOff;

#ifdef DEBUG
	std::cout << "Mask at " << newX << ", " << newY << ": " << buttonMap[newX + newY * mapWidth] << std::endl;
#endif

	if (buttonMap[newX + newY * mapWidth] == '-') return false;
	else return true;
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{

	// read input file contents
	std::string fileName = "AoC2016_02_input.txt";
	std::vector<std::vector<char>> movements = readMovements(fileName);

	Keypad myKeypad(1);
	std::vector<char> passcode;

	// loop through keypad steps, storing the button value after each stage
	std::vector<std::vector<char>>::iterator it;
	for (it = movements.begin(); it < movements.end(); it++)
	{
		for (int i = 0; i < (*it).size(); i++)
		{
			myKeypad.Move((*it)[i]);
		}

		// make a note of the button
		passcode.push_back(myKeypad.getButton());
	}

	std::cout << "Passcode: ";
	for (std::vector<char>::const_iterator i = passcode.begin(); i != passcode.end(); ++i)
	{
		std::cout << *i;
	}

}
