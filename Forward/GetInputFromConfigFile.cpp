#include "pch.h"
#include "GetInputFromConfigFile.h"

GetInputFromConfigFile::GetInputFromConfigFile()
{
	m_momentOfInertia = 0;
	m_torque = 0;
	m_heatingTemp = 0;
	m_depenceOfCoolingRateOnTemp = 0;
	m_depenceOfHeatingRateOnSpeed = 0;
	m_depenceOfHeatingRateOnTorque = 0;
}

GetInputFromConfigFile::~GetInputFromConfigFile()
{
}

void GetInputFromConfigFile::GetValuesFromFile(std::ifstream & file)
{
	std::string line;
	while (!file.eof()) {
		std::getline(file, line);

		InitValue("I", line);
		InitValue("T", line);
		InitValue("Hm", line);
		InitValue("Hv", line);
		InitValue("C", line);

		InitTorqueAndSpeed(line);
	}
}

void GetInputFromConfigFile::UpdateTorqueAndSpeed()
{
	m_speed += m_momentOfInertia * m_torque;
	
	int tempTorque = 0;
	for (auto & item : m_depenceOfTorqueOnSpeed) {
		tempTorque = item.first;
		if (m_speed < item.second) {
			m_torque = tempTorque;
		} else {
			break;
		}
	}
}

void GetInputFromConfigFile::InitValue(std::string valueName, std::string line)
{
	if (!line.empty() && line.find(valueName) != std::string::npos) {
		int pos = line.find("=");
		std::string valueString = line.substr(pos + 1, line.length() - pos);
		double value;
		std::stringstream(valueString) >> value;
		if (valueName == "I") {
			m_momentOfInertia = value;
		} else if (valueName == "T") {
			m_heatingTemp = value;
		} else if (valueName == "Hm") {
			m_depenceOfHeatingRateOnTorque = value;
		} else if (valueName == "Hv") {
			m_depenceOfHeatingRateOnSpeed = value;
		} else if (valueName == "C") {
			m_depenceOfCoolingRateOnTemp = value;
		}
	}
}

void GetInputFromConfigFile::InitTorqueAndSpeed(std::string line)
{
	if (!line.empty() && line.find("M") != std::string::npos) {
		int findV = line.find("V");
		std::string mString = line.substr(3, findV);
		std::string vString = line.substr(findV + 3, line.length() - findV);

		std::stringstream mStream(mString);
		std::stringstream vStream(vString);

		int mValue;
		int vValue;
		while (mStream >> mValue && vStream >> vValue) {
			m_depenceOfTorqueOnSpeed.push_back(std::pair<int, int>(mValue, vValue));
			
			if (mStream.peek() == ',')
			{
				mStream.ignore();
				vStream.ignore();
			}
		}

		m_torque = m_depenceOfTorqueOnSpeed.at(0).first;
		m_speed = m_depenceOfTorqueOnSpeed.at(0).second;
	}
}