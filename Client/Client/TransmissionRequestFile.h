#pragma once
#include "Transmission.h"

class TransmissionRequestFile : public Transmission
{
#pragma region Attributes

private:

#pragma endregion

#pragma region Constructors

public:
	TransmissionRequestFile();

	TransmissionRequestFile(ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

#pragma endregion
};

