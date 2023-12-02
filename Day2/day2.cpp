#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <array>
#include <regex>
#include <numeric>
#include <vector>

int main(){
	std::ifstream inputFile;
	std::string input, game, colour, colourSet, colourSingle, countString; 
	int maxRed, maxGreen, maxBlue, power, sum, total, count = 0;
	std::vector<int> validGames;
	std::vector<int> part2;
	inputFile.open("input");
	
	//Contents of bag
	int bagRed   = 12;
	int bagGreen = 13;
	int bagBlue  = 14;
	
	for (std::string line; std::getline(inputFile, line);){
		count = 0;
		maxRed   = 0;
		maxGreen = 0;
		maxBlue  = 0;

		//Excise the Game X section and store the game number
		game = line.substr(0, line.find(":"));
		game = std::regex_replace(game, std::regex(R"([\D])"), "");

		//Get the string of colours and numbers with the Game X section
		colour = line.substr(line.find(":")+2, std::string::npos);
		std::istringstream setStream(colour);
		//Break down into each set of revealed colours
		while(std::getline(setStream, colourSet, ';')){
			//Breadown into each colour
			std::istringstream colourStream(colourSet);
			while(std::getline(colourStream, colourSingle, ',')){
				countString = std::regex_replace(colourSingle, std::regex(R"([\D])"), "");
				count = std::stoi(countString);
				if(colourSingle.find("red")!=std::string::npos){
					if(count > maxRed){ maxRed = count;}
				}
				if(colourSingle.find("green")!=std::string::npos){
					if(count > maxGreen){ maxGreen = count;}
				}
				if(colourSingle.find("blue")!=std::string::npos){
					if(count > maxBlue){ maxBlue = count;}
				}
			}
		}
		//Check if game is valid
		if(maxRed <= bagRed && maxGreen <= bagGreen && maxBlue <= bagBlue){
			validGames.push_back(std::stoi(game));
		}
		//Add power of minimum cube set to vector
		int mult = maxRed * maxGreen * maxBlue;
		part2.push_back(mult);
		
	}

	//Sum of all game IDs
	total = std::accumulate(validGames.begin(), validGames.end(), 0);
	sum   = std::accumulate(part2.begin(), part2.end(), 0);
	std::cout << "The sum of all valid game IDs = " << total << std::endl;
	std::cout << "The sum of the power of the minum sets is " << sum << std::endl;
	return 0;
}
