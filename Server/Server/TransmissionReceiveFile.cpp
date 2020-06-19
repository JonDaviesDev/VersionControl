#include "TransmissionReceiveFile.h"



#pragma region Constructors

TransmissionReceiveFile::TransmissionReceiveFile() : Transmission(TransmissionType::RECEIVEFILE, nullptr) {}

TransmissionReceiveFile::TransmissionReceiveFile(ActiveConnection* connection, FileManager* fm)
	: Transmission(TransmissionType::RECEIVEFILE, connection), fm(fm) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionReceiveFile::Run() 
{
	std::string userArchiveLocation(fm->GetArchiveLocation().string() + "\\" + connection->GetUsername());

	fm->SearchFilesByExtension(userArchiveLocation, ".h", ".cpp");

	if (fm->GetFilePathList().empty())
		connection->Send("\nYou have no files to view in your archive.\n");
	else
	{
		connection->Send(fm->ListFilesInString(userArchiveLocation));

		std::string requestedFile = fm->GetFilePathList()[connection->ReceiveInt()].second;

		connection->Send(std::string("File selected: " + requestedFile));
		connection->SendFile(requestedFile, userArchiveLocation);

		connection->SetTextColour(10);
		std::cout << connection->Receive() << std::endl;
		connection->SetTextColour(15);

		fm->ClearFileList();
	}

	
}

#pragma endregion