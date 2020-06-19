#include "TransmissionRequestFile.h"



#pragma region Constructors

TransmissionRequestFile::TransmissionRequestFile() : Transmission(TransmissionType::REQUEST, nullptr) {}

TransmissionRequestFile::TransmissionRequestFile(ActiveConnection* connection, FileManager* fm) 
	: Transmission(TransmissionType::REQUEST, connection), fm(fm) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionRequestFile::Run()
{
	connection->SendInt(static_cast<int>(TransmissionType::REQUEST));

	std::cout << connection->Receive() << std::endl;

	int userChoice = 0;
	std::cin >> userChoice;
	connection->SendInt(userChoice);

	std::cout << connection->Receive() << std::endl;
	size_t size = connection->ReceiveInt();

	std::filesystem::path newPath = fm->ConstructFile(connection->ReceiveFile(size), fm->NewDirectory("Received", std::filesystem::current_path()));

	if (fm->DoesFileExist(newPath))
		connection->PrintPositive(std::string(newPath.filename().string() + " received."));
	else
		connection->PrintNegative(std::string("No file received."));

	connection->SendInt(static_cast<int>(TransmissionType::LISTENING));
}

#pragma endregion