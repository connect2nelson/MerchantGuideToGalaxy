// TestCommandReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest\gtest.h"

#include "StatementReader.h"

#include <string>
using namespace std;


TEST(read_from_file, StatementReader)
{
	StatementReader * reader = StatementReaderFactory::getStatementReader("FILE");
	
	vector<string> vecOfStrings;
	do
	{
		string stmt = reader->readStatement();
		
		if (!stmt.empty())
			vecOfStrings.push_back(stmt);
	} while (reader->isValidState());

	EXPECT_EQ(vecOfStrings.size(), 12);

	reader->close();
	EXPECT_EQ(reader->isValidState(), false);

}


TEST(read_from_console, StatementReader)
{
	StatementReader * reader = StatementReaderFactory::getStatementReader("CONSOLE");

	vector<string> vecOfStrings;

	int count = 0;

	do
	{
		string stmt = reader->readStatement();

		if (!stmt.empty())
		{
			vecOfStrings.push_back(stmt);
			count++;
		}
	} while (reader->isValidState());

	EXPECT_EQ(vecOfStrings.size(),count);

	reader->close();
	EXPECT_EQ(reader->isValidState(), false);

}


