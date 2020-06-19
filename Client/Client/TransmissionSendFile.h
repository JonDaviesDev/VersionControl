#pragma once
#include "Transmission.h"
#include "FileManager.h"

class TransmissionSendFile : public Transmission
{
#pragma region Attributes

private:
	FileManager* fm;

	std::filesystem::path archiveLocation;

#pragma endregion

#pragma region Constructors

public:
	TransmissionSendFile();

	TransmissionSendFile(ActiveConnection* connection, FileManager* fm);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

#pragma endregion
};

