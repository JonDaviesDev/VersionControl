#pragma once
#include "Transmission.h"

class TransmissionListen : public Transmission
{
#pragma region Attributes

private:


#pragma endregion

#pragma region Constructors

public:
	TransmissionListen();

	TransmissionListen(ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

	void DisplayMenuForClient();

#pragma endregion
};

