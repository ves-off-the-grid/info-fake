#pragma once

#define INFO_FAKE_VERSION 0.1

#include <string>
#include <vector>
#include <time.h>
#include <sstream>

#include "data.hpp"

enum class GENDER {
	MALE,
	FEMALE
};

enum class IPv4_CLASS {
	CLASS_A,
	CLASS_B,
	CLASS_C
};

class FullName {
private:
	std::string Name_;
	std::string Surname_;
public:
	FullName(std::string Name, std::string Surname) : Name_(Name), Surname_(Surname) {}

	std::vector<std::string> Unpack() {
		return { this->Name_, this->Surname_ };
	}

	std::string ToString() {
		return this->Name_ + " " + this->Surname_;
	}
};

class IPv4Address {
private:
	int FirstOctet_;
	int SecondOctet_;
	int ThirdOctet_;
	int FourthOctet_;
public:
	IPv4Address(int FirstOctet, int SecondOctet, int ThirdOctet, int FourthOctet) : FirstOctet_(FirstOctet), SecondOctet_(SecondOctet), ThirdOctet_(ThirdOctet), FourthOctet_(FourthOctet) {}

	std::vector<int> Unpack() {
		return { this->FirstOctet_, this->SecondOctet_, this->ThirdOctet_, this->FourthOctet_ };
	}

	std::string ToString() {
		std::vector<int> UnpackedAddress = this->Unpack();
		
		std::stringstream result;
		std::string StringResult = "";

		std::copy(UnpackedAddress.begin(), UnpackedAddress.end() - 1, std::ostream_iterator<int>(result, "."));

		StringResult = result.str();

		return StringResult += std::to_string(UnpackedAddress.back());
	}
};

class SSN {
private:
	int Area_;
	int Group_;
	int Serial_;
public:
	SSN(int Area, int Group, int Serial) : Area_(Area), Group_(Group), Serial_(Serial) {}

	std::vector<int> Unpack() {
		return { this->Area_, this->Group_, this->Serial_ };
	}

	std::string ToString() {
		std::vector<int> UnpackedSSN = this->Unpack();

		std::stringstream result;
		std::string StringResult = "";

		std::copy(UnpackedSSN.begin(), UnpackedSSN.end() - 1, std::ostream_iterator<int>(result, "-"));

		StringResult = result.str();

		return StringResult += std::to_string(UnpackedSSN.back());
	}
};

class CInfoFake {
public:
	FullName GetUniqueName(GENDER Gender);
	IPv4Address GetUniqueIPv4Address(IPv4_CLASS Class);
	SSN GetUniqueSSN();
};

inline CInfoFake* InfoFake = new CInfoFake;

class CUtils {
public:
	int RandomInt(int Min, int Max) {
		return Min + (rand() % (Max - Min + 1));
	}

	bool IntInRange(int Number, int Min, int Max) {
		if (Number >= Min && Number <= Max) {
			return true;
		}
		else {
			return false;
		}
	}
};

inline CUtils* Utils = new CUtils;

FullName CInfoFake::GetUniqueName(GENDER Gender) {
	srand(time(NULL));

	switch (Gender) {
	case GENDER::MALE:
		return FullName{ NAME::MALE::DATA.at(rand() % NAME::MALE::DATA.size()), SURNAME::DATA.at(rand() % NAME::MALE::DATA.size()) };
		break;
	case GENDER::FEMALE:
		return FullName{ NAME::FEMALE::DATA.at(rand() % NAME::MALE::DATA.size()), SURNAME::DATA.at(rand() % NAME::MALE::DATA.size()) };
		break;
	}
}

IPv4Address CInfoFake::GetUniqueIPv4Address(IPv4_CLASS Class) {
	srand(time(NULL));

	switch (Class) {
	case IPv4_CLASS::CLASS_A:
		return IPv4Address{ Utils->RandomInt(0, 127), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255) };
		break;
	case IPv4_CLASS::CLASS_B:
		return IPv4Address{ Utils->RandomInt(128, 191), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255) };
		break;
	case IPv4_CLASS::CLASS_C:
		return IPv4Address{ Utils->RandomInt(192, 223), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255), Utils->RandomInt(0, 255) };
		break;
	}
}

SSN CInfoFake::GetUniqueSSN() {
	srand(time(NULL));

	int Area = Utils->RandomInt(100, 899);

	if (Area == 666) {
		Area = Utils->RandomInt(100, 899);
	}
	
	return SSN{ Area, Utils->RandomInt(10, 99), Utils->RandomInt(1000, 9999) };
}
