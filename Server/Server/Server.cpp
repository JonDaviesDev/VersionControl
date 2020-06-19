#include "Server.h"

#pragma region Constructors

Server::Server(tcp::INet4Address address, unsigned int maxClients) : TCPConnection(address), maximumClients(maxClients), portNumber(address.GetPort())
{
	// Standard error checking 
	ErrorCheckSERVERATTACHMENT(address);
	
	ErrorCheckLISTEN();

	// if the directory 'Archive' doesnt exist, create it
	if (!fileManager.DoesDirectoryExist(std::filesystem::current_path(), "Archive"))
		archiveLocation = fileManager.NewDirectory("Archive");
	// otherwise update attribute with its location
	else archiveLocation = std::filesystem::current_path().string() + "\\" + "Archive";

	// Update the filemanagers attribute with the location (note that the previous one was the Servers attribute)
	fileManager.SetArchiveLocation(archiveLocation);

}

#pragma endregion

#pragma region Properties

void Server::SetMaximumConnections(unsigned int value)
{
	maximumClients = value;
}

#pragma endregion

#pragma region Methods

// Generic Read/Write capability
int Server::IOManagement(SOCKET socketFileDescriptor, const char* data, int totalByteNumber)
{
	//How many bytes we have left to write...
	int nleft = totalByteNumber;
	//... and how many have been written.
	int nwritten;

	while(nleft > 0) //Write until the buffer has been written to the end.
	{
		if((nwritten = send(socketFileDescriptor, data, nleft, 0)) <= 0)
		{
			//send returned an error - handle it.
			if(nwritten < 0 && errno == EINTR)
			{
				//EINTR indicates an interrupt stopped our read.  Retry.
				nwritten = 0;
			}
			else
			{
				//Error reported by write drop out with an error code.
				return -1;
			}
		}
		else //Read successful (0 or more bytes read)
		{
			//Decrement bytes left.
			nleft -= nwritten;
			//More pointer along buffer (bytes).
			data += nwritten;
		}
	}

	//Return the amount we have left (should be 0).
	return totalByteNumber;
}

// Standard information about the client that has connected
void Server::DisplayConnectionInformation()
{
	PrintInformative("\nNew client connected");

	char messageBuffer[256];

	address.GetSocketAddress(messageBuffer, sizeof(messageBuffer));

	std::cout << "Received connection from " << messageBuffer << ": " << address.GetPort() << std::endl;
}

// This function is worked on by a dedicated thread and handled the general communication between client and server
void Server::ClientHandler(ActiveConnection clientConnection)
{
	// While both clients are connected, run this code
	try
	{
		Transmission* t;

		// Set the starting state to CONNECT
		clientConnection.SendType(TransmissionType::CONNECT);				

		// Send prompt for client username and save it (each ActiveConnection knows its own username)
		clientConnection.SetUsername(UsernameSetup(clientConnection));		

		// Start listening
		t = new TransmissionListen(&clientConnection);
		t->Run();

		while (true)
		{
			// The switch waits for a TransmissionType that the client has sent
			switch (static_cast<TransmissionType>(clientConnection.ReceiveInt()))
			{
			case TransmissionType::SENDFILE:

				t = new TransmissionSendFile(&clientConnection, &fileManager);
				t->Run();
				break;
			case TransmissionType::RECEIVEFILE:

				t = new TransmissionReceiveFile(&clientConnection, &fileManager);
				t->Run();
				break;
			case TransmissionType::CHOICE:

				t = new TransmissionChoiceSelect(&clientConnection);
				t->Run();
				break;
			case TransmissionType::NOTIFICATION:

				t = new TransmissionNotification(&clientConnection);
				t->Run();
				break;
			case TransmissionType::LISTENING:

				t = new TransmissionListen(&clientConnection);
				t->Run();
				break;
			case TransmissionType::DISCONNECT:

				t = new TransmissionDisconnect(&clientConnection);
				t->Run();
				break;

			default:
				continue;
			}
		}

		delete t;
	}
	// if the client disconnects unexpectedly, run this
	catch (...)
	{
		// Print disconnecting message in Red
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 12);
		std::cout << clientConnection.GetUsername() << " disconnected." << std::endl;
		SetConsoleTextAttribute(handle, 15);
	}
	
}

// This is the initial function for the server to run, it will spend the majority of its life inside this function
void Server::StartListening()
{
	while(true)
	{
		std::cout << "Waiting for a new connection on port " << portNumber << std::endl;

		SOCKET listeningSocket;	// This socket will only receive a connection, as soon as the thread has the data it needs, it can go back to listening


		if((listeningSocket = accept(socketFileDescriptor, (sockaddr*)address.GetSockaddrRef(), (int*)address.GetSocketAddressLengthRef())) < 0)
		{
			std::cout << "Accept error" << std::endl;

			exit(-1);
		}
		else
		{
			// Create a new connection instance
			ActiveConnection connection(listeningSocket);

			DisplayConnectionInformation();

			// Each new client will have a dedicated thread
			std::thread worker([this, connection]() { ClientHandler(connection); });

			// Let the thread work independently from the rest of the application
			worker.detach();

			// If there is more than X clients, remove the last one
			if (clientList.size() > maximumClients)
			{
				clientList.erase(clientList.end() - 1);
			}
		}
	}
}

void Server::ErrorCheckSERVERATTACHMENT(tcp::INet4Address address)
{
	if(int errorCode = bind(GetSocketFileDescriptor(), (sockaddr*)address.GetSockaddrRef(), (int)address.GetSocketAddressLengthVal()) < 0)
	{
		std::cout << "CONNECTIONTCP::ERRORCHECK-SERVERATTACHMENT::Bind Error" << std::endl;

		exit(-1);
	}
}

void Server::ErrorCheckLISTEN()
{
	if(listen(socketFileDescriptor, maximumClients))
	{
		std::cout << "CONNECTIONTCP::ERRORCHECK-LISTEN::Listen Error" << std::endl;

		exit(-1);
	}
}

std::string Server::UsernameSetup(ActiveConnection clientConnection)
{
	// Let the client know what state to enter
	clientConnection.SendType(TransmissionType::CONNECT);
	clientConnection.Send(std::string("Please enter a username: "));
		
	// Receive the name that the user has entered
	std::string username = clientConnection.Receive();

	// This allows the server to check if a user already has a directory
	if (!fileManager.DoesDirectoryExist(archiveLocation, username))
	{
		fileManager.NewDirectory(username, archiveLocation);

		clientConnection.Send(std::string("Welcome, " + username));
	}
	else clientConnection.Send(std::string("Welcome back, " + username));

	return username;
}



// Functions to change the colour of the output text for easier clarification of events
void Server::SetTextColour(int colour)
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, colour);
}

void Server::PrintPositive(const std::string& message)
{
	SetTextColour(10);
	std::cout << message << std::endl;
	SetTextColour(15);
}

void Server::PrintNegative(const std::string& message)
{
	SetTextColour(12);
	std::cout << message << std::endl;
	SetTextColour(15);
}

void Server::PrintInformative(const std::string& message)
{
	SetTextColour(11);
	std::cout << message << std::endl;
	SetTextColour(15);
}

#pragma endregion
