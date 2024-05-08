#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "PlagueSimulatorLib.hpp"

namespace Ethene
{
	void CPolicy::Execute(CCountry &country) const
	{
		country.changeToLocalCorpseTransmission += changeToLocalCorpseTransmission;
		country.changeToLocalInfectivity += changeToLocalInfectivity;
		country.changeToLocalLethality += changeToLocalLethality;
		country.changeToLocalOrder += changeToLocalOrder;
		country.changeToLocalSeverity += changeToLocalSeverity;
		country.changeToResearchInvestment += changeToMedicalInput;
		country.isBorderOpen = changeToBorder;
	}
	bool CPolicy::CanExecute(CWorld &world, CCountry &country) const
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
}