#pragma once

#include <INet4Address.h>
#include <TCPConnection.h>


#include "File.h"
#include "TransmissionType.h"

class ActiveConnection
{
#pragma region Attributes

private:
	SOCKET external;

	TransmissionType currentType;

	HANDLE handle;

	std::string username;

#pragma endregion

#pragma region Constructors

public:
	ActiveConnection(SOCKET external);

#pragma endregion

#pragma region Properties

public:
	SOCKET GetSocket();

	void SetUsername(const std::string& value);

	void SetType(TransmissionType value);

	TransmissionType GetType();

#pragma endregion

#pragma region Methods

public:

	// Allow the ability to read incoming streams
	int Read(char* data, int totalByteNumber);

	// Allow the ability to write streams
	int Write(const char* data, int totalByteNumber);

	void Send(const std::string& data);

	void SendInt(int value);

	void SendInt(TransmissionType type);

	std::string Receive();

	std::string Receive(const size_t& size);

	int ReceiveInt();

	TransmissionType ReceiveType();

	int DataSizeIn();
	std::pair<u_long, u_long> DataInformationIn();

	void DataSizeOut(int size);

	void SendFile(const std::string& file);

	void RequestFile(const std::string& filename);

	std::pair<std::string, std::string> ReceiveFile(const size_t& size);

	std::string SearchForFilename(const std::string& data);

	void SetTextColour(int colour);

	void PrintPositive(const std::string& message);

	void PrintNegative(const std::string& message);

#pragma endregion
};

