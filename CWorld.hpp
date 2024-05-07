#pragma once
#include "PlagueSimulatorLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

namespace Ethene
{
	std::vector<std::string> ReadAllLines(const std::string& path)
	{
		std::vector<std::string> lines;
		std::ifstream file(path);
		if (file.is_open()) 
		{
			std::string line;
			while (std::getline(file, line)) 
			{
				lines.push_back(line);
			}
			file.close();
		}
		else {
			std::cerr << "Unable to open file" << std::endl;
		}
		return lines;
	}

	std::vector<std::string> Split(const std::string& str, char delimiter) 
	{
		std::vector<std::string> result;
		std::istringstream iss(str);
		std::string token;

		while (std::getline(iss, token, delimiter)) 
		{
			result.push_back(token);
		}

		return result;
	}

	// VERY IMPORTANT:
	// You should initialize the world in function "main" as below:
	// CWorld world = CWorld::getWorld();
	// Else it will cause program crash!
	class CWorld {
	private:
		static CWorld world;
		CWorld() {};

		double GetWorldAttention()
		{
			double ATW = 0;
			for (const CCountry& country : countries)
				ATW += 1.7 * country.areaImportance * country.realAreaAttention;
			worldAttention = ATW / 100;
			return worldAttention;
		}

		void GetOriginalPopulation()
		{
			long OP = 0;
			for (const CCountry& country : countries)
				OP += country.originalPopulation;
			originalPopulation = OP;
		}

		void GetAllKindsOfPopulation()
		{
			long HP = 0;
			long IP = 0;
			long DP = 0;
			for (const CCountry& country : countries)
			{
				HP += country.healthyPopulation;
				IP += country.infectedPopulation;
				DP += country.deadPopulation;
			}
			healthyPopulation = HP;
			infectedPopulation = IP;
			deadPopulation = DP;
		}

		void GetPopulationRatios()
		{
			infectedRatio = static_cast<double>(infectedPopulation) / originalPopulation;
			deadRatio = static_cast<double>(deadPopulation) / originalPopulation;
		}

		void InitializeCountries()
		{
			std::string path = ".\\source\\countryInfo.txt";
			std::vector<std::string> CountryInfoAll = ReadAllLines(path);
			for (std::string CountryInfo : CountryInfoAll)
			{
				//c stands for Country; ci standards for CountryInfomation
				std::vector<std::string> ci = Split(CountryInfo, ',');
				CCountry c = *new CCountry;
				c.name = ci[0];
				c.originalPopulation = std::stol(ci[1]);
				c.researchInvestmentTotal = std::stod(ci[2]);
				c.areaImportance = std::stod(ci[3]);
				c.isArid = static_cast<bool>(std::stoi(ci[4]));
				c.isCold = static_cast<bool>(std::stoi(ci[5]));
				c.isHot = static_cast<bool>(std::stoi(ci[6]));
				c.isHumid = static_cast<bool>(std::stoi(ci[7]));
				c.isPoverty = static_cast<bool>(std::stoi(ci[8]));
				c.isRural = static_cast<bool>(std::stoi(ci[9]));
				c.isUrban = static_cast<bool>(std::stoi(ci[10]));
				c.isWealthy = static_cast<bool>(std::stoi(ci[11]));
				c.policyExecuted.clear();

				c.healthyPopulation = c.originalPopulation;
				c.infectedPopulation = 0;
				c.deadPopulation = 0;
				c.areaOrder = 1;


				countries.push_back(c);
			}
		}

		void InitializePolicies()
		{
			std::string path = ".\\source\\policyInfo.txt";
			std::vector<std::string> PolicyInfoAll = ReadAllLines(path);
			for (std::string PolicyInfo : PolicyInfoAll)
			{
				//p stands for policy; pi stands for PolicyInfomation
				std::vector<std::string> pi = Split(PolicyInfo, ',');
				CPolicy p = *new CPolicy;
				p.name = pi[0];
				p.cond_localInfectedRatio = std::stod(pi[1]);
				p.cond_localDeadRatio = std::stod(pi[2]);
				p.cond_localAttention = std::stod(pi[3]);
				p.cond_worldInfectedRatio = std::stod(pi[4]);
				p.cond_worldDeadRatio = std::stod(pi[5]);
				p.cond_worldAttention = std::stod(pi[6]);
				p.changeToLocalInfectivity = std::stod(pi[7]);
				p.changeToLocalSeverity = std::stod(pi[8]);
				p.changeToLocalLethality = std::stod(pi[9]);
				p.changeToLocalCorpseTransmission = std::stod(pi[10]);
				p.changeToLocalOrder = std::stod(pi[11]);
				p.changeToMedicalInput = std::stod(pi[12]);
				p.changeToBorder = std::stod(pi[13]);
				policiesAll.push_back(p);
			}
		}

	public:
		static CWorld& GetWorld()
		{
			return world;
		}

		std::string name;

		static std::vector<CCountry> countries;
		static std::vector<CWorld> turns;
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

		void Initialize()
		{
			countries.clear();
			turns.clear();
			policiesAll.clear();
			CDisease::GetDisease().Initialize();

			// TODO: read all countries, and push them back!
			InitializeCountries();
			// TODO: Read all Policies, and push them back!
			InitializePolicies();
			GetOriginalPopulation();
			worldAttention = 0;
			worldTotalResearch = 0;

			// TODO: Change the WorldKindness! 
			// 实际上可以用摇杆控件（大嘘）
			// 这tnnd是前端的活（大恼）
			worldKindness = 0;

			healthyPopulation = originalPopulation;
			infectedPopulation = 0;
			deadPopulation = 0;
			infectedRatio = 0;
			deadRatio = 0;
		}

		void Update(const CDisease& disease)
		{
			for (CCountry& country : world.countries)
			{
				country.Update(world, disease);
			}
			world.GetAllKindsOfPopulation();
			world.GetPopulationRatios();
			world.GetWorldAttention();
		}
	};
}