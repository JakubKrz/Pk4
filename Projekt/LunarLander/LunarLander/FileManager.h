#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>//napisac w sprawozdaniu ze dolaczylem


namespace fs = std::filesystem;

class FileManager
{
private:
	fs::path currentDirectory;
	fs::path landerTexture;
	fs::path bestScores;
	fs::path font;
	std::regex pattern;
public:
	FileManager();
	~FileManager();

	bool checkName(std::string name);
	void writeScore(std::string name,int score); 
	std::vector<std::pair<std::string, int>> readScore();
};
