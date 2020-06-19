#include "Client.h"

// Because there is a lot of shared functionality between the client and the server,
// most commenting has been done in the Server application.

int main()
{
	char ip[] = "127.0.0.1";

	Client client(ip, 50024);

	client.StartListening();

	return 0;
}