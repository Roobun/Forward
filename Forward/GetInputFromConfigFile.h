#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class GetInputFromConfigFile
{
public:
	GetInputFromConfigFile();
	~GetInputFromConfigFile();

	void GetValuesFromFile(std::ifstream & file);
	void UpdateTorqueAndSpeed();

	const double GetMoment() { return m_momentOfInertia; }
	const int GetTorque() { return m_torque; }
	const double GetSpeed() { return m_speed; }
	const int GetHeatingTemp() { return m_heatingTemp; }
	const double GetDepenceOfHeatingRateOnTorque() { return m_depenceOfHeatingRateOnTorque; }
	const double GetDepenceOfHeatingRateOnSpeed() { return m_depenceOfHeatingRateOnSpeed; }
	const double GetDepenceOfCoolingRateOnTemp() { return m_depenceOfCoolingRateOnTemp; }

private:
	void InitValue(std::string valueName, std::string line);
	void InitTorqueAndSpeed(std::string line);

	double	m_momentOfInertia;
	int		m_torque;
	double	m_speed;
	int		m_heatingTemp;
	double	m_depenceOfHeatingRateOnTorque;
	double	m_depenceOfHeatingRateOnSpeed;
	double	m_depenceOfCoolingRateOnTemp;

	std::vector<std::pair<int, int>> m_depenceOfTorqueOnSpeed;
};

