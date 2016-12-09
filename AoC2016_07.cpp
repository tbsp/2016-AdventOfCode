/*

 Advent of Code 2016
 Day 7: Internet Protocol Version 7

*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>

#define DEBUG

/********************************************************
 ** Method to read IPs
 ********************************************************/
std::vector<std::string> readIPs(std::string &fileName)
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
	std::cout << "Read " << vect.size() << " IPs." << std::endl;
#endif

	return vect;
}

/********************************************************
 ** Return how many IPs support TLS
 ********************************************************/
int checkTLSSupport(std::vector<std::string> IPs, bool sortMax)
{
	int tlsSupportCount = 0;

	for (auto itr : IPs)
	{
		bool hasTLS = false;
		bool hasHypernetTLS = false;
		bool inHypernet = false;

		std::deque <char> recentChars;

		for (int i = 0; i < itr.size(); i++)
		{
			if (itr[i] == '[')
			{
				// restart in hypernet sequence
				inHypernet = true;
				while (!recentChars.empty()) recentChars.clear();
			}
			else if (itr[i] == ']')
			{
				// restart out of hypernet sequence
				inHypernet = false;
				while (!recentChars.empty()) recentChars.clear();
			}
			else
			{
				recentChars.push_back(itr[i]);
			}

			// limit the queue size
			if (recentChars.size() > 4)
				recentChars.pop_front();

			// check for ABBA
			if (recentChars.size() == 4)
			{
				// check for ABBA
				if (recentChars[0] != recentChars[1] &&
					recentChars[0] == recentChars[3] &&
					recentChars[1] == recentChars[2])
				{
					if (inHypernet) hasHypernetTLS = true;
					else hasTLS = true;
				}
			}
		}

		if (hasTLS && !hasHypernetTLS)
			tlsSupportCount++;
	}

	return tlsSupportCount;
}


/********************************************************
 ** Return if the IP has a matching BAB sequence
 ********************************************************/
bool hasBAB(std::string ip, char A, char B)
{
	bool inHypernet = false;

	std::deque <char> recentChars;

	for (int i = 0; i < ip.size(); i++)
	{
		if (ip[i] == '[')
		{
			// restart in hypernet sequence
			inHypernet = true;
			while (!recentChars.empty()) recentChars.clear();
		}
		else if (ip[i] == ']')
		{
			// restart out of hypernet sequence
			inHypernet = false;
			while (!recentChars.empty()) recentChars.clear();
		}
		else
		{
			recentChars.push_back(ip[i]);
		}

		// limit the queue size
		if (recentChars.size() > 3)
			recentChars.pop_front();

		// check for BAB
		if (recentChars.size() == 3 && inHypernet)
		{
			if (recentChars[0] == B &&
				recentChars[1] == A &&
				recentChars[2] == B)
				return true;
		}
	}
	return false;
}

/********************************************************
 ** Return how many IPs support SSL
 ********************************************************/
int checkSSLSupport(std::vector<std::string> IPs, bool sortMax)
{
	int sslSupportCount = 0;

	for (auto itr : IPs)
	{
		bool hasSSL = false;
		bool inHypernet = false;

		std::deque <char> recentChars;

		for (int i = 0; i < itr.size(); i++)
		{
			if (itr[i] == '[')
			{
				// restart in hypernet sequence
				inHypernet = true;
				while (!recentChars.empty()) recentChars.clear();
			}
			else if (itr[i] == ']')
			{
				// restart out of hypernet sequence
				inHypernet = false;
				while (!recentChars.empty()) recentChars.clear();
			}
			else
			{
				recentChars.push_back(itr[i]);
			}

			// limit the queue size
			if (recentChars.size() > 3)
				recentChars.pop_front();

			// check for ABA
			if (recentChars.size() == 3 && !inHypernet)
			{
				if (recentChars[0] != recentChars[1] &&
					recentChars[0] == recentChars[2])
				{
					if (hasBAB(itr, recentChars[0], recentChars[1]))
						hasSSL = true;
				}
			}
		}

		if (hasSSL) sslSupportCount++;
	}

	return sslSupportCount;
}

/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string fileName = "AoC2016_07_input.txt";
	std::vector<std::string> IPs = readIPs(fileName);

	std::cout << "TLS Support (part 1): " << checkTLSSupport(IPs, true) << std::endl;
	std::cout << "SSL Support (part 2): " << checkSSLSupport(IPs, false) << std::endl;

	return 0;
}
