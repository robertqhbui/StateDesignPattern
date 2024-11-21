#pragma once
#include "ProcessorState.h"
#include "Server.h"
#include <memory>


#define PROCESS_TIMEOUT_SECS 30

class TransactionProcessor
{

protected:
	TransactionProcessor();
	std::unique_ptr<ProcessorState> mState;
	std::unique_ptr<Server> mServer;

	

public:
	TransactionProcessor(std::unique_ptr<Server> serverr);
	TransactionProcessor(std::unique_ptr<Server> server, const ProcessorStateIndicator stateIndicator);
	~TransactionProcessor();

	ProcessorStateIndicator			getStateIndicator() const;
	void							nextState(const ProcessorStateIndicator stateIndicator);

	virtual void					start() = 0;	
	virtual bool					process(const int amount) = 0;


	virtual bool					onProcess(const int amount) = 0;
};

