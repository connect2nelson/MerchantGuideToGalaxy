// TestDataCollector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest\gtest.h"
#include <DataCollector.h>
#include <StatementReader.h>


TEST(collect_symbol_data, DataCollector)
{
	DataCollector dc;
	StatementReader * reader = StatementReaderFactory::getStatementReader("FILE");

	std::vector<std::string> vecOfStrings;
	do
	{
		std::string stmt = reader->readStatement();

		if (!stmt.empty() && stmt.find("?") == std::string::npos)
			EXPECT_TRUE(dc.collectData(stmt));
				
	} while (reader->isValidState());

	EXPECT_EQ(dc.getEquivalentRomanNumeral("glob"), 'I');
	EXPECT_EQ(dc.getEquivalentRomanNumeral("prok"), 'V');
	EXPECT_EQ(dc.getEquivalentRomanNumeral("pish"), 'X');
	EXPECT_EQ(dc.getEquivalentRomanNumeral("tegj"), 'L');

	EXPECT_EQ(dc.getEquivalentRomanNumeral("xxxx"), '*');
}


TEST(collect_rate_data, DataCollector)
{
	DataCollector dc;


	StatementReader * reader = StatementReaderFactory::getStatementReader("FILE");

	std::vector<std::string> vecOfStrings;
	do
	{
		std::string stmt = reader->readStatement();

		if (!stmt.empty() && stmt.find("?") == std::string::npos)
			EXPECT_TRUE(dc.collectData(stmt));

	} while (reader->isValidState());

	EXPECT_DOUBLE_EQ(dc.getRatePerUnit("Silver"), 17);
	EXPECT_DOUBLE_EQ(dc.getRatePerUnit("Gold"), 14450);
	EXPECT_DOUBLE_EQ(dc.getRatePerUnit("Iron"), 195.5);

	/*EXPECT_EQ(dc.getRatePerUnit("Gold"), 'V');
	EXPECT_EQ(dc.getRatePerUnit("Irong"), 'X');
	EXPECT_EQ(dc.getRatePerUnit("tegj"), 'L');
*/
	
}