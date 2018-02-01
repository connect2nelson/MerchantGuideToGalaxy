// TestCommandProcessor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include "gtest\gtest.h"
#include "StatementReader.h"
#include <StatementProcessor.h>
using namespace std;


TEST(process_stmt_from_input_file, StatementProcessor)
{
	StmtProcessor processor;

	vector<string>  vecStatements = 
	{
		{ "glob is I" },
		{ "prok is V" },
		{"pish is X"},
		{ "tegj is L" },
		{ "glob glob Silver is 34 Credits " },
		{ "glob prok Gold is 57800 Credits" },
		{ " pish pish Iron is 3910 Credits" },
		{ "how much is pish tegj glob glob ?" } ,
		{ "how many Credits is glob prok Silver ?" } ,
		{ "how many Credits is glob prok Gold ? " },
		{ "how many Credits is glob prok Iron ?" }
	};

	for (auto stmt : vecStatements)
	{
		EXPECT_EQ(processor.process(stmt), true);
	}

	string stmt = "how much wood could a woodchuck chuck if a woodchuck could chuck wood ? ";

	EXPECT_EQ(processor.process(stmt), false);

}
