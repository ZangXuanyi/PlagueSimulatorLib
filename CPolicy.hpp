#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "PlagueSimulatorLib.h"

namespace Ethene
{
	std::string ReadAllText(const std::string& path)
	{
		std::ifstream file(path);
		if (file)
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
		else
		{
			std::cerr << "Unable to open file" << std::endl;
			return "";
		}
	}

	class CPolicy
	{
	public:
		std::string name;
		double changeToLocalInfectivity;
		double changeToLocalSeverity;
		double changeToLocalLethality;
		double changeToLocalCorpseTransmission;
		double changeToLocalOrder;
		double changeToMedicalInput;
		bool changeToBorder;

		double cond_localInfectedRatio;
		double cond_localDeadRatio;
		double cond_localAttention;
		double cond_worldInfectedRatio;
		double cond_worldDeadRatio;
		double cond_worldAttention;

		void Execute(CCountry& country) const
		{
			country.changeToLocalCorpseTransmission += changeToLocalCorpseTransmission;
			country.changeToLocalInfectivity += changeToLocalInfectivity;
			country.changeToLocalLethality += changeToLocalLethality;
			country.changeToLocalOrder += changeToLocalOrder;
			country.changeToLocalSeverity += changeToLocalSeverity;
			country.changeToResearchInvestment += changeToMedicalInput;
			country.isBorderOpen = changeToBorder;
		}

		bool CanExecute(CWorld& world, CCountry& country) const
		{
			bool flag1 = cond_localAttention <= country.realAreaAttention;
			bool flag2 = cond_localDeadRatio <= country.deadRatio;
			bool flag3 = cond_localInfectedRatio <= country.infectedRatio;
			bool flag4 = cond_worldAttention <= world.worldAttention;
			bool flag5 = cond_worldDeadRatio <= world.deadRatio;
			bool flag6 = cond_worldInfectedRatio <= world.infectedRatio;
			if (flag1 && flag2 && flag3 && flag4 && flag5 && flag6)
				return true;
			else
				return false;
		}
	};
}