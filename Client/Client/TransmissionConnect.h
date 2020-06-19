#pragma once
#include "Transmission.h"
#include "ActiveConnection.h"

class TransmissionConnect : public Transmission
{
#pragma region Attributes

private:

#pragma endregion

#pragma region Constructors

public:
	TransmissionConnect();

	TransmissionConnect(ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

#pragma endregion
};

