#include "FileManager.h"

FileManager::FileManager()
{
	this->currentDirectory = fs::current_path();
	this->landerTexture = currentDirectory / "Textures" / "test1.png";//przeniesc pliki i zmienic kod
	this->bestScores = currentDirectory / "Scores" / "BestScores.txt";
	this->font = currentDirectory/"Fonts"/"zector" / "Zectro.ttf";//przeniesc pliki i zmienic kod
	this->pattern = "^[a-zA-Z0-9]{3,12}$";
	//przeniesc chyba do ui
	//sprawdzanie nazwy chyba tez w ui
	//gdy nazwa przejdzie zapisuje i wysylam zeby zapisac do pliku
	//to musi byc chyba osobny stan gry ktory pokazjue wpisywana nazwe
	//albo petla while nazwa poprawna draw teren lander i nazwe bez update
	//pozniej zapisz do pliku
	//tutaj jescze mozna usuwac wyniki slabsze tak zeby bylo tylko 10 maksymalnie

	//wywietlenie to ma byc stan 
	//po prostu np 10 najlepszych wynikow
}

FileManager::~FileManager()
{
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
