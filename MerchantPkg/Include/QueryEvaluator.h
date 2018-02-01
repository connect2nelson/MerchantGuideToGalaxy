
#ifndef QUERY_EVALUATOR_H
#define QUERY_EVALUATOR_H

#include <string>
#include <iostream>

#include "DataCollector.h"
#include "StringHelperFunctions.h"

class QueryEvaluator
{
public:
	virtual ~QueryEvaluator(){}
	virtual double evaluate(const std::string& strInputQuery, DataCollector* collector) = 0;
};


class QueryEvaluatorHelperFunctions
{
public:
	
	static void getRomanNumeralString(	DataCollector*	collector,
										std::string		strInputStatement,
										std::string&	strRomanString)
	{
		std::vector<std::string> vecDataSubStrings;
		StringHelperFunctions::createVectorOfStringsFromInputString(strInputStatement, vecDataSubStrings);

		GalacticNumericalSymbolTable* symbolTable = collector->getGalacticNumericalSymbolTable();
		strRomanString = "";

		for (auto& str : vecDataSubStrings)
		{
			char romanDigitEquivalent = symbolTable->getSymbolValue(str);

			if (romanDigitEquivalent != '*')
			{
				strRomanString += romanDigitEquivalent;
			}
		}
	}

	static void getItemNameAndValueFromStatement(DataCollector*	collector,
										std::string		strInputStatement,
										std::string&	strItemName,
										double &		value)
	{
		std::vector<std::string> vecDataSubStrings;
		StringHelperFunctions::createVectorOfStringsFromInputString(strInputStatement, vecDataSubStrings);
		ItemUnitRateStore* itemUnitRates = collector->getItemUnitRateStore();

		double tempDoubleValue = 0.0f;

		for (auto& str : vecDataSubStrings)
		{
			tempDoubleValue = itemUnitRates->getValueForItem(str);
			if (tempDoubleValue > 0)
			{
				strItemName = str;
				value = tempDoubleValue;
			}
		}

	}

	static void getOutputString(DataCollector* collector,
								std::string  strInputStatement,
								std::string& strOutputString)
	{
		std::vector<std::string> vecDataSubStrings;
		StringHelperFunctions::createVectorOfStringsFromInputString(strInputStatement, vecDataSubStrings);

		GalacticNumericalSymbolTable* symbolTable = collector->getGalacticNumericalSymbolTable();
		ItemUnitRateStore* itemUnitRates = collector->getItemUnitRateStore();

		strOutputString = "";
		double tempDoubleValue = 0.0f;

		for (auto& str : vecDataSubStrings)
		{
			char romanDigitEquivalent = symbolTable->getSymbolValue(str);

			if (romanDigitEquivalent != '*')
			{
				strOutputString += str + " ";
			}
			else
			{
				tempDoubleValue = itemUnitRates->getValueForItem(str);
				if (tempDoubleValue > 0)
				{
					strOutputString += str + " ";
				}
			}

		}
	}
};



class NumberQueryEvaluator : public QueryEvaluator
{
public:
	double evaluate(const std::string& strInputQuery, DataCollector* collector) override
	{
		std::string strRomanNumber;
		std::string outputString;
	
		QueryEvaluatorHelperFunctions::getRomanNumeralString(collector,strInputQuery,  strRomanNumber);

		if ( RomanNumeral::isRomanNumberValid(strRomanNumber) == false)
		{
			std::cout << "Error : Invalid symbol combination provided " << std::endl;
			return -1;
		}

		int equivalentDecimalValue = RomanNumeral::getDecimalEquivalent(strRomanNumber);
		
		QueryEvaluatorHelperFunctions::getOutputString(collector, strInputQuery, outputString);

		std::cout << "\n" << outputString << " is " << equivalentDecimalValue ;

		return equivalentDecimalValue;
	}

private :

	
};

class CreditQueryEvaluator : public QueryEvaluator
{
public:
	double evaluate(const std::string& strInputQuery, DataCollector* collector) override
	{

		std::string strRomanNumber;
		std::string outputString;
		std::string strItemName = "";
		double itemValue = 0.0f;

		QueryEvaluatorHelperFunctions::getRomanNumeralString(collector, strInputQuery, strRomanNumber);
		QueryEvaluatorHelperFunctions::getItemNameAndValueFromStatement(collector, strInputQuery, strItemName, itemValue);

		if (!(itemValue > 0))
			return -1;


		if ( RomanNumeral::isRomanNumberValid(strRomanNumber) == false)
		{
			std::cout << "Error : Invalid symbol combination provided " << std::endl;
			return -1; 
		}

		int equivalentDecimalValue = RomanNumeral::getDecimalEquivalent(strRomanNumber);
		
		QueryEvaluatorHelperFunctions::getOutputString(collector, strInputQuery, outputString);
		std::cout << "\n" << outputString << " is " << equivalentDecimalValue * itemValue << " Credits";

		return equivalentDecimalValue * itemValue;
		
	}
};


class QueryEvaluatorFactory
{
public :
	static QueryEvaluator * getQueryEvaluator(const std::string& query)
	{
		if (query.find("how much is") != std::string::npos)
		{
			return new  NumberQueryEvaluator();
		}
		else if (query.find("how many Credits is") != std::string::npos)
		{
			return new CreditQueryEvaluator();
		}
		else
		{
			return nullptr;
		}
	}
};
#endif