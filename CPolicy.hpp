#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include "PlagueSimulatorLib.h"

namespace Ethene
{
	class CPolicy
	{
	private:
		static int id;

	public:
		std::string name;
		bool isTriggered;
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
		static std::vector<CPolicy> policiesAll;

		CPolicy(const std::string& policyName,
			const double& infectivityChange,
			const double& severityChange,
			const double& lethalityChange,
			const double& corpseTransmissionChange,
			const double& orderChange,
			const double& medicalInput,
			const bool& borderChange)
		{
			name = policyName;
			id++;
			isTriggered = false;
			changeToLocalInfectivity = infectivityChange;
			changeToLocalSeverity = severityChange;
			changeToLocalLethality = lethalityChange;
			changeToLocalOrder = orderChange;
			changeToBorder = borderChange;
			changeToLocalCorpseTransmission = corpseTransmissionChange;
			changeToMedicalInput = medicalInput;
		}

		void Execute(CCountry& country) const
		{
			country.changeToLocalCorpseTransmission += changeToLocalCorpseTransmission;
			country.changeToLocalInfectivity += changeToLocalInfectivity;
			country.changeToLocalLethality += changeToLocalLethality;
			country.changeToLocalOrder += changeToLocalOrder;
			country.changeToLocalSeverity += changeToLocalSeverity;
			country.researchInvestment += changeToMedicalInput;
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