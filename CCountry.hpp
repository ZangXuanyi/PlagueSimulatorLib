#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <map>
#include <set>
#include <random>
#include <cmath>
#include "PlagueSimulatorLib.h"

// Weighted Average Calculator by KimiChat
template<typename T>
T weightedAverage(const std::vector<T>& values, const std::vector<T>& weights) {
	T sum = 0;
	T weightSum = 0;
	if (values.size() != weights.size()) {
		throw std::invalid_argument("Values and weights must be the same size.");
	}
	for (size_t i = 0; i < values.size(); ++i) {
		sum += values[i] * weights[i];
		weightSum += weights[i];
	}
	if (weightSum == 0) {
		throw std::runtime_error("Sum of weights cannot be zero.");
	}
	return sum / weightSum;
}

// Random number getter by KimiChat
template<typename T>
T GetRandomNumber(const T& lowerLimit, const T& upperLimit)
{
	static std::mt19937 gen;
	std::uniform_real_distribution<T> distribution(lowerLimit, upperLimit);
	return distribution(gen);
}



namespace Ethene
{
	class CCountry {
	private:
		double originalDensity;
		double subjectiveWorldAttention = 0;

		// to get itself...
		CCountry& GetThis()
		{
			return *this;
		}

		// To get current density without corpse transmission
		double GetCurrentDensity() const
		{
			return ((double)healthyPopulation + (double)infectedPopulation) / (double)originalPopulation * originalDensity;
		}

		// To get current density with corpse transmission
		double GetCurrentDensity(const CDisease& disease) const
		{
			return (static_cast<double>(healthyPopulation)
				+ static_cast<double>(infectedPopulation)
				+ static_cast<double>(deadPopulation)
				* (disease.corpseTransmission + changeToLocalCorpseTransmission))
				/ static_cast<double>(originalPopulation) * originalDensity;
		}

