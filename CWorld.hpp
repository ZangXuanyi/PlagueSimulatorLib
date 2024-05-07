#pragma once
#include "PlagueSimulatorLib.h"
#include <iostream>
#include <vector>

namespace Ethene
{
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

		void AddCountry(const CCountry& country)
		{
			countries.push_back(country);
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

	public:
		static CWorld& GetWorld()
		{
			return world;
		}

		std::string name;
		static std::vector<CCountry> countries;
		static std::vector<CWorld> turns;

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
			CDisease::GetDisease().Initialize();

			// TODO: read all countries, and push them back!

			GetOriginalPopulation();
			worldAttention = 0;
			worldTotalResearch = 0;

			// TODO: Change the WorldKindness! 

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