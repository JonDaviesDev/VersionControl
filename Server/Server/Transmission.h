#pragma once
#include "TransmissionType.h"
#include "ActiveConnection.h"

#include <iostream>
#include <string>
#include <sstream>

class Transmission
{
#pragma region Attributes

protected:
	TransmissionType type;

	ActiveConnection* connection;

#pragma endregion

#pragma region Constructors

public:
	Transmission();

	Transmission(const TransmissionType& type, ActiveConnection* connection);

#pragma endregion

#pragma region Properties

public:
	void SetType(TransmissionType type);

	TransmissionType GetType();

#pragma endregion

#pragma region Methods

public:

	// Change all this, its Tims
	void Serialise(std::ostream& out);
	std::string Serialise();

	static Transmission* Unserialise(std::istream& in);
	static Transmission* Unserialise(const std::string& value);

	virtual void Run() = 0;

#pragma endregion
};

