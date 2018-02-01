#ifndef MERCHANT_H
#define MERCHANT_H

#include <string>
#include <iostream>
#include <map>

#include "Broker.h"


#include "TransactionType.h"
#include "StatementReader.h"

class Merchant
{
	Broker*			m_Broker;

public:

	Merchant()
	{
		m_Broker = nullptr;
	}

	bool processStatement(StatementReader* pCmdReader)
	{

		if (pCmdReader->isValidState())
		{
			std::string commandFromFile = pCmdReader->readStatement();

			if (!commandFromFile.empty())
				m_Broker->processStatement(commandFromFile);

			return true;
		}
		else
		{
			return false;
		}

	}

	void startTransaction(eTranscationType transactionType)
	{
		//Create the broker object 
		m_Broker = BrokerFactory::getBroker(transactionType);
	}

	Broker* getBrokerInstance()
	{
		return m_Broker;
	}
	void endTransaction()
	{
		//std::cout << "\nTransaction completed !" << std::endl;
		delete m_Broker;
		m_Broker = nullptr;
	}
};

#endif