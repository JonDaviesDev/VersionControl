#include "FileManager.h"


#pragma region Constructors

FileManager::FileManager() {}

#pragma endregion

#pragma region Properties

std::string FileManager::GetLastFile() { return lastFile.string(); }

std::vector<std::pair<std::string, std::string>> FileManager::GetFilePathList() { return filePathList; }

void FileManager::SetArchiveLocation(const std::filesystem::path& value) { archiveLocation = value; }

std::filesystem::path FileManager::GetArchiveLocation() { return archiveLocation; }

#pragma endregion

#pragma region Methods

// Most methods/variables inside this class have a fairly decent naming convention whereby the adding of comments may not be 
// considered necessary

std::filesystem::path FileManager::NewDirectory(const std::string& directoryName, const std::filesystem::path& atLocation)
{
	const char* seperator = "\\";

	std::filesystem::path path;

	// if the user has not specified a location, make new directory in the project folder, else make it at the desired path
	if (atLocation == "")
		path = std::filesystem::current_path();
	else path = atLocation;

	path += (seperator + directoryName);

	std::filesystem::create_directory(path);

	return path;
}

void FileManager::DeleteDirectory(const std::filesystem::path& directoryName)
{
	std::filesystem::remove_all(directoryName);
}

void FileManager::RemoveFile(const std::filesystem::path& filename)
{
	std::filesystem::remove(filename);
}

void FileManager::ClearFileList() { filePathList.clear(); }

std::filesystem::path FileManager::ConstructFile(const std::pair<std::string, std::string>& fileData, const std::filesystem::path& location)
{
	File file;

	// write a file at the LOCATION, fileData.first = the name of the file, fileData.second = the data/contents of the file
	file.WriteFile(location, fileData.first, fileData.second);

	// return a path the new file
	return std::filesystem::path(std::string(location.string() + "\\" + fileData.first));
}

bool FileManager::SearchExtension(std::filesystem::directory_entry file, std::string extension)
{
	// if the extension of the current file matches the argument return true, else return false
	return std::filesystem::path(file).extension() == extension;
}

std::string FileManager::ListFilesInString(const std::filesystem::path& location)
{
	std::string fileMessage;

	unsigned int userChoiceFile = 0;
	fileMessage += "These are the files available to send from your project directory,\n";
	fileMessage += "select a file via the number associated with it:\n\n";

	for (int i = 0; i < filePathList.size(); i++)
	{
		fileMessage += std::string(std::to_string(i) + " - " + filePathList[i].second + "\n");
	}

	return fileMessage;
}

bool FileManager::DoesDirectoryExist(const std::filesystem::path& location, const std::string& searchfor)
{
	// for each directory inside the target directory, if the current directory name matches what we are searching for, return true
	for (const auto& dirEntry : std::filesystem::directory_iterator(location))
			if (dirEntry.path().string() == std::string(location.string() + "\\" + searchfor))
				return true;
			else continue;

	return false;
}

bool FileManager::DoesFileExist(const std::filesystem::path& location)
{
	return std::filesystem::exists(location);
}

#pragma endregion