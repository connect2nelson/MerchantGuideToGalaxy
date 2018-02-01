
#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "QueryEvaluator.h"
#include "DataCollector.h"

class StmtProcessor
{
	QueryEvaluator* queryEvaluator;
	DataCollector*  dataCollector;
	std::string		m_strCommand;
	bool			m_bIsCommandValid;
public:

	void InitializeQueryEvaluator()
	{
		if (queryEvaluator != nullptr)
			delete queryEvaluator;
		queryEvaluator = nullptr;


		if (m_strCommand.find("how much is") != std::string::npos)
		{
			queryEvaluator = new NumberQueryEvaluator();
		}
		else if (m_strCommand.find("how many Credits is") != std::string::npos)
		{
			queryEvaluator = new CreditQueryEvaluator();
		}
		else
		{
			m_bIsCommandValid = false;
		}
	}

	void InitializeDataCollector()
	{
		dataCollector = new DataCollector();
	}

	StmtProcessor()
	{
		m_strCommand = "";
		m_bIsCommandValid = false;
		queryEvaluator = nullptr;
		dataCollector = nullptr;
		InitializeDataCollector();
	}

	void Initialize(const std::string statement)
	{
		m_strCommand = statement;
		m_bIsCommandValid = true;
		
		if (isStatementAQuery())
		{
			InitializeQueryEvaluator();
		}
		else if (isStatementAData() )
		{
		}
		else
		{
			m_bIsCommandValid = false;
		}
		
	}

	double compute() const 
	{
		if (m_bIsCommandValid)
			return queryEvaluator->evaluate(m_strCommand, dataCollector);
		else
			return -1;
	}

	bool process(const std::string strStatement )  
	{
		Initialize(strStatement);

		if (!m_bIsCommandValid)
			return  false;
		

		if (isStatementAQuery())
		{
			return compute();
		}
		else if (isStatementAData())
		{
			return dataCollector->collectData(strStatement);
		}
		
		return false;
	}

	bool isStatementAData() const
	{
		if (m_strCommand.find("is") != std::string::npos)
			return true;
		return false;
	}

	bool isStatementAQuery() const
	{
		if (m_strCommand.find("how much") != std::string::npos ||
			m_strCommand.find("how many") != std::string::npos ||
			m_strCommand.find("?") != std::string::npos)
			return true;

		return false;
	}

};

#endif
