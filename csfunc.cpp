#pragma once
#include "PlagueSimulatorLib.hpp"
#include <format>

namespace Ethene
{
    std::string ReadAllText(const std::string &path)
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

    std::vector<std::string> ReadAllLines(const std::string &path)
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
        else
        {
            std::cerr << "Unable to open file" << std::endl;
        }
        return lines;
    }

    std::vector<std::string> Split(const std::string &str, char delimiter)
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

    std::ostream& operator<<(std::ostream& out, const CCountry& country)
    {
        std::string strN = std::format("Name:\t{}\n", country.name);
        std::string strH = std::format("healthyPopulation:\t{}\n", country.healthyPopulation);
        std::string strI = std::format("infectedPopulation:\t{}\n", country.infectedPopulation);
        std::string strD = std::format("deadPopulation:\t{}\n", country.deadPopulation);
        out << strN << strH << strI << strD;
        return out;
    }

    bool IsInset(const std::set<std::string> &mySet, const std::string &str)
    {
        auto it = mySet.find(str);
        return (it != mySet.end());
    }

    int GetRandomNumber(const int &lowerLimit, const int &upperLimit)
    {
        static std::mt19937 generator(std::random_device{}());

        // 设置分布范围
        std::uniform_int_distribution<int> distribution(lowerLimit, upperLimit);

        // 生成并返回随机数
        return distribution(generator);
    }
}