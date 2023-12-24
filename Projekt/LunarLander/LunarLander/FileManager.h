#pragma once
#include <filesystem>
#include <fstream>
#include <regex>
#include <algorithm>


namespace fs = std::filesystem;

class FileManager
{
private:
	fs::path currentDirectory;
	fs::path bestScores;
	std::regex pattern;
public:
	FileManager();

	bool checkName(std::string name);
	void writeScore(std::string name,int score); 
	std::vector<std::pair<std::string, int>> readScore();
};