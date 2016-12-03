/*

 Advent of Code 2016
 Day 1: No Time for a Taxicab

*/


#include <string>
#include <iostream>
#include <vector>

//#define DEBUG

/********************************************************
 ** Method to tokenize string based on string delimiter
 ********************************************************/
std::vector<std::string> split(std::string &s, const std::string delimiter)
{
	std::vector<std::string> vect;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		vect.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	vect.push_back(s);

	return vect;
}

/*******************************************************
 ** Person object
 *******************************************************/
class Person {
public:
	Person(int, bool);
	void Turn(std::string);
	void Move(int);

	int x, y;

private:
	bool HaveBeenHere();

	int direction;
	bool stopOnDuplicate;
	std::vector<std::pair<int, int>> locationHistory;

};

Person::Person(int d, bool stop)
{
	x = 0;
	y = 0;

	direction = d;
	stopOnDuplicate = stop;
}

//
// Turn in the specified direction
//
void Person::Turn(std::string turnDirection)
{
	if (turnDirection == "R") {
		#ifdef DEBUG 
			std::cout << "Turned right" << std::endl;
		#endif

		direction += 1;
	}
	else if (turnDirection == "L") {
		#ifdef DEBUG
			std::cout << "Turned left" << std::endl;
		#endif
		direction -= 1;
	}

	if (direction < 0) direction = 3;
	if (direction > 3) direction = 0;

	#ifdef DEBUG
		std::cout << "Direction: " << direction << std::endl;
	#endif
}

//
// Move blockCount blocks in the current facing direction
//
void Person::Move(int blockCount)
{
	for (int i = 0; i < blockCount; i++)
	{
		if (stopOnDuplicate == false || (stopOnDuplicate == true && HaveBeenHere() == false))
		{
			locationHistory.push_back(std::make_pair(x, y));

			if (direction == 0) y += 1;
			else if (direction == 1) x += 1;
			else if (direction == 2) y -= 1;
			else if (direction == 3) x -= 1;

		}
	}

	#ifdef DEBUG
		std::cout << "x: " << x << " y: " << y << std::endl;
	#endif
}

//
// Return if we've been here before
//
bool Person::HaveBeenHere()
{
	std::vector<std::pair<int, int>>::iterator it;

	for (it = locationHistory.begin(); it < locationHistory.end(); it++)
	{
		if (it->first == x && it->second == y) return true;
	}

	return false;
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string s = "L2, L3, L3, L4, R1, R2, L3, R3, R3, L1, L3, R2, R3, L3, R4, R3, R3, L1, L4, R4, L2, R5, R1, L5, R1, R3, L5, R2, L2, R2, R1, L1, L3, L3, R4, R5, R4, L1, L189, L2, R2, L5, R5, R45, L3, R4, R77, L1, R1, R194, R2, L5, L3, L2, L1, R5, L3, L3, L5, L5, L5, R2, L1, L2, L3, R2, R5, R4, L2, R3, R5, L2, L2, R3, L3, L2, L1, L3, R5, R4, R3, R2, L1, R2, L5, R4, L5, L4, R4, L2, R5, L3, L2, R4, L1, L2, R2, R3, L2, L5, R1, R1, R3, R4, R1, R2, R4, R5, L3, L5, L3, L3, R5, R4, R1, L3, R1, L3, R3, R3, R3, L1, R3, R4, L5, L3, L1, L5, L4, R4, R1, L4, R3, R3, R5, R4, R3, R3, L1, L2, R1, L4, L4, L3, L4, L3, L5, R2, R4, L2";
	std::string delimiter = ", ";

	std::vector<std::string> movements;

	Person me(0, true); // start facing North
	movements = split(s, delimiter);

	std::vector<std::string>::iterator it;
	for (it = movements.begin(); it < movements.end(); it++)
	{
		// Parse movement step
		std::string turnDirection = (*it).substr(0, 1);
		int blockCount = std::stoi((*it).substr(1, std::string::npos));

		// Perform movement
		me.Turn(turnDirection);
		me.Move(blockCount);
	}

	// Calculate shortest path
	int shortestPath = abs( me.x ) + abs( me.y );

	std::cout << "Shortest path: " << shortestPath << std::endl;

}