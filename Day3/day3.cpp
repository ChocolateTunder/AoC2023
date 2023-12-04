#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cstddef>
#include <ctype.h>

using std::cout;
using std::endl;
int main(){
	std::ifstream inputFile;
	std::stringstream inputStream;
	//position : value map
	std::map<int, int> value_pos;
	std::string inputString, numString, inputChar, line;
	std::size_t match;
	char c;
	int lineLength, sum, begin, end;
	
	inputFile.open("input");
	inputStream << inputFile.rdbuf();
	inputString = inputStream.str();
	std::getline(inputFile, line);
	lineLength = line.length();


	begin = 0;
	end = 0;
	while(inputStream.get(c)){
		if(isdigit(c)){
			numString = c;
			value_pos[inputStream.tellg()] = atoi(&c);
			if(isdigit(inputStream.peek())){
				begin = inputStream.tellg();
				while(isdigit(inputStream.peek())){
					inputStream.get(c);
					numString += c;
				}
				end = inputStream.tellg();
				for(int i = begin; i <= end; i++){
					value_pos[i] = std::stoi(numString);
				}
			}
		}
	}
	
	auto search = value_pos.find(1);
	sum = 0;
	match = inputString.find_first_of("!@#$%^&*+_-=/");
	while(match!=std::string::npos){
		for(int i = -1; i < 2;){
			search = value_pos.find(match - lineLength + i);
			if(search != value_pos.end()){
				sum += value_pos[match - lineLength + i];
				i += std::to_string(value_pos[match - lineLength + i]).length();
			}
			i++;
		}
		for(int i = -1; i < 2;){
			search = value_pos.find(match + lineLength + i);
			if(search != value_pos.end()){
				sum += value_pos[match + lineLength + i];
				i += std::to_string(value_pos[match + lineLength + i]).length();
			}
			i++;
		}
		search = value_pos.find(match + 1);
		if(search != value_pos.end()){
			sum += value_pos[match + 1];
		}
		search = value_pos.find(match - 1);
		if(search != value_pos.end()){
			sum += value_pos[match - 1];
		}
		
		match = inputString.find_first_of("!@#$%^&*+_-=/", match+1);
	}

	cout << "Total sum: " << sum << endl;

	inputFile.close();

}
