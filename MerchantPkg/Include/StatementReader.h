
#ifndef STATEMENT_READER_H
#define STATEMENT_READER_H

#include <string>
#include <fstream>

const char *  INPUT_STATEMENT_FILE_NAME = ".\\input.txt";

class StatementReader
{
public:
	virtual ~StatementReader(){}
	virtual std::string readStatement() = 0;
	virtual bool isValidState() = 0;
	virtual void close() = 0;
};

class FileStatementReader : public StatementReader
{


private:
	std::ifstream   m_fileStream;


	void openFile(std::string fileName)
	{
		if (!m_fileStream.is_open())
			m_fileStream = std::ifstream(fileName.c_str(), std::ifstream::in);

		if (!m_fileStream)
			std::cout << "\n Coud not open file " << std::endl;

	}

public:
	
	bool isValidState() override
	{
		if (m_fileStream)
			return true;
		else
			return false;
	}

	std::string readStatement() override
	{
		std::string input;
		
		openFile(std::string(INPUT_STATEMENT_FILE_NAME));

		getline(m_fileStream, input);

		return input;
	}

	
	void close() override
	{
		if (m_fileStream)
			m_fileStream.close();
	}
};

class ConsoleStatementReader : public StatementReader
{
	std::string  m_lastCommand;

public:

	bool isValidState() override
	{
		if (m_lastCommand == "END")
			return false;
		else
			return true;
	}

	std::string readStatement() override
	{
		char input[4028];
		memset(input, 0, 2048);
		std::cin.getline(input, 4028);

		m_lastCommand = input; 
		return m_lastCommand;

	}

	void close() override
	{
		
	}
};


class StatementReaderFactory
{

public:
	static StatementReader* getStatementReader(const std::string& typeOfCmdInterpter)
	{
		if (strcmp("FILE", typeOfCmdInterpter.c_str()) == 0)
			return new FileStatementReader();
		else if (strcmp("CONSOLE", typeOfCmdInterpter.c_str()) == 0)
			return new ConsoleStatementReader();

		return nullptr;
	}
};

#endif

