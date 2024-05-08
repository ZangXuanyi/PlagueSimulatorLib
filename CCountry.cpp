#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <map>
#include <set>
#include <random>
#include <cmath>
#include "PlagueSimulatorLib.hpp"

namespace Ethene
{
	// to get itself...
	CCountry &CCountry::GetThis()
	{
		return *this;
	}
	double CCountry::GetCurrentDensity() const
	{
		return ((double)healthyPopulation + (double)infectedPopulation) / (double)originalPopulation * originalDensity;
	}
	double CCountry::GetCurrentDensity(const CDisease &disease) const
	{
		return (static_cast<double>(healthyPopulation) + static_cast<double>(infectedPopulation) + static_cast<double>(deadPopulation) * (disease.corpseTransmission + changeToLocalCorpseTransmission)) / static_cast<double>(originalPopulation) * originalDensity;
	}
	double CCountry::GetLocalResistance(const CDisease &disease) const
	{
		double resistance = 0;
		double weights = 0;
		bool areaResistances[8] = {isWealthy, isPoverty, isUrban, isRural, isHot, isCold, isHumid, isArid};
		double diseaseResistances[8] =
			{
				disease.wealthyResistance,
				disease.povertyResistance,
				disease.urbanResistance,
				disease.ruralResistance,
				disease.hotResistance,
				disease.coldResistance,
				disease.humidResistance,
				disease.aridResistance};
		double weightsMap[8] = {30, 30, 3, 3, 10, 10, 2, 2};
		for (int i = 0; i < 8; i++)
		{
			if (areaResistances[i] != 0)
			{
				weights += weightsMap[i];
				resistance += diseaseResistances[i] * weightsMap[i];
			}
		}
		return resistance / weights;
	}
	double CCountry::GetCurrentLocalRealInfectivity(const CDisease &disease) const
	{
		return (GetLocalResistance(disease) * disease.infectivity + changeToLocalInfectivity);
	}
	long CCountry::GetCurrentPopulation() const
	{
		return healthyPopulation + infectedPopulation;
	}
	double CCountry::GetCurrentAreaAttention(CWorld &world, const CDisease &disease)
	{
		double areaSeverity = std::max(0.05, disease.severity + changeToLocalSeverity);
		double areaSeverityRatio = areaSeverity / (areaSeverity + 30.0);
		double areaSeverityPower = infectedPopulation >= 10 ? static_cast<double>(areaSeverity*areaSeverity) / 100000.0 : 0;
		double infectedSense =
			1.5 * infectedRatio*infectedRatio * areaSeverity*areaSeverity + areaSeverityPower;
		double deathSense =
			3.0 * deadRatio / (0.3 + deadRatio);
		double areaAttention = infectedSense + deathSense;
		realAreaAttention = (areaAttention + world.worldKindness * subjectiveWorldAttention) / (1 + world.worldKindness);
		return realAreaAttention;
	}
	double CCountry::GetCurrentAreaOrder(const CDisease &disease) const
	{
		double areaSeverity = std::max(0.05, disease.severity + changeToLocalSeverity);
		double os =
			-2.0 * infectedRatio * (areaSeverity*areaSeverity) / (18225.0 * (infectedRatio + 0.5));
		double od =
			-1.15 * deadRatio*deadRatio;
		double CAO = 1 + os + od + changeToLocalOrder;
		return CAO > 0 ? CAO : 0;
	}
	long CCountry::AddInfected(const CDisease &disease)
	{
		if (healthyPopulation == 0)
		{
			return 0;
		}
		double isr = GetCurrentLocalRealInfectivity(disease) * infectedPopulation / 100.0;
		double i_d = deadPopulation * (disease.corpseTransmission + changeToLocalCorpseTransmission) * GetCurrentDensity();
		double I_S = (i_d + GetCurrentDensity()) * isr;
		long deltaFromAlive = GetRandomNumber(5, 10) * I_S * infectedPopulation/10;
		if (healthyPopulation > deltaFromAlive)
		{
			healthyPopulation -= deltaFromAlive;
			infectedPopulation += deltaFromAlive;
		}
		else if (deltaFromAlive == 0)
		{
			deltaFromAlive = 1;
			healthyPopulation -= 1;
			infectedPopulation += 1;
		}
		else
		{
			infectedPopulation += healthyPopulation;
			deltaFromAlive = healthyPopulation;
			healthyPopulation = 0;
		}
		infectedRatio = static_cast<double>(infectedPopulation) / originalPopulation;
		return deltaFromAlive;
	}
	long CCountry::AddDeath(const CDisease &disease)
	{
		long delta = (disease.lethality + changeToLocalLethality) * GetRandomNumber(5, 10) * infectedPopulation / 1000;
		if (infectedPopulation > delta)
		{
			infectedPopulation -= delta;
			deadPopulation += delta;
		}
		else if (delta == 0)
		{
			delta = 1;
			infectedPopulation -= 1;
			deadPopulation += 1;
		}
		else
		{
			delta = infectedPopulation;
			deadPopulation += deadPopulation;
			infectedPopulation = 0;
		}
		deadRatio = static_cast<double>(deadPopulation) / originalPopulation;
		return delta;
	}
	double CCountry::GetCurrentRealMedicalInput(const CDisease &disease) const
	{
		double CRMI = GetCurrentAreaOrder(disease) * researchInvestment;
		return CRMI > 0 ? CRMI : 0;
	}
	double CCountry::GetCurrentSubjectiveWorldAttention(const CWorld &world)
	{
		subjectiveWorldAttention = world.worldAttention * areaImportance;
		return subjectiveWorldAttention;
	}
	void CCountry::CrossBorder(CWorld &world, const CDisease &disease) const
	{
		double openBorder = isBorderOpen ? 3.0 : 1.0;
		for (CCountry &country : world.countries)
		{
			if (country.name == name)
				continue;
			else if (country.infectedPopulation > 0)
				continue;
			else
			{
				double dice1 = GetRandomNumber(1, 50);
				double dice2 = GetRandomNumber(10, 100);
				double crossAbility = disease.landTransmission * infectedRatio * dice1 * 2000;
				double openBorderOther = country.isBorderOpen ? 3.0 : 1.0;
				if (crossAbility * openBorder * openBorderOther > dice2)
				{
					int dice3 = GetRandomNumber(1, 10);
					country.infectedPopulation += dice3;
					country.healthyPopulation -= dice3;
				}
			}
		}
	}
	void CCountry::ExecutePolicies(CWorld &world)
	{
		int len = world.policiesAll.size();
		for (int i = 0; i<len; i++)
		{
			CPolicy& policy = world.policiesAll[i];
			CCountry &instance = GetThis();
			if (policy.CanExecute(world, instance) == true && !IsInset(policyExecuted, policy.name))
			{
				policy.Execute(instance);
				policyExecuted.insert(policy.name);
			}
		}
	}
	void CCountry::GetCurrentInvestment()
	{
		researchInvestment = researchInvestmentTotal * changeToResearchInvestment;
	}
	void CCountry::Update(CWorld &world, const CDisease &disease)
	{
		AddDeath(disease);
		AddInfected(disease);
		GetCurrentAreaAttention(world, disease);
		if (infectedPopulation != 0)
			CrossBorder(world, disease);
		world.worldTotalResearch += GetCurrentRealMedicalInput(disease);
		ExecutePolicies(world);
	}
}