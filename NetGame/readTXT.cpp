#include "readTXT.h"

bool ReadTXT::readFile(std::vector<std::vector<int>>& data, const std::string filename) {

	std::ifstream file(filename);

	if (!file.is_open()) return false;

	std::string line;

	while (std::getline(file, line)) {
		
		data.push_back(std::vector<int>());
		splitLine(data.back(), line);
	}

	file.close();

	return true;
}

void ReadTXT::splitLine(std::vector<int>& vec, std::string& line) {

	std::string temp;

	for (auto&ch : line) {

		if (ch == ' ' || ch == ',') {

			if (!temp.empty()) {

				vec.push_back(std::stoi(temp));
				temp.clear();
			}

		} else temp += ch;	
	}

	if (!temp.empty()) vec.push_back(std::stoi(temp));

	line.clear();
}