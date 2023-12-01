#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <array>
#include <map>

std::array<std::string, 20> strNums = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
std::map<std::string, std::string> values{{"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"},
					{"0", "0"}, {"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"}, {"5", "5"}, {"6", "6"}, {"7", "7"}, {"8", "8"}, {"9", "9"}};

int getCalibrationValue(std::string input){
	std::string a, b = "0";
	bool first = true;
		
	for (int i = 0; i < input.length(); i++){
		if (isdigit(input.at(i))){
			if(first){
				a = input.at(i);
				b = a;
				first = false;
			} else {
				b = input.at(i);
			}
		}
	}
	return std::stoi(a+b);
}

int part2getValues(std::string input){
	std::string a, b = "0";
	bool start, end = false;
	std::size_t match, first, last;
	
	for (int i = 0; i < 20; i++){
		match = input.find(strNums.at(i));

		if (!start && match!=std::string::npos){
			first = match;
			a = strNums.at(i);
			start = true;
		}else{
			if (match < first && match!=std::string::npos){
				first = match;
				a = strNums.at(i);
			}
		}

		match = input.rfind(strNums.at(i));

		if (!end && match!=std::string::npos){
			last = match;
			b = strNums.at(i);
			end = true;
		}else{
			if (match > last && match!=std::string::npos) {
				last = match;
				b = strNums.at(i);
			}
		}
	}
	a = values[a];
	b = values[b];
	
	std::cout << a+b << "  " << input << std::endl;

	return std::stoi(a+b);
}

int main() {
	std::ifstream inputFile;
	std::string input;
	int sum1, sum2, total1, total2 = 0;
	
	inputFile.open("input");

	
	for (std::string line; std::getline(inputFile, line);){
		sum1 = getCalibrationValue(line);
		total1 += sum1;
		sum2 = part2getValues(line);
		total2 += sum2;
	}

	std::cout << "Part 1: The sum of all calibration values is: " << total1 << "." << std::endl;
	std::cout << "Part 2: The sum of all calibration values is: " << total2 << "." << std::endl; 
	return 0;
}
