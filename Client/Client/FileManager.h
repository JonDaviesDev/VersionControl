#pragma once
#include <filesystem>
#include <vector>
#include <iostream>

#include "File.h"

class FileManager
{
#pragma region Attributes

private:
	std::vector<std::pair<std::string, std::string>> filePathList;

	std::string currentUserFile;

	std::string currentUserFilePath;

#pragma endregion

#pragma region Constructors

public:
	FileManager();

#pragma endregion

#pragma region Properties

public:
	std::vector<std::pair<std::string, std::string>> GetFilePathList();

	std::string GetCurrentUserFile();

#pragma endregion

#pragma region Methods

public:
	void ListFiles();
	
#pragma region Reused from Major Project

	bool SearchExtension(std::filesystem::directory_entry file, std::string extension);

	template<class T> void SearchFilesByExtension(std::string path, T extension);

	template<class T, class... Ts> void SearchFilesByExtension(std::string path, T extension, Ts... extensions);

	std::filesystem::path ConstructFile(const std::pair<std::string, std::string>& fileData, const std::filesystem::path& location);

	std::filesystem::path NewDirectory(const std::string& directoryName, const std::filesystem::path& atLocation);

	bool DoesFileExist(const std::filesystem::path& location);

	std::string FindProjectDirectory();

#pragma endregion

#pragma endregion
};





// Searches for one file with the desired extention (this will be used with the variadic function to ensure that the last file is found)
template<class T> void FileManager::SearchFilesByExtension(std::string path, T extension)
{
	// Iterate through all files in a specified directory
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		// If the extension of the current file matches an argument from list of arguments, step in
		if (SearchExtension(file, extension))
		{
			// Add both the file path and the file name to the vector in the form of a pair
			filePathList.push_back(std::pair<std::string, std::string>(std::filesystem::path(file).string(), std::filesystem::path(file).filename().string()));
		}
	}
}

// Variadic function to search for X number of file extensions
template<class T, class... Ts> void FileManager::SearchFilesByExtension(std::string path, T extension, Ts... extensions)
{
	SearchFilesByExtension(path, extension);

	SearchFilesByExtension(path, extensions...);
}