#ifndef BROKER_H

#define BROKER_H

#include <string>

#include "TransactionType.h"
#include "StatementProcessor.h"


class Broker
{
public:
	virtual ~Broker(){}
	virtual bool processStatement(const std::string& cmd) = 0;
	virtual std::string getBrokerType() = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InterGalacticStockTransactionBroker : public Broker
{
	std::string		m_strBrokerType;
	StmtProcessor	processor;

public:
	bool processStatement(const std::string& stmt) override
	{
		 if ( processor.process(stmt) ) 
			return true;
		 else
		 {
			 std::cout << "\nI have no idea what you are talking about" << std::endl;
			 return false;
		 }
	}

	std::string getBrokerType() override
	{
		return "\"InterGalactic StockTransaction\" Broker";
	}

};

//StmtProcessor InterGalacticStockTransactionBroker::processor;



class BrokerFactory
{
public:
	static Broker* getBroker(eTranscationType  transaction)
	{
		switch (transaction)
		{
			case eTranscationType::STOCK:
				return new InterGalacticStockTransactionBroker();

			default :
				return nullptr;
		}
		
	}
};

#endif