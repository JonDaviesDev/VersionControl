#pragma once

#include <sstream>

#include "INet4Address.h"
#include "TCPConnection.h"
#include "File.h"
#include "ActiveConnection.h"
#include "FileManager.h"

#include "Transmission.h"
#include "TransmissionCore.h"



class Client : tcp::TCPConnection
{
#pragma region Attributes

private:
	std::unique_ptr<ActiveConnection> connection;

#pragma endregion

#pragma region Constructors

public:
	Client(char* DestinationIP, int destinationPort);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	virtual int IOManagement(SOCKET socketFileDescriptor, const char* data, int totalByteNumber);

	void StartListening();

	void ErrorCheckCLIENTATTACHMENT();

	void UsernameSetup(ActiveConnection& connection);

#pragma endregion
};

