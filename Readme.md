
-----------------------------------------------------
A Merchang guide to Galaxy - Readme 
-----------------------------------------------------

------------
Design :	
------------

a)  In order to assist Merchant [class] to help stock value evaluation using galactic numeric symbols & units, a helper Broker[class] object is used [ Fundamental Theorem of Software Engg, in action :) ]
	The Broker object is extensible to handle different type of requests according to the need in future. A BrokerFactory[class] for creating different broker objects.
	At present, for handling stock evaluation ; InterGalacticStockTransactionBroker[class] object is used to process stock evaluation queries and data.
	The broker object are created on the fly when stock evaulation transactions are started and destroyed when broker object ends the same.

b) 	StatementProcessor object is used by Broker class to process the input stock evaluation data + queries.
	It uses DataCollector object to store galactic numeric symbols and units. 
	It also uses QueryEvaluator [abstract-class] to perform credit queries or numerical evaluation of galactic numerical symbols.
	At runtime, QueryEvaluator decides whether it is suppose to equip itself for numerical / credit related queries.
	QueryEvaluator can thus be extended to support many other evaluations.

c)  StatementReader object is used to facilitate reading from FILE / console in superfluous way.

d)  RomanNumeral 
	Purpose : 
	a) Provide helper functions to peform validation as to whether the input string is a valid Roman numeral or not.
	b) Generate decimal value for the Roman Numeral.

Salient Features :
a) The Merchant object by virtue of extra level of indirection, can carry out multiple galactic stock evaluation transaction  as a separate broker object is created for it.
b) The majority of the code is Functional Programming based and hence follows the Data-In, Data-Out idiom to a great extent to support Multithreading constructs.
c) QueryEvaluation can be easily extended to support other needs of the Merchant.
d) Broker class can be extended to support working with multiple brokers in future for the Merchant.

----------------
Assumptions :	|
----------------
a) For now, Merchant is interested in collecting only galactic numeric symbols & units from the stock evaulation broker. [Scope for improvement]
b) While providing data for stock evaluation, StatementProcessor assumes the following grammar :
	<symbol1..n><Item> is <Value>
c) The input commands and queries are by default taken from "input.txt" file present at the following location : .\TW-Assignment\Debug\input.txt
d) One has to append new inputs in the input.txt in order to be processed by the TestMerchant binary.
   	
------------------
External Libaries |
------------------
- Gtest1.7.0 [ Note: The gtest.lib gets compiled along with the other modules. :)]

---------------------------------------------
Instructions to Build & start the program :  |
---------------------------------------------
a) Download VS2013 Express Edition (Free) installer  if dont have a local installation of the same.
b) Open the TW-Assignment.sln in VS 2013 Express Edition from the attached zip.
c) Select the Solution Platform as "Win32" and Solution Configuration as "Debug" 
d) Press F7 or Right-click on solution to build the entire solution containing 
	- Gtest
	- MerchantPkg
		|--Includes
		|--Source
	-Test*[Projects that do unit test for various sub-classes like StmtProcessor, StmtReader,DataCollector, etc]
	-TestMerchant[ Run this Exe created by this project, for one shot verfication of program with sample data stored in .\TW-Assignment\Debug\input.txt ]
e) Click on TestMerchant project and right-click on it to Build it,if it is not built.
f) Click on TestMerchant project and right-click on it and then set it as "Startup-Project"
g) Press Ctrl+F5 to start execution of TestMerchant project.

Note : The input.txt folder is present 

