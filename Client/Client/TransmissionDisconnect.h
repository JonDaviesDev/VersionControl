#pragma once
#include "Transmission.h"

class TransmissionDisconnect : public Transmission
{
#pragma region Attributes

private:

#pragma endregion

#pragma region Constructors

public:
	TransmissionDisconnect();

	TransmissionDisconnect(ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:

	void Run();

#pragma endregion
};

