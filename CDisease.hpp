#pragma once
#include "PlagueSimulatorLib.h"
#include <iostream>
#include <cstdio>

namespace Ethene
{
	class CDisease {
	private:
		static CDisease disease;
		CDisease() {};
	public:
		std::string name;
		double infectivity;
		double severity;
		double lethality;
		double wealthyResistance;
		double povertyResistance;
		double urbanResistance;
		double ruralResistance;
		double hotResistance;
		double coldResistance;
		double humidResistance;
		double aridResistance;
		double corpseTransmission;
		double cureRequirement;
		double landTransmission;

		static CDisease& GetDisease()
		{
			return disease;
		}

		void Initialize()
		{
			// TODO: read in a txt and initialize the disease
		}
	};
}