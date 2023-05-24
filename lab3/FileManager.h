#pragma once

#include <iostream>
#include <filesystem>

class FileManager 
{
public:
	bool copy(std::string);
	void move(std::string);
	void make_shortcut(std::string);
	void rename(std::string);
	FileManager(std::string path) : path(path) {};
private:
	std::string path;

};