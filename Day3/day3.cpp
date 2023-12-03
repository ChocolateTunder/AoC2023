#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
int main(){
	std::ifstream inputFile;
	
	std::vector<std::vector<std::string>> input;
	std::vector<std::string> inputVec;

	int lineLength;
	inputFile.open("input");

	
	for(std::string line; std::getline(inputFile, line);){
		inputVec.push_back(line);
		lineLength = line.length();
	}	
	
	//for(std::string line : inputVec){
	//	cout << line << endl;
	//}
	for(int i = 0; i < inputVec.size(); i++){
		cout << inputVec.at(i);
	}
}
