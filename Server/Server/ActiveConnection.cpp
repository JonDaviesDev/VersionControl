#include "ActiveConnection.h"

#pragma region Constructors

ActiveConnection::ActiveConnection(SOCKET external) : external(external), currentType(TransmissionType::LISTENING) {}

#pragma endregion

#pragma region Properties

SOCKET ActiveConnection::GetSocket() { return external; }

void ActiveConnection::SetUsername(std::string value) { username = value; }

std::string ActiveConnection::GetUsername() { return username; }

void ActiveConnection::SetType(TransmissionType value) { currentType = value; }

TransmissionType ActiveConnection::GetType() { return currentType; }

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

std::string ActiveConnection::Receive()
{
	// how large is the incoming data
	int dataSize = DataSizeIn();

	// create a container
	char* data = new char[dataSize + 1];

	// Read contents
	Read(data, dataSize);

	// replace garbage with a null terminator
	data[dataSize] = '\0';

	// Create a string out of the data
	std::string editedData(data);

	// delete container array
	delete[] data;

	// return string
	return editedData;
}

std::string ActiveConnection::Receive(const size_t& size)
{
	// create data container
	char* data = new char[(int)size + 1];

	// Read contents
	Read(data, (int)size);

	// replace garbage with a null terminator
	data[(int)size] = '\0';

	// create string out of data
	std::string editedData(data);

	// delete data array
	delete[] data;

	// return string
	return editedData;
}

void ActiveConnection::DataSizeOut(int size)
{
	size = htonl(size);

	char* tosend = (char*)&size;

	Write(tosend, sizeof(size));
}

void ActiveConnection::SendType(TransmissionType t)
{
	int value = static_cast<int>(t);

	int type = htonl(value);

	char* data = (char*)&type;

	Write(data, sizeof(type));
}

void ActiveConnection::SendInt(int value)
{


	char* data = (char*)&value;

	Write(data, sizeof(int));
}

int ActiveConnection::ReceiveInt()
{
	int value = 0;

	char* receiveBuffer = (char*)&value;

	Read(receiveBuffer, sizeof(int));

	return ntohl(value);
}

int ActiveConnection::DataSizeIn()
{
	int value = 0;

	char* receiveBuffer = (char*)&value;

	Read(receiveBuffer, sizeof(int));

	return ntohl(value);
}

std::pair<std::string, std::string> ActiveConnection::ReceiveFile(const size_t& size)
{
	// Recieve the data and store in string
	std::string strdata(Receive(size));

	// Search for the filename that is appended to the front of the incoming data
	std::string filename = SearchForFilename(strdata);

	// erase the appended filename so that only the actually data remains
	strdata.erase(0, filename.length() + 2);

	// if the string contains data, confirm, else deny
	if (strdata != "")
		Send(std::string("\nServer received file: " + filename));
	else Send(std::string("\nNo file contents received"));

	// return a pair containing the file name and data
	return std::make_pair(filename, strdata);
}

std::string ActiveConnection::SearchForFilename(const std::string& data)
{
	// create a substring that ranges from the first position, to the first instance of '\t' (\t is used as a terminator)
	return std::string(data.substr(1, (data.find_first_of("\t", 0)) - 1));
}

void ActiveConnection::SendFile(const std::string& file, const std::filesystem::path& fromDirectory)
{
	File* f;

	// allow files to be sent from a particular directory
	if (fromDirectory != "")
		f = new File(fromDirectory.string() + "\\" + file);
	else f = new File(file);

	std::stringstream ss((" " + f->GetFilename() + '\t') += f->ReadFile().str());

	f->Serialise(ss);

	std::string inter = ss.str();

	Send(inter);
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