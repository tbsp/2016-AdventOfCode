/*

 Advent of Code 2016
 Day 9: Explosives in Cyberspace

*/

#include <string>
#include <fstream>
#include <iostream>

//#define DEBUG

/********************************************************
 ** Method to calculate the decompressed length
 ********************************************************/
int getDecompressedLength(std::string &fileName)
{
	int decompressedLength = 0;

	char ch;
	bool inMarker = false;
	std::string intInProgress = "";
	int length;
	int skipCount = 0;

	std::ifstream fin(fileName, std::fstream::in);
	while (fin >> ch)
	{
		if (skipCount > 0)
		{
			skipCount--;
		}
		else if (ch == '(' && !inMarker) inMarker = true;
		else if (ch == ')' && inMarker)
		{
#ifdef DEBUG
			std::cout << "Compressed block: " << length << " x " << intInProgress << std::endl;
#endif
			skipCount = length;
			decompressedLength += (length * stoi(intInProgress));
			intInProgress = "";
			inMarker = false;
		}
		else if (inMarker && ch == 'x') {
			length = stoi(intInProgress);
			intInProgress = "";
		}
		else if (inMarker) intInProgress += ch;
		else decompressedLength++;
	}

	return decompressedLength;
}

//
// Recursively process 'charCount' characters in the input and return the decompressed length scaled by the multiplier
//
unsigned long long getDecompressedSegmentLength(std::ifstream& fin, int charCount, int multiplier, int& recursionDepth)
{
	recursionDepth++;

	unsigned long long  decompressedLength = 0;

	char ch;
	bool inMarker = false;
	std::string intInProgress = "";
	int length;

	while (charCount > 0 && fin >> ch)
	{
		if (ch == '(' && !inMarker) inMarker = true;
		else if (ch == ')' && inMarker)
		{
#ifdef DEBUG
			std::cout << std::string(recursionDepth, '*') << " Compressed block: " << length << " x " << intInProgress << std::endl;
#endif
			decompressedLength += getDecompressedSegmentLength(fin, length, stoi(intInProgress), recursionDepth);
			charCount -= length;
			intInProgress = "";
			inMarker = false;
		}
		else if (inMarker && ch == 'x') {
			length = stoi(intInProgress);
			intInProgress = "";
		}
		else if (inMarker) intInProgress += ch;
		else decompressedLength++;

		charCount--;
	}

#ifdef DEBUG
	std::cout << std::string(recursionDepth, '*') << " Substep: " << decompressedLength << " x " << multiplier << " = " << decompressedLength * multiplier << std::endl;
#endif

	recursionDepth--;

	return decompressedLength * multiplier;
}

/********************************************************
 ** Method to calculate the decompressed length V2
 ********************************************************/
unsigned long long getDecompressedLengthV2(std::string &fileName)
{
	int recursionDepth = 0;

	std::ifstream fin(fileName, std::fstream::in);
	return getDecompressedSegmentLength(fin, 999999999, 1, recursionDepth);
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string fileName = "AoC2016_09_input.txt";

	std::cout << "Decompressed length (part 1): " << getDecompressedLength(fileName) << std::endl;
	std::cout << "Decompressed length (part 2): " << getDecompressedLengthV2(fileName) << std::endl;

	return 0;
}