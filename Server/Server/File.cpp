#include "File.h"


#pragma region Constructors

File::File() {}

File::File(const std::string& filepath)
{
	Open(std::filesystem::path(filepath));

	SetFilename(std::filesystem::path(filepath).filename().string());
}

File::File(const std::filesystem::path& filepath) : filename(filepath.filename().string())
{
	Open(filepath);

	SetFilename(filepath.filename().string());
}

File::~File()
{
	file.close();
}

#pragma endregion

#pragma region Properties

void File::SetData(const std::string& value) { data = value; }

void File::SetFilename(const std::string& value) { filename = value; }

std::string File::GetData() { return data; }

std::string File::GetFilename() { return filename; }

#pragma endregion

#pragma region Methods

void File::Open(const std::filesystem::path& filepath)
{
	file.open(filepath.c_str());
}

void File::Close()
{
	file.close();
}

std::stringstream File::ReadFile()
{
	return std::stringstream(std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())));
}

std::stringstream File::ReadFile(std::fstream& stream)
{
	stream >> filename;

	return std::stringstream(std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>())));
}

void File::WriteFile(const std::filesystem::path& location, const std::filesystem::path& newFilename, const std::string& data)
{
	std::ofstream outFile(location.string() + "\\" + newFilename.string());
	
	outFile << data;

	outFile.close();
}

void File::Serialise(std::ostream& out)
{
	out << data << std::endl;
}

void File::Unserialise(std::istream& in)
{
	in >> data;
}

#pragma endregion