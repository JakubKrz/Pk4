#include "FileManager.h"

FileManager::FileManager()
{
	this->currentDirectory = fs::current_path();
	this->bestScores = currentDirectory / "Scores" / "BestScores.txt";
	this->pattern = "^[a-zA-Z0-9]{3,12}$";
}

bool FileManager::checkName(std::string name)
{
	return std::regex_match(name, this->pattern);
}

void FileManager::writeScore(std::string name,int score)
{
	std::ofstream file(this->bestScores,std::ios::app);
	file << name << " " << score << std::endl;
	file.close();

}

//Reads all scores from file and returns 10 best
std::vector<std::pair<std::string, int>> FileManager::readScore()
{
	std::fstream file(this->bestScores);
	std::vector<std::pair<std::string, int>> scores;
	std::string name;
	int points;
	while (file >> name >> points)
	{
		scores.push_back(std::make_pair(name, points));
	}
	file.close();
	std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) 
		{
		return a.second > b.second;
		});
	if (scores.size() > 10)
	{
		scores.resize(10);
	}
	return scores;
}