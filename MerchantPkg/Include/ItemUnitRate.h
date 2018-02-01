#ifndef ITEM_UNIT_RATE_H
#define ITEM_UNIT_RATE_H


#include <string>
#include <map>

class ItemUnitRateStore
{
	typedef std::string Item;
	std::map<Item, double>  mapItemUnitRates;

public:
	bool addPerUnitItemValuePair(const Item & item, const double &value)
	{
		mapItemUnitRates.insert(std::make_pair(item, value));
		return true;
	}
	double  getValueForItem(const Item &  item)
	{
		if (mapItemUnitRates.find(item) != mapItemUnitRates.end())
			return mapItemUnitRates[item];
		else
			return 0;
	}

	void erase()
	{
		mapItemUnitRates.clear();
	}


private :
	void printSymbolInformation()
	{
		std::cout << "\nPrice value pair :" << std::endl;
		for (auto& x : mapItemUnitRates)
		{
			std::cout << x.first << "=>" << x.second << std::endl;
		}
	}
};


#endif
