#pragma once

#include "INet4Address.h"
#include "TCPConnection.h"
#include "FileManager.h"
#include "File.h"
#include "ActiveConnection.h"
#include "Transmission.h"
#include "TransmissionCore.h"

#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <vector>
#include <functional>

class Server : tcp::TCPConnection
{
#pragma region Attributes

	unsigned int maximumClients;

	unsigned int portNumber;

	FileManager fileManager;

	std::filesystem::path archiveLocation;
	
	std::vector<std::pair<ActiveConnection, std::string>> clientList;

	HANDLE handle;

#pragma endregion

#pragma region Constructors

public:
	Server(tcp::INet4Address address, unsigned int maxClients);

#pragma endregion

#pragma region Properties

public:
	void SetMaximumConnections(unsigned int value);

#pragma endregion

#pragma region Methods

public:
	virtual int IOManagement(SOCKET socketFileDescriptor, const char* data, int totalByteNumber);

	void DisplayConnectionInformation();

	void ClientHandler(ActiveConnection clientConnection);

	void StartListening();

	void ErrorCheckSERVERATTACHMENT(tcp::INet4Address address);

	void ErrorCheckLISTEN();

	std::string UsernameSetup(ActiveConnection clientConnection);

	void SetTextColour(int colour);

	void PrintPositive(const std::string& message);

	void PrintNegative(const std::string& message);

	void PrintInformative(const std::string& message);

#pragma endregion

};