		// To get local resistance
		double GetLocalResistance(const CDisease& disease) const
		{
			double resistance = 0;
			double weights = 0;
			bool areaResistances[8] = { isWealthy, isPoverty, isUrban, isRural, isHot, isCold, isHumid, isArid };
			double diseaseResistances[8] =
			{
				disease.wealthyResistance,
				disease.povertyResistance,
				disease.urbanResistance,
				disease.ruralResistance,
				disease.hotResistance,
				disease.coldResistance,
				disease.humidResistance,
				disease.aridResistance
			};
			double weightsMap[8] = { 30, 30, 3, 3, 10, 10, 2, 2 };
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

		// To get local real infectivity
		double GetCurrentLocalRealInfectivity(const CDisease& disease) const
		{
			return (GetLocalResistance(disease) * disease.infectivity + changeToLocalInfectivity);
		}

		// To get people alive, heathy and infected
		long GetCurrentPopulation() const
		{
			return healthyPopulation + infectedPopulation;
		}

		// To get current attention
		double GetCurrentAreaAttention(CWorld& world, const CDisease& disease)
		{
			double areaSeverity = std::max(0.05, disease.severity + changeToLocalSeverity);
			double areaSeverityRatio = areaSeverity / (areaSeverity + 30.0);
			double areaSeverityPower = infectedPopulation >= 10 ?
				std::powf(static_cast<double>(areaSeverity), 2.0) / 100000.0 : 0;
			double infectedSense =
				1.5
				* std::powf(infectedRatio, 2.0)
				* std::powf(areaSeverity, 2.0)
				+ areaSeverityPower;
			double deathSense =
				3.0 * deadRatio
				/ (0.3 + deadRatio);
			double areaAttention = infectedSense + deathSense;
			realAreaAttention = (areaAttention + world.worldKindness * subjectiveWorldAttention) / (1 + world.worldKindness);
			return realAreaAttention;
		}

		// To get area order
		double GetCurrentAreaOrder(const CDisease& disease) const
		{
			double areaSeverity = std::max(0.05, disease.severity + changeToLocalSeverity);
			double os =
				-2.0 * infectedRatio * std::powf(areaSeverity, 2.0)
				/ (18225.0 * (infectedRatio + 0.5));
			double od =
				-1.15 * std::powf(deadRatio, 2.0);
			double CAO = 1 + os + od + changeToLocalOrder;
			return CAO > 0 ? CAO : 0;
		}

		// Add today's infected population. the return is the change to population.
		long AddInfected(const CDisease& disease)
		{
			if (healthyPopulation == 0)
			{
				return 0;
			}
			double isr = GetCurrentLocalRealInfectivity(disease) * infectedPopulation / 100.0;
			double i_d = deadPopulation * (disease.corpseTransmission + changeToLocalCorpseTransmission) * GetCurrentDensity();
			double I_S = (i_d + GetCurrentDensity()) * isr;
			long deltaFromAlive = GetRandomNumber(0.5, 1.0) * I_S * infectedPopulation;
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

		// Add today's dead population. the return is the change to population.
		long AddDeath(const CDisease& disease)
		{
			long delta = (disease.lethality + changeToLocalLethality) * GetRandomNumber(0.5, 1.0) * infectedPopulation / 100;
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

		// Get current medical input, which is order multiplies the real input.
		double GetCurrentRealMedicalInput(const CDisease& disease) const
		{
			double CRMI = GetCurrentAreaOrder(disease) * researchInvestment;
			return CRMI > 0 ? CRMI : 0;
		}

		// To get current world attention the area thinks
		double GetCurrentSubjectiveWorldAttention(const CWorld& world)
		{
			subjectiveWorldAttention = world.worldAttention * areaImportance;
			return subjectiveWorldAttention;
		}

		// To get if the disease can cross the border, and cross it
		void CrossBorder(CWorld& world, const CDisease& disease) const
		{
			double openBorder = isBorderOpen ? 3.0 : 1.0;
			for (CCountry& country : world.countries)
			{
				if (country.name == name) continue;
				else if (country.infectedPopulation > 0)continue;
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

		// To get the executable policies and execute them
		void ExecutePolicies(CWorld& world)
		{
			for (CPolicy& policy : CPolicy::policiesAll)
			{
				CCountry& instance = GetThis();
				if (policy.CanExecute(world, instance) == true && !IsInset(policyExecuted, policy.name))
				{
					policy.Execute(instance);
					policyExecuted.insert(policy.name);
				}
			}
		}

		template<typename T>
		bool IsInset(const std::set<T>& mySet, const T& str)
		{
			// 使用 find 方法查找 str 是否存在于 mySet 中
			auto it = mySet.find(str);
			if (it != mySet.end())
				return true;
			else
				return false;
		}

	public:
		std::string name;

		long originalPopulation;
		long healthyPopulation;
		long infectedPopulation;
		long deadPopulation;

		double infectedRatio;
		double deadRatio;

		double realAreaAttention;
		double areaOrder = 1;
		double researchInvestment;
		double areaImportance;
		bool isWealthy;
		bool isPoverty;
		bool isUrban;
		bool isRural;
		bool isHot;
		bool isCold;
		bool isHumid;
		bool isArid;
		bool isAware;

		bool isBorderOpen;

		double changeToLocalInfectivity = 0;
		double changeToLocalSeverity = 0;
		double changeToLocalLethality = 0;
		double changeToLocalCorpseTransmission = 0;
		double changeToLocalOrder = 0;

		std::set<std::string> policyExecuted;

		void Update(CWorld& world, const CDisease& disease)
		{
			AddDeath(disease);
			AddInfected(disease);
			GetCurrentAreaAttention(world, disease);
			if (infectedPopulation != 0)
				CrossBorder(world, disease);
			world.worldTotalResearch += GetCurrentRealMedicalInput(disease);
			ExecutePolicies(world);
		}
	};
}