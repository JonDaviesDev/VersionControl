#include "ActiveConnection.h"


#pragma region Constructors

ActiveConnection::ActiveConnection(SOCKET external) : external(external) {}

#pragma endregion

#pragma region Properties

SOCKET ActiveConnection::GetSocket() { return external; }

void ActiveConnection::SetType(TransmissionType value) { currentType = value; }

TransmissionType ActiveConnection::GetType() { return currentType; }

void ActiveConnection::SetUsername(const std::string& value) { username = value; }

#pragma endregion

#pragma region Methods

int ActiveConnection::Read(char* data, int totalByteNumber)
{
	// How many bytes we have left to read
	int nLeft = totalByteNumber;

	// How many have been read
	int nRead;

	// Convert incoming data into a format that 'recv' can use
	char* tempData = (char*)data;

	// Read until the buffer is full
	while (nLeft > 0)
	{
		if ((nRead = recv(external, tempData, nLeft, 0)) < 0)
		{
			// recv returned an error - handle it
			if (errno == EINTR) // host delivery failure
			{
				nRead = 0;
			}
			else
			{
				throw - 1; // return error code
			}
		}
		else
		{
			// No error
			if (nRead == 0)
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

int ActiveConnection::Write(const char* data, int totalByteNumber)
{
	//How many bytes we have left to write...
	int nleft = totalByteNumber;
	//... and how many have been written.
	int nwritten;

	while (nleft > 0) //Write until the buffer has been written to the end.
	{
		if ((nwritten = send(external, data, nleft, 0)) <= 0)
		{
			//send returned an error - handle it.
			if (nwritten < 0 && errno == EINTR)
			{
				//EINTR indicates an interrupt stopped our read.  Retry.
				nwritten = 0;
			}
			else
			{
				//Error reported by write drop out with an error code.
				throw - 1;
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

void ActiveConnection::Send(const std::string& data)
{
	DataSizeOut(data.length());

	Write(data.c_str(), data.length());
}

void ActiveConnection::SendInt(int value)
{
	value = htonl(value);

	char* data = (char*)&value;

	Write(data, sizeof(int));
}

void ActiveConnection::SendInt(TransmissionType type)
{
	int value = static_cast<int>(type);

	value = htonl(value);

	char* data = (char*)&value;

	Write(data, sizeof(int));
}

std::string ActiveConnection::Receive()
{
	int dataSize = DataSizeIn();

	char* data = new char[dataSize + 1];

	Read(data, dataSize);

	data[dataSize] = '\0';
		
	std::string editedData(data);

	delete[] data;

	return editedData;
}

std::string ActiveConnection::Receive(const size_t& size)
{
	char* data = new char[(int)size + 1];

	Read(data, (int)size);

	data[(int)size] = '\0';

	std::string editedData(data);

	delete[] data;

	return editedData;
}

int ActiveConnection::ReceiveInt()
{
	int value = 0;

	char* receiveBuffer = (char*)&value;

	Read(receiveBuffer, sizeof(int));

	return ntohl(value);
}

TransmissionType ActiveConnection::ReceiveType()
{
	int value = 0;

	char* data = (char*)&value;

	Read(data, sizeof(int));

	return static_cast<TransmissionType>(ntohl(value));
}

int ActiveConnection::DataSizeIn()
{
	int value = 0;

	char* receiveBuffer = (char*)&value;

	Read(receiveBuffer, sizeof(int));

	return ntohl(value);
}

std::pair<u_long, u_long> ActiveConnection::DataInformationIn()
{
	int value1 = 0;
	int value2 = 0;

	char* sizeBuffer = (char*)&value1;
	char* typeBuffer = (char*)&value2;

	Read(sizeBuffer, sizeof(int));
	Read(typeBuffer, sizeof(int));

	int s = ntohl(value1);

	return std::make_pair(ntohl(value1), ntohl(value2));
}

void ActiveConnection::DataSizeOut(int size)
{
	size = htonl(size);

	char* tosend = (char*)&size;

	Write(tosend, sizeof(size));
}

void ActiveConnection::SendFile(const std::string& file)
{
	File f(file);

	std::stringstream ss((" " + file + '\t') += f.ReadFile().str());

	f.Serialise(ss);

	std::string inter = ss.str();

	Send(inter);
}

std::pair<std::string, std::string> ActiveConnection::ReceiveFile(const size_t& size)
{
	std::string strdata(Receive(size));

	std::string filename = SearchForFilename(strdata);

	strdata.erase(0, filename.length() + 2);

	if (strdata != "")
	{
		Send(std::string("\n" + username + " received file: " + filename));
	}
	else
	{
		Send(std::string("\n" + username + " did not receive file"));
	}

	return std::make_pair(filename, strdata);
}

std::string ActiveConnection::SearchForFilename(const std::string& data)
{
	return std::string(data.substr(1, (data.find_first_of("\t", 0)) - 1));
}

void ActiveConnection::SetTextColour(int colour)
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, colour);
}

void ActiveConnection::PrintPositive(const std::string& message)
{
	SetTextColour(10);
	std::cout << message << std::endl;
	SetTextColour(15);
}

void ActiveConnection::PrintNegative(const std::string& message)
{
	SetTextColour(12);
	std::cout << message << std::endl;
	SetTextColour(15);
}

#pragma endregion