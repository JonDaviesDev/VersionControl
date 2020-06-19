#include "Transmission.h"


#pragma region Constructors

Transmission::Transmission() : connection(nullptr) {}

Transmission::Transmission(const TransmissionType& type, ActiveConnection* connection)
	: type(type), connection(connection) {}

#pragma endregion

#pragma region Properties

void Transmission::SetType(TransmissionType type) { this->type = type; }

TransmissionType Transmission::GetType() { return type; }

#pragma endregion

#pragma region Methods

#pragma endregion