#pragma once
#include "Transmission.h"
#include "FileManager.h"

class TransmissionRequestFile : public Transmission
{
#pragma region Attributes

private:
	FileManager* fm;

	std::filesystem::path userArchiveLocation;

#pragma endregion

#pragma region Constructors

public:
	TransmissionRequestFile();

	TransmissionRequestFile(ActiveConnection* connection, FileManager* fm);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

#pragma endregion
};

