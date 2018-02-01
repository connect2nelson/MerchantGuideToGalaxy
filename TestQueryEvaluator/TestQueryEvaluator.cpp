// TestQueryEvaluator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest\gtest.h"
#include <DataCollector.h>
#include <StatementReader.h>
#include <QueryEvaluator.h>

TEST(NumberQueryEvaluator, QueryEvaluator)
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

	
	std::string stmt = "how much is pish tegj glob glob ? ";
	QueryEvaluator* evaluator = QueryEvaluatorFactory::getQueryEvaluator(stmt);
	EXPECT_EQ( evaluator->evaluate(stmt, &dc), 42);
		
}


TEST(CreditQueryEvaluator, QueryEvaluator)
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

	
	std::string stmt1 = "how many Credits is glob prok Silver ?";
	QueryEvaluator* evaluator = QueryEvaluatorFactory::getQueryEvaluator(stmt1);
	EXPECT_DOUBLE_EQ(evaluator->evaluate(stmt1, &dc), 68);


	std::string stmt2 = "how many Credits is glob prok Gold ?";
	evaluator = QueryEvaluatorFactory::getQueryEvaluator(stmt1);
	EXPECT_EQ(evaluator->evaluate(stmt2, &dc), 57800);

	std::string stmt3 = "how many Credits is glob prok Iron ?";
	evaluator = QueryEvaluatorFactory::getQueryEvaluator(stmt1);
	EXPECT_EQ(evaluator->evaluate(stmt3, &dc), 782);
	

}