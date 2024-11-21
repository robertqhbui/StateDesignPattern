#include "TransactionProcessor.h"
#include "ProcessorState.h"

//---------------------------------------------------------------------------------------------------------------------
// Name			:	TransactionProcessor
// Description	:	Defaul constructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
TransactionProcessor::TransactionProcessor()
{
	nextState(INVALID_STATE);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	TransactionProcessor
// Description	:	Overloaded constructor
// Parameter	:	server - unique pointer to Server object
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
TransactionProcessor::TransactionProcessor(std::unique_ptr<Server> server) : 
										   mServer(std::move(server))
{
	nextState(INVALID_STATE);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	TransactionCardProcessor
// Description	:	Overloaded constructor
// Parameter	:	server - unique pointer to Server object
//					stateIndicator - the initial state of this state machine
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
TransactionProcessor::TransactionProcessor(std::unique_ptr<Server> server,
										   const ProcessorStateIndicator stateIndicator) :
										   mServer(std::move(server))
{
	nextState(stateIndicator);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~TransactionProcessor
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
TransactionProcessor::~TransactionProcessor()
{
	//Nothing 
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getStateIndicator
// Description	:	Get the current state of this state machine
// Parameter	:	None
// Return		:	ProcessorStateIndicator value
//---------------------------------------------------------------------------------------------------------------------
ProcessorStateIndicator TransactionProcessor::getStateIndicator() const
{
	return mState->getStateIndicator();
}
//---------------------------------------------------------------------------------------------------------------------
// Name			:	nextState
// Description	:	Create and assign the new state.
// Parameter	:	ProcessorStateIndicator - state indicator for the state to create
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void TransactionProcessor::nextState(const ProcessorStateIndicator stateIndicator)
{
	switch (stateIndicator)
	{
		case STARTUP_STATE:
		{
			mState = std::make_unique<ProcessorStartupState>(this);
			break;
		}
		case PENDING_STATE:
		{
			mState = std::make_unique<ProcessorPendingState>(this);
			break;
		}
		case TRANSACTING_STATE:
		{
			mState = std::make_unique<ProcessorTransactingState>(this);
			break;
		}
		case INVALID_STATE:
		default:
		{
			mState = std::make_unique<ProcessorInvalidState>(this);
		}
	}
}