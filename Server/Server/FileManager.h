#pragma once

#include <filesystem>
#include <string>
#include <iostream>

#include "File.h"

class FileManager
{
#pragma region Attributes

private:
	std::filesystem::path lastFile;

	std::vector<std::pair<std::string, std::string>> filePathList;

	std::string currentUserFile;

	std::string currentUserFilePath;

	std::filesystem::path archiveLocation;

#pragma endregion

#pragma region Constructors

public:
	FileManager();

#pragma endregion

#pragma region Properties

public:
	std::string GetLastFile();

	std::vector<std::pair<std::string, std::string>> GetFilePathList();

	void SetArchiveLocation(const std::filesystem::path& value);

	std::filesystem::path GetArchiveLocation();

#pragma endregion

#pragma region Methods

public:
	// Create a new directory by providing a new name, and optionally, a location where you want to save it
	std::filesystem::path NewDirectory(const std::string& directoryName, const std::filesystem::path& atLocation = "");

	// Remove a directory
	void DeleteDirectory(const std::filesystem::path& directoryName);

	// Remove a file
	void RemoveFile(const std::filesystem::path& filename);

	// Clear all elements of the fileList vector
	void ClearFileList();

	// Remake a file
	std::filesystem::path ConstructFile(const std::pair<std::string, std::string>& fileData, const std::filesystem::path& location);

	// List of all files that the fileManager has
	std::string ListFilesInString(const std::filesystem::path& location);

	// Check the existance of a directory
	bool DoesDirectoryExist(const std::filesystem::path& location, const std::string& searchfor = "");

	// Check the existance of a file
	bool DoesFileExist(const std::filesystem::path& location);


#pragma region Variadic Functions

	// Variadic functions that were used in my major project
	// Help was sourced from Tim Bashford

	bool SearchExtension(std::filesystem::directory_entry file, std::string extension);

	template<class T> void SearchFilesByExtension(std::string path, T extension);

	template<class T, class... Ts> void SearchFilesByExtension(std::string path, T extension, Ts... extensions);

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

