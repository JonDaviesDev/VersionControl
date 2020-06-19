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
	connection->SendInt(static_cast<int>(TransmissionType::CHOICE));

	int userChoice = 0;
	std::cin >> userChoice;

	connection->SendInt(userChoice);
	std::cout << connection->Receive() << std::endl;
}

#pragma endregion