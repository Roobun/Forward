#include "pch.h"
#include "MainLogic.h"

MainLogic::MainLogic()
{
	m_outsideTemp = 0;
	m_engineTemp = 0;
	m_sec = 0;
	m_heatingRate = 0;
	m_coolingRate = 0;
}

MainLogic::~MainLogic()
{
}

void MainLogic::Init()
{
	std::ifstream file;
	file.open("ConfigFile.txt");

	if (!file.is_open()) {
		std::cout << "Something went wrong. Please check file named `ConfigFile.txt` in project directory" << std::endl;
	}

	GetInputFromConfigFile data = GetInputFromConfigFile();
	data.GetValuesFromFile(file);
	file.close();

	std::cout << "Enter outside temperature: ";
	std::cin >> m_outsideTemp;
	m_engineTemp = m_outsideTemp;

	while (m_engineTemp < data.GetHeatingTemp()) {
		Update(data);
	}

	std::cout << std::endl << "Total time: " << m_sec << " sec." << std::endl;
}

void MainLogic::Update(GetInputFromConfigFile & data)
{
	UpdateHeatingRate(data);
	UpdateCoolingRate(data);
	data.UpdateTorqueAndSpeed();
	m_engineTemp += m_heatingRate - m_coolingRate;

	m_sec++;
}

void MainLogic::UpdateHeatingRate(GetInputFromConfigFile & data)
{
	m_heatingRate = data.GetMoment() * data.GetDepenceOfHeatingRateOnTorque()
		+ data.GetSpeed() * data.GetSpeed() * data.GetDepenceOfHeatingRateOnSpeed();
}

void MainLogic::UpdateCoolingRate(GetInputFromConfigFile & data)
{
	m_coolingRate = data.GetDepenceOfHeatingRateOnSpeed() * (m_outsideTemp - m_engineTemp);
}
