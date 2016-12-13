/*

 Advent of Code 2016
 Day 10: Balance Bots

*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

//#define DEBUG

/********************************************************
 ** Method to read commands
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
	std::cout << "Read " << vect.size() << " commands." << std::endl;
#endif

	return vect;
}



/********************************************************
 ** Bot object
 ********************************************************/
class Bot {
public:
	Bot();
	void Accept(int);
	void SetTargets(bool, int, bool, int);
	bool isFull();
	int GetLowChip();
	int GetHighChip();
	void EmptyChips();

	int chip1, chip2;
	int lowIsBot, highIsBot;
	int lowTarget, highTarget;

private:

};

Bot::Bot()
{
	chip1 = NULL;
	chip2 = NULL;
}

//
// Accept a chip with the specified value
//
void Bot::Accept(int value)
{
	if (chip1 == NULL) chip1 = value;
	else chip2 = value;
}

//
// Set the bot's targets when distributing chips
//
void Bot::SetTargets(bool LIB, int LT, bool HIB, int HT)
{
	lowIsBot = LIB;
	highIsBot = HIB;
	lowTarget = LT;
	highTarget = HT;
}

//
// Return if both chip slots are full
//
bool Bot::isFull()
{
	return (chip1 != NULL && chip2 != NULL);
}

//
// Return the low chip
//
int Bot::GetLowChip()
{
	if (chip1 < chip2) {
		int retChip = chip1;
		return retChip;
	}
	else
	{
		int retChip = chip2;
		return retChip;
	}
}


//
// Return the high chip
//
int Bot::GetHighChip()
{
	if (chip1 > chip2) {
		int retChip = chip1;
		return retChip;
	}
	else
	{
		int retChip = chip2;
		return retChip;
	}
}

//
// Empty the chips
//
void Bot::EmptyChips()
{
	chip1 = NULL;
	chip2 = NULL;
}


/********************************************************
 ** Distribute the bot instructions
 ********************************************************/
void DistributeBotInstructions(std::map<unsigned int, Bot>& bots, std::vector<std::string> instructions)
{
	for (auto itr : instructions)
	{
		// parse instruction
		if (itr[0] == 'v')
		{
			int gIndex = itr.find(" g");

			int value = stoi(itr.substr(6, gIndex - 6));
			int botId = stoi(itr.substr(gIndex + 12, std::string::npos));

#ifdef DEBUG
			std::cout << "Value " << value << " -> bot " << botId << std::endl;
#endif

			bots[botId].Accept(value);
		}
		else
		{
			int gIndex = itr.find(" g");
			bool lowIsBot = itr.find("low to bot") != std::string::npos;
			bool highIsBot = itr.find("high to bot") != std::string::npos;

			int andIndex = itr.find("and");
			int beforeLowTargetIndex = (itr.substr(0, andIndex - 1)).find_last_of(' ');
			int lastSpaceIndex = itr.find_last_of(' ');

			int srcId = stoi(itr.substr(4, gIndex - 4));
			int lowTarget = stoi(itr.substr(beforeLowTargetIndex, andIndex - beforeLowTargetIndex));
			int highTarget = stoi(itr.substr(lastSpaceIndex, std::string::npos));

#ifdef DEBUG
			std::cout << "Bot " << srcId << " low (" << lowIsBot << ")-> " << lowTarget << ", high (" << highIsBot << ")-> " << highTarget << std::endl;
#endif
			bots[srcId].SetTargets(lowIsBot, lowTarget, highIsBot, highTarget);

		}
	}
}

/********************************************************
 ** Process the bot instructions
 ********************************************************/
void ProcessBotInstructions(std::map<unsigned int, Bot>& bots, std::map<unsigned int, unsigned int>& outputs)
{
	int foundFullBot = false;

	// repeat as long as we keep finding full bots
	do
	{
		foundFullBot = false;

		// It's very important to use & here or the changes we make to the bots as wel loop are lost
		for (auto& itr : bots)
		{
			if (itr.second.isFull())
			{
				foundFullBot = true;

				Bot& bot = itr.second;

				if ((bot.chip1 == 61 && bot.chip2 == 17) ||
					(bot.chip1 == 17 && bot.chip2 == 61))
					std::cout << "Part 1: Bot #" << itr.first << std::endl;

				int lowChip = bot.GetLowChip();
				int highChip = bot.GetHighChip();
				bot.EmptyChips();

				if (bot.lowIsBot) bots[bot.lowTarget].Accept(lowChip);
				else (outputs[bot.lowTarget] = lowChip);

				if (bot.highIsBot) bots[bot.highTarget].Accept(highChip);
				else (outputs[bot.highTarget] = highChip);
			}
		}
	} while (foundFullBot);
}


/********************************************************
 ** Main
 ********************************************************/
int main()
{
	std::string fileName = "AoC2016_10_input.txt";
	std::vector<std::string> instructions = readInstructions(fileName);

	std::map<unsigned int, Bot> bots;
	std::map<unsigned int, unsigned int> outputs;

	DistributeBotInstructions(bots, instructions);
	ProcessBotInstructions(bots, outputs);

	std::cout << "Part 2: " << outputs[0] * outputs[1] * outputs[2] << std::endl;

	return 0;
}
