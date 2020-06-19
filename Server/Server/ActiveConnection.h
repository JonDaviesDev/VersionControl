#pragma once
#include "INet4Address.h"
#include "TCPConnection.h"
#include <filesystem>

#include "File.h"
#include "TransmissionType.h"

class ActiveConnection
{
#pragma region Attributes

private:
	SOCKET external;

	TransmissionType currentType;

	std::string username;

	HANDLE handle;

#pragma endregion

#pragma region Constructors

public:
	ActiveConnection(SOCKET external);

#pragma endregion

#pragma region Properties

public:
	SOCKET GetSocket();

	void SetUsername(std::string value);

	std::string GetUsername();

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

	int ReceiveInt();

	std::string Receive();

	std::string Receive(const size_t& size);

	virtual void DataSizeOut(int size);

	void SendType(TransmissionType t);

	virtual int DataSizeIn();

	std::pair<std::string, std::string> ReceiveFile(const size_t& size);

	std::string SearchForFilename(const std::string& data);

	void SendFile(const std::string& file, const std::filesystem::path& fromDirectory = "");

	void SetTextColour(int colour);

	void PrintPositive(const std::string& message);

	void PrintNegative(const std::string& message);

#pragma endregion
};

