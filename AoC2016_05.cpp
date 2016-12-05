/*

 Advent of Code 2016
 Day 5: How About a Nice Game of Chess?

*/

// Use the RSA Data Security, Inc. MD5 Message-Digest Algorithm
#include "md5.h"

#include <string>
#include <iostream>
#include <vector>
#include <ctime>

#define DEBUG


//
// Calculate and return the door password
//
std::string getDoorPassword(std::string doorId, bool usePosition)
{
	int i = 0;
	int j = 0;

	std::string password("________");
	std::string hashString;
	std::string md5hash("fffff"); // sneak into the while loop

	while (j < 8)
	{
		while (md5hash.substr(0, 5) != "00000")
		{
			hashString = doorId + std::to_string(i);
			md5hash = md5(hashString);

			i++;
		}

		if (usePosition == false)
		{
			password[j] = md5hash.at(5);
			j += 1;

#ifdef DEBUG
			std::cout << "Hash string: " << hashString << " Hash: " << md5hash << ", Password: " << password << std::endl;
#endif
		}
		else
		{
			int insertIndex = md5hash.at(5) - '0';
			if ((insertIndex < 8) && (password[insertIndex] == '_'))
			{
				password[insertIndex] = md5hash.at(6);
				j += 1;

#ifdef DEBUG
				std::cout << "Hash string: " << hashString << " Hash: " << md5hash << ", Password: " << password << std::endl;
#endif
			}
		}

		md5hash = "fffff"; // sneak into the while loop... again
	}

	return password;
}



/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string doorId = "ojvtpuvg";

	clock_t begin = clock();

	std::cout << "Password (part 1): " << getDoorPassword(doorId, false) << std::endl;

	clock_t end1 = clock();

	std::cout << "Password (part 2): " << getDoorPassword(doorId, true) << std::endl;

	clock_t end2 = clock();

	double elapsedPart1 = double(end1 - begin) / CLOCKS_PER_SEC;
	double elapsedPart2 = double(end2 - end1) / CLOCKS_PER_SEC;

	std::cout << "Part 1 in " << elapsedPart1 << " seconds, part 2 in " << elapsedPart2 << " seconds." << std::endl;

	return 0;
}