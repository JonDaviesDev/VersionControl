#include "Client.h"

#pragma region Constructors

Client::Client(char* destinationIP, int destinationPort) 
	: TCPConnection(destinationIP, destinationPort)
{
	ErrorCheckCLIENTATTACHMENT();
}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

int Client::IOManagement(SOCKET socketFD, const char* data, int totalByteNumber)
{
	// How many bytes we have left to read
	int nLeft = totalByteNumber;

	// How many have been read
	int nRead;

	// Convert incoming data into a format that 'recv' can use
	char* tempData = (char*)data;

	// The problem was strcpy_s, I needed to change a const char* to a regular char* so that the inherited function would work with recv 
	//strcpy_s(tempData, totalByteNumber,  data);	/////////////////// THIS LINE CAUSES THE ASSERTION ERROR

	// Read until the buffer is full
	while(nLeft > 0)
	{
		if((nRead = recv(socketFD, tempData, nLeft, 0)) < 0)
		{
			// recv returned an error - handle it
			if(errno == EINTR) // host delivery failure
			{
				nRead = 0;
			}
			else
			{
				return -1; // return error code
			}
		}
		else
		{
			// No error
			if(nRead == 0)
			{
				break; // connection closed - exit loop
			}
			else // read success
			{
				// Update pointers
				nLeft -= nRead;
				data += nRead;
			}
		}
	}

	// Return the amount we have left (should be 0)
	return totalByteNumber - nLeft;
}

void Client::StartListening()
{
	// While connected
	while(true)
	{
		SOCKET receiveSocket;

		if((receiveSocket = accept(socketFileDescriptor, (sockaddr*)address.GetSockaddrRef(), (int*)address.GetSocketAddressLengthRef())) < 0)
		{
			std::cout << "Cannot accept connection." << std::endl;

			exit(-1);
		}
		else
		{
			// if the server is connected
			try
			{
				Transmission* t;
				FileManager fm;
				connection = std::make_unique<ActiveConnection>(socketFileDescriptor);

#pragma region Initialisation Information

				std::string connectionInfo = { "Connection obtained from " + address.GetSocketAddress() + ": " + std::to_string(address.GetPort()) };

				// Print connection information
				std::cout << connectionInfo << std::endl;

#pragma endregion

				while (true)
				{

					connection->SetType(connection->ReceiveType());

					switch (connection->GetType())
					{
					case TransmissionType::CONNECT:	// This was left in for future development

						t = new TransmissionConnect(connection.get());
						t->Run();
						break;
					case TransmissionType::RECEIVEFILE:

						t = new TransmissionReceiveFile(connection.get(), &fm);
						t->Run();
						break;
					case TransmissionType::SENDFILE:

						t = new TransmissionSendFile(connection.get(), &fm);
						t->Run();
						break;
					case TransmissionType::NOTIFICATION:

						t = new TransmissionNotification(connection.get());
						t->Run();
						break;
					case TransmissionType::CHOICE:

						t = new TransmissionChoiceSelect(connection.get());
						t->Run();
						break;
					case TransmissionType::DISCONNECT:

						t = new TransmissionDisconnect(connection.get());
						t->Run();
						break;
					default:
						break;
					}
				}

			}
			// if the server disconnects unexpectedly
			catch (...)
			{
				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(handle, 12);
				std::cout << "Server disconnected." << std::endl;
				std::cout << "Disconnecting..." << std::endl;
				SetConsoleTextAttribute(handle, 15);

				break;
			}


		}
	}
}

void Client::ErrorCheckCLIENTATTACHMENT()
{
	if(int errorCode = connect(socketFileDescriptor, (sockaddr*)address.GetSockaddrRef(), (int)address.GetSocketAddressLengthVal()) < 0)
	{
		std::cout << "CONNECTIONTCP::ERRORCHECK-CLIENTATTACHMENT::Connection Error" << std::endl;

		exit(-1);
	}
}

void Client::UsernameSetup(ActiveConnection& connection)
{
	connection.ReceiveType();
	std::cout << connection.Receive() << std::endl;

	std::string name;

	std::cin >> name;

	connection.SetUsername(name);

	connection.SendInt(TransmissionType::CHOICE);
	connection.Send(name);

	connection.ReceiveType();
	std::cout << connection.Receive() << std::endl;
}




#pragma endregion

