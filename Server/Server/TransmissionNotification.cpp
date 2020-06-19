#include "TransmissionNotification.h"


#pragma region Constructors

TransmissionNotification::TransmissionNotification() : Transmission(TransmissionType::NOTIFICATION, nullptr) {}

TransmissionNotification::TransmissionNotification(ActiveConnection* connection)
	: Transmission(TransmissionType::NOTIFICATION, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionNotification::Run()
{
	std::cout << connection->Receive() << std::endl;
}

#pragma endregion