// This is an example!
// �����趨��������Terra��Moon�������Թ��ң��˿ھ���1����
// ��δ���ǽ�ҩ�з���

#pragma once
#include "PlagueSimulatorLib.hpp"
#include <iostream>
#include <cstdio>

#pragma region Static Variables Initialization
std::vector<Ethene::CCountry> Ethene::CWorld::countries = {};
std::vector<Ethene::CPolicy> Ethene::CWorld::policiesAll = {};
Ethene::CDisease Ethene::CDisease::disease = *new Ethene::CDisease();
Ethene::CWorld Ethene::CWorld::world = *new Ethene::CWorld();
#pragma endregion

int main()
{
	Ethene::CWorld& world = Ethene::CWorld::GetWorld();
	Ethene::CDisease& disease = Ethene::CDisease::GetDisease();
	world.Initialize();
	disease.Initialize();
	world.countries[0].infectedPopulation = 1;
	world.countries[0].healthyPopulation -= 1;
	std::cout << world.originalPopulation << std::endl;
	std::cout << world.countries[0] << std::endl;
	std::cout << world.countries[1] << std::endl;
	while (world.deadPopulation < 50000000)
	{
		world.Update(disease);
		std::cout << world.countries[0];
		std::cout << world.countries[1] << std::endl;
	}
	return 0;
}