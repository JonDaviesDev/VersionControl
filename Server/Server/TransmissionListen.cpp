#include "TransmissionListen.h"


#pragma region Constructors

TransmissionListen::TransmissionListen() : Transmission(TransmissionType::LISTENING, nullptr) {}

TransmissionListen::TransmissionListen(ActiveConnection* connection) 
	: Transmission(TransmissionType::LISTENING, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionListen::Run()
{
	DisplayMenuForClient();
}

void TransmissionListen::DisplayMenuForClient()
{
	connection->SendType(TransmissionType::NOTIFICATION);

	std::string line1("\nPlease select an option from the following:\n");
	std::string line2("1. Connect\n");
	std::string line3("2. Disconnect\n");
	std::string line4("3. Send file\n");
	std::string line5("4. Request file\n");

	connection->Send(std::string(line1 + line2 + line3 + line4 + line5));

	connection->SendType(TransmissionType::CHOICE);
}

#pragma endregion