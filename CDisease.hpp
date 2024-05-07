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
			std::string path = ".\\source\\diseaseInfo.txt";
			std::string diseaseInfo = ReadAllText(path);
			std::vector<std::string> di = Split(diseaseInfo, ',');
			name = di[0];
			infectivity = std::stod(di[1]);
			severity = std::stod(di[2]);
			lethality = std::stod(di[3]);
			wealthyResistance = std::stod(di[4]);
			povertyResistance = std::stod(di[5]);
			urbanResistance = std::stod(di[6]);
			ruralResistance = std::stod(di[7]);
			hotResistance = std::stod(di[8]);
			coldResistance = std::stod(di[9]);
			humidResistance = std::stod(di[10]);
			aridResistance = std::stod(di[11]);
			corpseTransmission = std::stod(di[12]);
			cureRequirement = 1e6 * std::stod(di[13]);
			landTransmission = std::stod(di[14]);
		}
	};
}