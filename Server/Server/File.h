#pragma once
#include <fstream>
#include <sstream>
#include <filesystem>

class File
{
#pragma region Attributes

private:
	std::string filename;

	std::string data;

	std::fstream file;

#pragma endregion

#pragma region Constructors

public:
	File();

	File(const std::string& filepath);

	File(const std::filesystem::path& filepath);

	~File();

#pragma endregion

#pragma region Properties

public:
	void SetData(const std::string& value);

	void SetFilename(const std::string& value);

	std::string GetData();

	std::string GetFilename();

#pragma endregion

#pragma region Methods

public:
	inline void Open(const std::filesystem::path& filepath);

	inline void Close();

	std::stringstream ReadFile();

	std::stringstream ReadFile(std::fstream& stream);

	void WriteFile(const std::filesystem::path& location, const std::filesystem::path& newFilename, const std::string& data);

	void Serialise(std::ostream& out);

	void Unserialise(std::istream& in);

#pragma endregion
};

