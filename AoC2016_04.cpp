/*

 Advent of Code 2016
 Day 4: Security Through Obscurity

*/


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

//#define DEBUG



/*******************************************************
 ** Room object
 *******************************************************/
class Room
{
public:
	Room(std::string, int, std::string);
	bool isReal();
	std::string getDecryptedName();

	int sectorId;

private:
	std::string encryptedName;
	std::string checksum;
};

Room::Room(std::string n, int s, std::string c)
{
	encryptedName = n;
	sectorId = s;
	checksum = c;
}

//
// Return if the room is real (or a decoy)
//
bool Room::isReal()
{
	std::map<char, unsigned int> charCount;

	// Count characters
	for (char character : encryptedName)
		if( character != '-') charCount[character]++;

	// Build vector of pairs
	std::vector<std::pair<char, unsigned int>> pairs;
	for (auto itr = charCount.begin(); itr != charCount.end(); ++itr)
		pairs.push_back(*itr);

	// Sort based on frequency and alphabetical order
	std::sort(pairs.begin(), pairs.end(), [=](std::pair<char, unsigned int>& a, std::pair<char, unsigned int>& b)
	{
		return a.second > b.second;
	});

	// Check checksum
	int i = 0;
	for (auto itr = pairs.begin(); itr != pairs.begin() + 5; ++itr, i++)
	{
		if (checksum[i] != (*itr).first)
			return false;
	}

	return true;
}

//
// Return the decrypted room name
//
std::string Room::getDecryptedName()
{
	std::string decryptedName = encryptedName;

	for (auto itr = decryptedName.begin(); itr != decryptedName.end(); ++itr)
	{
		if (*itr == '-')
			(*itr) = ' ';
		else
		{
			(*itr) = 'a' + (((*itr) - 'a' + sectorId) % 26);
		}
	}

	return decryptedName;
}


/********************************************************
 ** Method to read room input
 ********************************************************/
std::vector<Room> readRooms(std::string &fileName)
{
	std::vector<Room> vect;

	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::size_t sectorIdStart = line.find_last_of("-");
			std::size_t checksumStart = line.find("[");

			std::string encryptedName = line.substr(0, sectorIdStart);
			int sectorId = stoi(line.substr(sectorIdStart + 1, checksumStart - sectorIdStart));
			std::string checksum = line.substr(checksumStart + 1, 5);

			vect.push_back(Room(encryptedName, sectorId, checksum));
		}
		myfile.close();
	}

#ifdef DEBUG
	std::cout << "Read " << vect.size() << " rooms." << std::endl;
#endif

	return vect;
}



/********************************************************
 ** Main
 ********************************************************/
int main()
{
	// Read input file contents
	std::string fileName = "AoC2016_04_input.txt";
	std::vector<Room> rooms = readRooms(fileName);

	int sectorSum = 0;
	int northPoleObjectId = 0;

	for (std::vector<Room>::iterator itr = rooms.begin(); itr < rooms.end(); ++itr)
	{
		if ((*itr).isReal() == true)
		{
			sectorSum += (*itr).sectorId;

			std::string decryptedName = (*itr).getDecryptedName();

#ifdef DEBUG
			std::cout << "Decrypted name: " << decryptedName << std::endl;
#endif

			if (decryptedName == "northpole object storage")
				northPoleObjectId = (*itr).sectorId;
		}
	}

	std::cout << "Real room sector ID sum: " << sectorSum << std::endl;
	std::cout << "North pole object storage sector ID: " << northPoleObjectId << std::endl;

	return 0;
}
