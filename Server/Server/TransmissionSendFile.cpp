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
	size_t incomingSize = connection->ReceiveInt();

	/* This line of code does multipe things -

		1st. Sends out a message to the client asking for them to provide a username in the
			 function called 'UsernameSetup'.  It then receives this as a string and returns it.

		2nd. the fileManager creates a new directory branching off the archivelocation with the name that the user provided.

		3rd. ReceieveFile reads the entirety of the file sent by the client and returns it as a string object.

		4th. ConstructFile takes the contents of the file and the path of the new directory and forms the file in that location.


		The function for UsernameSetup has been made the second parameter because functions processes their parameters from right
		to left, and the username was required for the file constuction first.

	*/
	fm->ConstructFile(connection->ReceiveFile(incomingSize),
		fm->NewDirectory(connection->GetUsername(), fm->GetArchiveLocation()));

	connection->SendInt(static_cast<int>(TransmissionType::LISTENING));
}

#pragma endregion