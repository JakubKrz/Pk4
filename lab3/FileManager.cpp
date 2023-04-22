#include "FileManager.h"

namespace fs = std::filesystem;

bool FileManager::copy(std::string path)
{
	if (fs::exists(this->path))
	{
		fs::create_directories(path);
		fs::copy(this->path, path, fs::copy_options::recursive);
		return true;
	}
	else return false;
}

void FileManager::move(std::string path)
{
	if (this->copy(path))
	{
		fs::remove_all(this->path);
	}
}

void FileManager::make_shortcut(std::string path)
{
	if (fs::exists(this->path))
	{
		if (fs::is_directory(this->path))
		{
			fs::create_directory_symlink(this->path, path);
		}
		else
		{
			fs::create_symlink(this->path, path);
		}
	}
}

void FileManager::rename(std::string path)
{
	if (fs::exists(this->path))
	{
		fs::path p = fs::path{ this->path };
		p = p.parent_path();
		fs::rename(this->path, p / path);
	}

}