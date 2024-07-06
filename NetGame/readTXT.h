#pragma once

#ifndef READTEXT
#define READTEXT

#include <fstream>
#include <string>
#include <vector>

class ReadTXT {
 public:
	 bool readFile(std::vector<std::vector<int>>& data, const std::string filename);

 private:
	 void splitLine(std::vector<int>& vec, std::string& line);
};


#endif