#pragma once
#include "Transmission.h"
#include "FileManager.h"

class TransmissionReceiveFile : public Transmission
{
#pragma region Attributes

private:
	FileManager* fm;

#pragma endregion

#pragma region Constructors

public:
	TransmissionReceiveFile();
	
	TransmissionReceiveFile(ActiveConnection* connection, FileManager* fm);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:

	void Run();

#pragma endregion
};

