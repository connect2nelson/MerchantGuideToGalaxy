// TW-Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "gtest\gtest.h"
#include <map>
#include <string>
#include "Broker.h"
#include "Merchant.h"
#include <StatementReader.h>

using namespace std;

int main( int argc, char **acters)
{

	//
	// Create a merchant 
	//
	Merchant m;
	m.startTransaction(eTranscationType::STOCK);

	//
	// Get a statement reader object 
	//
	StatementReader * reader = StatementReaderFactory::getStatementReader("FILE");

	//
	//  Pass the reader to merchant for getting input and processing the input.
	//
	while( m.processStatement(reader) ) ;
	
	//
	// End the transaction 
	//
	m.endTransaction();

}



