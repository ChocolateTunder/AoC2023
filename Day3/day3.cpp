#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstddef>
#include <ctype.h>

using std::cout;
using std::endl;

std::string numb ="0";

int numCrawl(const std::string input, const int loc){
	//Check if location is legal
	if(loc > 0 && loc < input.length() && isdigit(input.at(loc))){
		//Check if left is legal
		if(loc - 1 > 0 && isdigit(loc - 1)){
			int newLoc = loc - 1;
			//Keep crawling to left to find start of number
			numCrawl(input, newLoc);
		}else{
			numb = "";
			int count = loc;
			//Move right until end of number, concaconate string to get full number
			while(isdigit(input.at(count))){
				numb += input.at(count);
				//if(count+1 > input.length()){
				//	break;
				//}
				count += 1;
			}
		}
	}
	return std::stoi(numb);
}

int main(){
	std::ifstream inputFile;
	std::stringstream inputStream;
	std::string input, line;
	std::size_t match;
	int lineLength, total, sum;
	
	inputFile.open("input");
	inputStream << inputFile.rdbuf();
	input = inputStream.str();
	std::getline(inputStream, line);
	lineLength = line.length();
	
	//Find first char that matches one of these symbols
	match = input.find_first_of("!@#$%^&*+_-=/");
	while(match!=std::string::npos){
    		//Search above and below first, check right corners to begin and move left if not solid number
		for(int i = 1; i > -2; i--){
			//Skip if location is number and so is the left character - unless if we're checking left corner - so we don't double dip on long numbers
			if(isdigit(input.at(match - lineLength + i)) && isdigit(input.at(match - lineLength + i - 1)) && i!=-1){continue;}
			numb = "0";
			sum = numCrawl(input, match - lineLength + i);
			total += sum;
			numb = "0";
			if(isdigit(input.at(match + lineLength + i)) && isdigit(input.at(match + lineLength + i - 1)) && i!=-1){continue;}
			sum = numCrawl(input, match + lineLength + i);
			total += sum;
		}
		//Find next match
    		match = input.find_first_of("!@#$%^&*+_-=/", match+1);
  	}
	//Check sides
	sum = numCrawl(input, match + 1);
	total += sum;
	sum = numCrawl(input, match - 1);
	total += sum;
	inputFile.close();
	cout << "Total: " << total << endl;
}
