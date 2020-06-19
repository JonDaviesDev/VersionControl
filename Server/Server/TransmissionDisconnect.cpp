#include "TransmissionDisconnect.h"


#pragma region Constructors

TransmissionDisconnect::TransmissionDisconnect() : Transmission(TransmissionType::DISCONNECT, nullptr) {}

TransmissionDisconnect::TransmissionDisconnect(ActiveConnection* connection)
	: Transmission(TransmissionType::DISCONNECT, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionDisconnect::Run() 
{
	connection->SetTextColour(12);
	std::cout << "Connection terminated." << std::endl;
	connection->SetTextColour(15);
}

#pragma endregion