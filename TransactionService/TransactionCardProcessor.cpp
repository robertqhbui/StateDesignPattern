#include "TransactionCardProcessor.h"
#include "Logger.h"
#include <future>
#include <chrono>
#include <iostream>
#include <string>
using namespace std::chrono_literals;

//---------------------------------------------------------------------------------------------------------------------
// Name			:	TransactionCardProcessor
// Description	:	Overloaded constructor
// Parameter	:	server - unique pointer to Server object
//					stateIndicator - the initial state of this state machine
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
TransactionCardProcessor::TransactionCardProcessor(std::unique_ptr<Server> server,
												   const ProcessorStateIndicator stateIndicator) :
												   TransactionProcessor(std::move(server), stateIndicator)
{
	//Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	TransactionCardProcessor
// Description	:	Overloaded constructor
// Parameter	:	server - unique pointer to Server object
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
TransactionCardProcessor::TransactionCardProcessor(std::unique_ptr<Server> server) :
												   TransactionProcessor(std::move(server))
{
	//Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~TransactionCardProcessor
// Description	:	Default destructor
// Parameter	:	NOne
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
TransactionCardProcessor::~TransactionCardProcessor()
{
	//Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	start
// Description	:	Action on request to start the transaction
// Parameter	:	None
// Return		:	NOne
//---------------------------------------------------------------------------------------------------------------------
void TransactionCardProcessor::start()
{
	mState->onStart();
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	process
// Description	:	Action on request to process the transaction
// Parameter	:	amount - integer value to process
// Return		:	true - process successfully.
//					false - unsuccessful
//---------------------------------------------------------------------------------------------------------------------
bool TransactionCardProcessor::process(const int amount)
{
	Logger* logger = Logger::getInstance();

	logger->logMessage("Received transaction with amount " + std::to_string(amount) + ".", INFO_LEVEL);
	mState->onProcessingStart();
	bool isSuccessful = mState->onProcessing(amount);
	if (isSuccessful)
	{
		mState->onProcessingFinish();
		logger->logMessage("Transaction completed.", INFO_LEVEL);
	}
	else
	{
		logger->logMessage("Timed out.", ERROR_LEVEL);
		mState->onTimeout();
	}
	return isSuccessful;
}
//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcess
// Description	:	Action on Process event
// Parameter	:	amount - integer value to process transaction.
// Return		:	true - successful
//					false - unsuccessfull
//---------------------------------------------------------------------------------------------------------------------
bool TransactionCardProcessor::onProcess(const int amount)
{
	Logger* logger = Logger::getInstance();
	
	std::future<bool> future = std::async(&Server::putTransaction, mServer.get(), amount);

	std::future_status status = future.wait_for(std::chrono::seconds(PROCESS_TIMEOUT_SECS));

	if (status == std::future_status::ready)
		return true;
	return false;
}
