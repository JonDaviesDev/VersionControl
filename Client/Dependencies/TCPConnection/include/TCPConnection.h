#pragma once

#include "INet4Address.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

namespace tcp
{
	class TCPConnection
	{
#pragma region Attributes

	protected:
		WSADATA wsaData;

		INet4Address address;

		SOCKET socketFileDescriptor;

#pragma endregion

#pragma region Constructors

	public:
		TCPConnection();

		TCPConnection(int port);

		TCPConnection(std::string IP, int port);

		TCPConnection(char* IP, int port);

		TCPConnection(INet4Address client);

#pragma endregion

#pragma region Properties

#pragma region Setters

	public:
		void SetINet4Address(INet4Address value);

		void SetSocket(SOCKET value);

#pragma endregion

#pragma region Getters

	public:
		INet4Address GetInet4Address();

		SOCKET GetSocketFileDescriptor();

#pragma endregion

#pragma endregion

#pragma region Methods

	protected:
		void ErrorCheckWSADATA();

		void ErrorCheckSOCKET();

		void ErrorCheckACCEPT(SOCKET socket);

		virtual int IOManagement(SOCKET socketFileDescriptor, const char* data, int totalByteNumber) = 0;

		virtual void DataSize();

#pragma endregion
	};
}