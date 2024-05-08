#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <map>
#include <set>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

namespace Ethene
{
	class CCountry;
	class CDisease;
	class CPolicy;
	class CWorld;

	int GetRandomNumber(const int &lowerLimit, const int &upperLimit);

	bool IsInset(const std::set<std::string> &mySet, const std::string &str);

	std::string ReadAllText(const std::string &path);

	std::vector<std::string> ReadAllLines(const std::string &path);

	std::vector<std::string> Split(const std::string &str, char delimiter);

	class CCountry
	{
	private:
		double originalDensity;
		double subjectiveWorldAttention = 0;
		CCountry &GetThis();
		double GetCurrentDensity() const;
		double GetCurrentDensity(const CDisease &disease) const;
		double GetLocalResistance(const CDisease &disease) const;
		double GetCurrentLocalRealInfectivity(const CDisease &disease) const;
		long GetCurrentPopulation() const;
		double GetCurrentAreaAttention(CWorld &world, const CDisease &disease);
		double GetCurrentAreaOrder(const CDisease &disease) const;
		long AddInfected(const CDisease &disease);
		long AddDeath(const CDisease &disease);
		double GetCurrentRealMedicalInput(const CDisease &disease) const;
		double GetCurrentSubjectiveWorldAttention(const CWorld &world);
		void CrossBorder(CWorld &world, const CDisease &disease) const;
		void ExecutePolicies(CWorld &world);
		void GetCurrentInvestment();

	public:
		std::string name;
		long originalPopulation;
		long healthyPopulation;
		long infectedPopulation = 0;
		long deadPopulation = 0;
		double infectedRatio = 0;
		double deadRatio = 0;
		double realAreaAttention = 0;
		double areaOrder = 1;
		double researchInvestment = 0;
		double researchInvestmentTotal;
		double areaImportance;
		bool isWealthy;
		bool isPoverty;
		bool isUrban;
		bool isRural;
		bool isHot;
		bool isCold;
		bool isHumid;
		bool isArid;
		bool isBorderOpen = true;
		double changeToLocalInfectivity = 0;
		double changeToLocalSeverity = 0;
		double changeToLocalLethality = 0;
		double changeToLocalCorpseTransmission = 0;
		double changeToLocalOrder = 0;
		double changeToResearchInvestment = 0;
		std::set<std::string> policyExecuted;
		void Update(CWorld &world, const CDisease &disease);
	};

	class CDisease
	{
	private:
		static CDisease disease;
		CDisease();

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
		static CDisease &GetDisease();
		void Initialize();
	};

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

		void Execute(CCountry &country) const;

		bool CanExecute(CWorld &world, CCountry &country) const;
	};

	class CWorld
	{
	private:
		static CWorld world;
		CWorld();
		double GetWorldAttention();
		void GetOriginalPopulation();
		void GetAllKindsOfPopulation();
		void GetPopulationRatios();
		void InitializeCountries();
		void InitializePolicies();

	public:
		static CWorld &GetWorld();
		std::string name;
		static std::vector<CCountry> countries;
		static std::vector<CPolicy> policiesAll;
		double worldAttention;
		double worldTotalResearch;
		double worldKindness;
		long originalPopulation;
		long infectedPopulation;
		long healthyPopulation;
		long deadPopulation;
		double infectedRatio;
		double deadRatio;
		void Initialize();
		void Update(const CDisease &disease);
	};
}
