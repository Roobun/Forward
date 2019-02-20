//#pragma once
#include "GetInputFromConfigFile.h"

class MainLogic
{
public:
	MainLogic();
	~MainLogic();

	void Init();

private:
	void Update(GetInputFromConfigFile & data);
	void UpdateHeatingRate(GetInputFromConfigFile & data);
	void UpdateCoolingRate(GetInputFromConfigFile & data);

	int		m_outsideTemp;
	int		m_engineTemp;
	int		m_sec;
	double	m_heatingRate;
	double	m_coolingRate;


};

