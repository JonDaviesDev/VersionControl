#include "Server.h"

int main()
{
	tcp::INet4Address info(50024);

	Server server(info, 100);

	server.StartListening();

	return 0;
}