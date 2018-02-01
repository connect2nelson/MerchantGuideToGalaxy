
#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H


#include <string>
#include <sstream>
#include <vector>

#include "NumericalSystem.h"
#include "ItemUnitRate.h"


#include "RomanNumeral.h"
#include "StringHelperFunctions.h"

class DataCollector 
{
	enum class ETypeOfData
	{
		SYMBOL_TABLE_DATA,
		RATE_PER_UNIT_DATA,
		INVALID_DATA
	};

	ETypeOfData getTypeOfData(const std::string& data)
	{
		if (data.find("is") != std::string::npos && data.find("Credits") != std::string::npos)
			return ETypeOfData::RATE_PER_UNIT_DATA;
		else if (data.find("is") != std::string::npos)
			return ETypeOfData::SYMBOL_TABLE_DATA;
		else
			return ETypeOfData::INVALID_DATA;
	}

public:

	bool clearRepository() 
	{
		numSystem->erase();
		itemUnitRates->erase();
	}

	bool collectData(const std::string data)
	{
		switch (getTypeOfData(data))
		{
		case ETypeOfData::SYMBOL_TABLE_DATA:
			return collectNumeralSymbolData(data);
			
		case ETypeOfData::RATE_PER_UNIT_DATA:
			return collecRatePerUnitItemData(data);
			
		case ETypeOfData::INVALID_DATA:
			std::cout << "\nI have no idea what you are talking about" << std::endl; 
			return false;
		}
		return true;
	}
	
	bool collectNumeralSymbolData(const std::string data) 
	{
		std::vector<std::string> vecDataSubStrings;
		StringHelperFunctions::createVectorOfStringsFromInputString(data, vecDataSubStrings);

		if (vecDataSubStrings.size() > 3)
			return false;

		std::string	strSymbol = vecDataSubStrings[0];
		char		value =  vecDataSubStrings[2][0];

		std::string  strRomanNumeral = "";
		strRomanNumeral += value;

		if (!RomanNumeral::isRomanNumberValid(strRomanNumeral))
		{
			std::cout << "\nRoman digit assigned to galactic symbol " << strRomanNumeral << " is invalid ! " << std::endl;
			return false; 
		}

		numSystem->addSymbolValuePair(strSymbol, value);
		
		return true;
	}


	bool collecRatePerUnitItemData(const std::string data)
	{

		std::vector<std::string> vecDataSubStrings;
		StringHelperFunctions::createVectorOfStringsFromInputString(data, vecDataSubStrings);

		std::string strRomanNumber = "";
		int  itemNamePosition = -1; 
		std::string  itemName = "";

		for (auto & str : vecDataSubStrings)
		{
			char c = numSystem->getSymbolValue(str);

			itemNamePosition++;
			if (c != '*')
				strRomanNumber += c;
			else
			{
				break;
			}
		}

		if ( RomanNumeral::isRomanNumberValid(strRomanNumber) == false)
		{
			std::cout << "Error : Invalid symbol combination provided " << std::endl; 
			return false;
		}

		int quantityInDec = RomanNumeral::getDecimalEquivalent(strRomanNumber);

		double creditsValue = -1; 
		double perUnitRate = -1;

		if (itemNamePosition > 0 && itemNamePosition < vecDataSubStrings.size())
		{
			std::string  itemName = vecDataSubStrings[itemNamePosition].c_str();

			creditsValue = std::stod(vecDataSubStrings[itemNamePosition + 2].c_str());

			perUnitRate = creditsValue / quantityInDec;

			if (creditsValue > 0)
			{
				itemUnitRates->addPerUnitItemValuePair(itemName, perUnitRate);	
				return true;
			}
		}
		return false;
	}
	char getEquivalentRomanNumeral(const std::string& searchValue)
	{
		return numSystem->getSymbolValue(searchValue);
	}
	
	double getRatePerUnit(const std::string& itemName)
	{
		return  itemUnitRates->getValueForItem(itemName);
		
	}

	static GalacticNumericalSymbolTable* getGalacticNumericalSymbolTable()
	{
		return numSystem;
	}

	static ItemUnitRateStore* getItemUnitRateStore()
	{
		return itemUnitRates;
	}
	
public :
	static GalacticNumericalSymbolTable*  numSystem;
	static ItemUnitRateStore*  itemUnitRates;
};

GalacticNumericalSymbolTable*  DataCollector::numSystem = new  GalacticNumericalSymbolTable();
ItemUnitRateStore*  DataCollector::itemUnitRates = new ItemUnitRateStore();



#endif

