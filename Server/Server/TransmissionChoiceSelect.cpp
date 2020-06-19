#include "TransmissionChoiceSelect.h"


#pragma region Constructors

TransmissionChoiceSelect::TransmissionChoiceSelect() : Transmission(TransmissionType::CHOICE, nullptr) {}

TransmissionChoiceSelect::TransmissionChoiceSelect(ActiveConnection* connection)
	: Transmission(TransmissionType::CHOICE, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionChoiceSelect::Run()
{
	int userChoice = connection->ReceiveInt();

	connection->Send(std::string(MatchSelection(userChoice)));

	// if the user selects a valid choice
	if (userChoice > 4 || userChoice < 0)
		connection->SendType(TransmissionType::LISTENING);
	else
		connection->SendType(static_cast<TransmissionType>(userChoice));
}

std::string TransmissionChoiceSelect::MatchSelection(int value)
{
	std::string messageStart("You have chosen ");

	switch (value)
	{
	case 1:
		return std::string("Connection already established.");
	case 2:
		return std::string("Disconnecting.");
	case 3:
		return std::string(messageStart + "to send a file to the server.\n");
	case 4:
		return std::string(messageStart + "to request a file from the server.\n");
	default:
		return std::string(messageStart + "an invalid option, please select from the options available");
	}
}

#pragma endregion