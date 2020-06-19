#include "TransmissionConnect.h"



#pragma region Constructors

TransmissionConnect::TransmissionConnect() : Transmission(TransmissionType::CONNECT, nullptr) {}

TransmissionConnect::TransmissionConnect(ActiveConnection* connection)
	: Transmission(TransmissionType::CONNECT, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionConnect::Run()
{
	connection->ReceiveType();
	std::cout << connection->Receive() << std::endl;

	std::string name;

	std::cin >> name;

	connection->SetUsername(name);

	connection->Send(name);

	std::cout << connection->Receive() << std::endl;
}

#pragma endregion