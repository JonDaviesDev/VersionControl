#include "TransmissionRequestFile.h"



#pragma region Constructors

TransmissionRequestFile::TransmissionRequestFile() : Transmission(TransmissionType::REQUEST, nullptr) {}

TransmissionRequestFile::TransmissionRequestFile(ActiveConnection* connection) 
	: Transmission(TransmissionType::REQUEST, connection) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void TransmissionRequestFile::Run() {}

#pragma endregion