#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <ctime>

#define DEBUG

/********************************************************
** Method to read messages
********************************************************/
std::vector<std::string> readMessages(std::string &fileName)
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
	std::cout << "Read " << vect.size() << " messages." << std::endl;
#endif

	return vect;
}

/********************************************************
** Return the error-corrected message
********************************************************/
std::string correctMessage(std::vector<std::string> messages, bool sortMax)
{
	std::string message;

	for (int i = 0; i < 8; i++)
	{
		std::map<char, unsigned int> charCount;
		using pair_type = decltype(charCount)::value_type;

		// count the character frequency
		for (auto itr : messages)
			charCount[itr[i]]++;

		// find the max value in the frequency map
		auto pr = std::max_element
		(
			std::begin(charCount), std::end(charCount),
			[=](const pair_type & p1, const pair_type & p2) {
			if ( sortMax == true )
				return p1.second < p2.second;
			else
				return p1.second > p2.second;
			}
		);
		message += pr->first;
	}

	return message;
}

/********************************************************
** Main
********************************************************/
int main()
{
	std::string fileName = "AoC2016_06_input.txt";
	std::vector<std::string> messages = readMessages(fileName);

	clock_t begin = clock();
	std::cout << "Message (part 1): " << correctMessage(messages, true) << std::endl;
	clock_t end1 = clock();
	std::cout << "Message (part 2): " << correctMessage(messages, false) << std::endl;
	clock_t end2 = clock();

	double elapsedPart1 = double(end1 - begin) / CLOCKS_PER_SEC;
	double elapsedPart2 = double(end2 - end1) / CLOCKS_PER_SEC;

	std::cout << "Part 1 in " << elapsedPart1 << " seconds, part 2 in " << elapsedPart2 << " seconds." << std::endl;

	return 0;
}
