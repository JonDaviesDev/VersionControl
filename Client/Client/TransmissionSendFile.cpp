#include "TransmissionSendFile.h"



#pragma region Constructors

TransmissionSendFile::TransmissionSendFile() : Transmission(TransmissionType::SENDFILE, nullptr) {}

TransmissionSendFile::TransmissionSendFile(ActiveConnection* connection, FileManager* fm) 
	: Transmission(TransmissionType::SENDFILE, connection), fm(fm) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionSendFile::Run()
{
	connection->SendInt(static_cast<int>(TransmissionType::SENDFILE));

	std::string projectDirectory = fm->FindProjectDirectory();

	if (projectDirectory == "")
		fm->SearchFilesByExtension(std::filesystem::current_path().string(), std::string(".h"), std::string(".cpp"));
	else fm->SearchFilesByExtension(projectDirectory, std::string(".h"), std::string(".cpp"));

	fm->ListFiles();

	connection->SendFile(fm->GetCurrentUserFile());

	std::cout << connection->Receive() << std::endl;

	connection->SendInt(static_cast<int>(TransmissionType::LISTENING));
}

#pragma endregion