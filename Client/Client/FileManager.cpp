#include "FileManager.h"



#pragma region Constructors

FileManager::FileManager() {}

#pragma endregion

#pragma region Properties

std::vector<std::pair<std::string, std::string>> FileManager::GetFilePathList() { return filePathList; }

std::string FileManager::GetCurrentUserFile() { return currentUserFile; }

#pragma endregion

#pragma region Methods

void FileManager::ListFiles()
{
	unsigned int userChoiceFile = 0;
	std::cout << "These are the files available to send from your project directory," << std::endl;
	std::cout << "select a file via the number associated with it: " << std::endl << std::endl;

	for (int i = 0; i < filePathList.size(); i++)
	{
		std::cout << i << " - " << filePathList[i].second << std::endl;
	}

	std::cin >> userChoiceFile;

	currentUserFilePath = filePathList[userChoiceFile].first;
	currentUserFile = filePathList[userChoiceFile].second;

	filePathList.clear();
}

bool FileManager::SearchExtension(std::filesystem::directory_entry file, std::string extension)
{
	// if the extension of the current file matches the argument return true, else return false
	return std::filesystem::path(file).extension() == extension;
}

std::filesystem::path FileManager::ConstructFile(const std::pair<std::string, std::string>& fileData, const std::filesystem::path& location)
{
	File file;

	file.WriteFile(location, fileData.first, fileData.second);

	return std::filesystem::path(std::string(location.string() + "\\" + fileData.first));
}

std::filesystem::path FileManager::NewDirectory(const std::string& directoryName, const std::filesystem::path& atLocation)
{
	const char* seperator = "\\";

	std::filesystem::path path;

	if (atLocation == "")
		path = std::filesystem::current_path();
	else path = atLocation;

	path += (seperator + directoryName);

	std::filesystem::create_directory(path);

	return path;
}

bool FileManager::DoesFileExist(const std::filesystem::path& location)
{
	return std::filesystem::exists(location);
}

std::string FileManager::FindProjectDirectory()
{
	SearchFilesByExtension(std::filesystem::current_path().string(), ".h", ".bmp");

	if (filePathList.empty())
	{
		std::string cp = std::filesystem::path(std::filesystem::current_path()).string();

		cp.substr(0, cp.find_last_of("\\", 0));

		cp += "\\client";

		return cp;
	}
	
	
	filePathList.clear();

	return "";

}

#pragma endregion