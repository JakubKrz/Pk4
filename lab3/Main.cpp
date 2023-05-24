#include <iostream>
#include <filesystem>
#include <fstream>
#include "FileManager.h"

namespace fs = std::filesystem;

int main()
{
	//dla utworzonego wczsniej pliku test.txt w katalogu test_folder
	FileManager file("test_folder/test.txt");
	file.copy("test_folder/copies");
	file.move("test_folder/moved");

	FileManager file_rename("test_folder/moved/test.txt");
	file_rename.rename("test_renamed.txt");

	FileManager file_short("test_folder/moved/test_renamed.txt");
	file_short.make_shortcut("shortcut_test1");
}
