#pragma once
#include "PlagueSimulatorLib.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

namespace Ethene
{
	CWorld::CWorld(){};
	double CWorld::GetWorldAttention()
	{
		double ATW = 0;
		for (const CCountry &country : countries)
			ATW += 1.7 * country.areaImportance * country.realAreaAttention;
		worldAttention = ATW / 100;
		return worldAttention;
	}
	void CWorld::GetOriginalPopulation()
	{
		long OP = 0;
		for (const CCountry &country : countries)
			OP += country.originalPopulation;
		originalPopulation = OP;
	}
	void CWorld::GetAllKindsOfPopulation()
	{
		long HP = 0;
		long IP = 0;
		long DP = 0;
		for (const CCountry &country : countries)
		{
			HP += country.healthyPopulation;
			IP += country.infectedPopulation;
			DP += country.deadPopulation;
		}
		world.healthyPopulation = HP;
		world.infectedPopulation = IP;
		world.deadPopulation = DP;
	}
	void CWorld::GetPopulationRatios()
	{
		infectedRatio = static_cast<double>(infectedPopulation) / originalPopulation;
		deadRatio = static_cast<double>(deadPopulation) / originalPopulation;
	}
	void CWorld::InitializeCountries()
	{
		std::string path = ".\\source\\countryInfo.txt";
		std::vector<std::string> CountryInfoAll = ReadAllLines(path);
		for (std::string CountryInfo : CountryInfoAll)
		{
			// c stands for Country; ci standards for CountryInfomation
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
			c.originalDensity = static_cast<double>(std::stod(ci[12]));
			c.policyExecuted.clear();

			c.healthyPopulation = c.originalPopulation;
			c.infectedPopulation = 0;
			c.deadPopulation = 0;
			c.areaOrder = 1;

			countries.push_back(c);
		}
	}
	void CWorld::InitializePolicies()
	{
		std::string path = ".\\source\\policyInfo.txt";
		std::vector<std::string> PolicyInfoAll = ReadAllLines(path);
		for (std::string PolicyInfo : PolicyInfoAll)
		{
			// p stands for policy; pi stands for PolicyInfomation
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
	CWorld &CWorld::GetWorld()
	{
		return world;
	}
	void CWorld::Initialize()
	{
		countries.clear();
		policiesAll.clear();
		diseaseHistory.clear();
		worldHistory.clear();
		InitializeCountries();
		InitializePolicies();
		GetOriginalPopulation();
		worldAttention = 0;
		worldTotalResearch = 0;
		worldKindness = 0;
		healthyPopulation = originalPopulation;
		infectedPopulation = 0;
		deadPopulation = 0;
		infectedRatio = 0;
		deadRatio = 0;
	}
	void CWorld::Update(const CDisease &disease)
	{
		for (CCountry& country : world.countries)
		{
			country.Update(world, disease);
		}
		world.GetAllKindsOfPopulation();
		world.GetPopulationRatios();
		world.GetWorldAttention();
		worldHistory.push_back(*new std::tuple<long, long, long>(healthyPopulation, infectedPopulation, deadPopulation));
		diseaseHistory.push_back(*new std::tuple<double, double, double>(disease.infectivity, disease.severity, disease.lethality));
	}
}