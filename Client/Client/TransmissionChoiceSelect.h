#pragma once
#include "Transmission.h"

class TransmissionChoiceSelect : public Transmission
{
#pragma region Attributes

private:

#pragma endregion

#pragma region Constructors

public:
	TransmissionChoiceSelect();

	TransmissionChoiceSelect(ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void Run();

#pragma endregion
};

