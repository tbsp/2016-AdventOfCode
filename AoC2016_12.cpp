/*

 Advent of Code 2016
 Day 12: Leonardo's Monorail

*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

//#define DEBUG

/********************************************************
 ** Method to read instructions
 ********************************************************/
std::vector<std::string> readInstructions(std::string &fileName)
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
	std::cout << "Read " << vect.size() << " instructions." << std::endl;
#endif

	return vect;
}



/********************************************************
 ** CPU object
 ********************************************************/
class CPU {
public:
	CPU();
	CPU(int, int, int, int);
	int Execute(std::string);
	std::map<char, int> registers;

private:
};

CPU::CPU()
{
	registers['a'] = 0;
	registers['b'] = 0;
	registers['c'] = 0;
	registers['d'] = 0;
}

CPU::CPU(int a, int b, int c, int d)
{
	registers['a'] = a;
	registers['b'] = b;
	registers['c'] = c;
	registers['d'] = d;
}

//
// Execute an instruction and return a jump offset, if any
//
int CPU::Execute(std::string instruction)
{
	if (instruction.find("cpy") != std::string::npos)
	{
		if (registers.find(instruction[4]) != registers.end())
			registers[instruction.back()] = registers[instruction[4]];
		else
			registers[instruction.back()] = stoi(instruction.substr(4, instruction.size() - 1));
	}
	else if (instruction.find("inc") != std::string::npos)
	{
		registers[instruction.back()]++;
	}
	else if (instruction.find("dec") != std::string::npos)
	{
		registers[instruction.back()]--;
	}
	else if (instruction.find("jnz") != std::string::npos)
	{
		char source = instruction[4];
		int baseValue = 0;

		if (registers.find(source) != registers.end()) baseValue = registers[source];
		else baseValue = source - '0';

		if (baseValue != 0)
			return stoi(instruction.substr(6, instruction.size() - 1));
	}
	else
	{
		std::cout << "Unrecognized instruction: " << instruction << std::endl;
	}

#ifdef DEBUG
	std::cout << "a: " << registers['a'] << ", b: " << registers['b'] << ", c: " << registers['c'] << ", d: " << registers['d'] << std::endl;
#endif
	return 0;
}


/********************************************************
 ** Execute a list of instructions on the specified CPU
 ********************************************************/
void ExecuteInstructions(CPU& myCPU, std::vector<std::string> instructions)
{
	int jumpOffset;
	std::vector<std::string>::iterator itr;

	for (itr = instructions.begin(); itr < instructions.end(); itr++)
	{
		jumpOffset = myCPU.Execute(*itr);
		if (jumpOffset != 0)
			itr += (jumpOffset - 1);
	}
}

/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string fileName = "AoC2016_12_input.txt";
	std::vector<std::string> instructions = readInstructions(fileName);

	CPU myCPU;

	ExecuteInstructions(myCPU, instructions);
	std::cout << "Part 1: " << myCPU.registers['a'] << std::endl;

	CPU myCPU2(0, 0, 1, 0);

	ExecuteInstructions(myCPU2, instructions);
	std::cout << "Part 2: " << myCPU2.registers['a'] << std::endl;

	return 0;
}