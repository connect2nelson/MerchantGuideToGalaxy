#ifndef NUMERICAL_SYSTEM_H

#define NUMERICAL_SYSTEM_H

#include <string>
#include <map>

class GalacticNumericalSymbolTable
{
	typedef std::string Symbol;
	typedef char RomanDigit;
	std::map<Symbol, char >  mapSymbolValue;
	
public:
	bool addSymbolValuePair(const Symbol& symbol, const char value)
	{
		mapSymbolValue.insert(std::make_pair(symbol, value));
		return true;
	}
	char  getSymbolValue(const Symbol& symbol)
	{
		if (mapSymbolValue.find(symbol) != mapSymbolValue.end())
		{
			return  mapSymbolValue[symbol];
		}
		else
		{
			//std::cout << "\nSYMBOL not found !" << std::endl;
			return '*'; 
		}
	}

	void erase()
	{
		mapSymbolValue.clear();
	}
	void printSymbolInformation()
	{
		std::cout << "\nSymbol value pair :" << std::endl; 
		for (auto& x : mapSymbolValue)
		{
			std::cout << x.first << "=>" << x.second << std::endl; 
		}
	}
};

#endif
