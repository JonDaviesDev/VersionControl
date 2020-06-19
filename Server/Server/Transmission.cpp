#include "Transmission.h"


#pragma region Constructors

Transmission::Transmission() : connection(0) {}

Transmission::Transmission(const TransmissionType& type, ActiveConnection* connection) 
	: type(type), connection(connection) {}

#pragma endregion

#pragma region Properties

void Transmission::SetType(TransmissionType type) { this->type = type; }

TransmissionType Transmission::GetType() { return type; }

#pragma endregion

#pragma region Methods

void Transmission::Serialise(std::ostream& out)
{
	out << static_cast<int>(type) << std::endl;
}

std::string Transmission::Serialise()
{
	// change this because its Tims
	std::stringstream ss;

	Serialise(ss);
	return ss.str();
}


Transmission* Transmission::Unserialise(std::istream& in)
{
	return nullptr;
}

Transmission* Transmission::Unserialise(const std::string& value)
{
	std::stringstream ss;
	ss.str(value);
	return Unserialise(ss);
}


#pragma endregion