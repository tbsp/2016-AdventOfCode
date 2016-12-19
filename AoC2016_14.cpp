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
#include <map>
#include <algorithm>

#define DEBUG


//
// Return the char of the first triplet in the string, or 'N' if none exists
//
char getFirstTripletChar(std::string s)
{
	char lastChar = NULL;
	int counter = 1;

	for (auto itr : s)
	{
		if (lastChar != NULL)
		{
			if (itr == lastChar)
			{
				counter++;
				if (counter == 3) return lastChar;
			}
			else
			{
				counter = 1;
			}
		}
		lastChar = itr;
	}
	return 'N';
}

//
// Return if the specified character is repeated 5 times in the string
//
bool hasQuiplet(std::string s, char c)
{
	char lastChar = NULL;
	int counter = 1;

	for (auto itr : s)
	{
		if (lastChar != NULL)
		{
			if (itr == c && itr == lastChar)
			{
				counter++;
				if (counter == 5) return true;
			}
			else
			{
				counter = 1;
			}
		}
		lastChar = itr;
	}
	return false;
}

/********************************************************
 ** Return the vector of keys
 ********************************************************/
std::vector<std::pair<int, std::string>> GetKeys(std::string salt, int md5repeats)
{
	std::string hashString;
	std::string md5hash;

	int index = 0;
	std::map<std::pair<int, char>, int> counters;
	std::map<std::pair<int, char>, std::string> candidates;

	std::vector<std::pair<int, std::string>> keys;

	do
	{
		hashString = salt + std::to_string(index);
		md5hash = md5(hashString);
		std::transform(md5hash.begin(), md5hash.end(), md5hash.begin(), ::tolower);

		// repeat hashing as requested
		if (md5repeats > 0)
		{
			for (int i = 0; i < md5repeats; i++)
			{
				md5hash = md5(md5hash);
				std::transform(md5hash.begin(), md5hash.end(), md5hash.begin(), ::tolower);
			}
		}

		// check existing key candidates
		for (auto itr = counters.begin(); itr != counters.cend(); )
		{
			if (hasQuiplet(md5hash, (*itr).first.second))
			{
				keys.push_back(std::make_pair((*itr).first.first, candidates[(*itr).first]));
#ifdef DEBUG
				//std::cout << "Found quiplet of " << (*itr).first.second << " at " << index << std::endl;
				std::cout << "Found key " << keys.size() << " at index " << (*itr).first.first << " (" << candidates[(*itr).first] << ")" << std::endl;
#endif	
				candidates.erase((*itr).first);
			}
			(*itr).second--;

			if ((*itr).second == 0) counters.erase(itr++);
			else ++itr;
		}

		// look for new candidates
		char tripleChar = getFirstTripletChar(md5hash);
		if (tripleChar != 'N')
		{
#ifdef DEBUG
			//std::cout << "Found triplet of " << tripleChar << " at " << index << std::endl;
#endif
			counters[std::make_pair(index, tripleChar)] = 1000;
			candidates[std::make_pair(index, tripleChar)] = md5hash;
		}

		index++;

	} while (keys.size() < 64);

	return keys;
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string salt = "yjdafjpo";

	std::vector<std::pair<int, std::string>> keys;

	clock_t begin = clock();

	keys = GetKeys(salt, 0);

	std::cout << "64th key index (part 1): " << keys[63].first << std::endl;

	clock_t end1 = clock();

	keys = GetKeys(salt, 2016);

	std::cout << "64th key index (part 2): " << keys[63].first << std::endl;

	clock_t end2 = clock();

	double elapsedPart1 = double(end1 - begin) / CLOCKS_PER_SEC;
	double elapsedPart2 = double(end2 - end1) / CLOCKS_PER_SEC;

	std::cout << "Part 1 in " << elapsedPart1 << " seconds, part 2 in " << elapsedPart2 << " seconds." << std::endl;
 
	return 0;
}
