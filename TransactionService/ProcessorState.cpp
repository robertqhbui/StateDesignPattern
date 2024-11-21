#include "ProcessorState.h"
#include "TransactionProcessor.h"
#include "Logger.h"
#include <string> 


//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorState
// Description	:	Default constructor. Setting the state to INVALID State for this state machine
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorState::ProcessorState():
								mProcessor(nullptr),
								mStateIndicator(INVALID_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorState
// Description	:	Overloaded constructor. Setting the state to INVALID State for this state machine
// Parameter	:	Pointer to TransactionProcessor
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorState::ProcessorState(TransactionProcessor *processor):
								mProcessor(processor),
								mStateIndicator(INVALID_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorState
// Description	:	Overloaded constructor. Setting the state to state provided for this state machine
// Parameter	:	TransactionProcessor pointer
//					ProcessorStateIndicator enum to indicate the state of this state machine
// Return		:	
//---------------------------------------------------------------------------------------------------------------------
ProcessorState::ProcessorState(TransactionProcessor* processor, const ProcessorStateIndicator stateIndicator):
								mProcessor(processor),
								mStateIndicator(stateIndicator)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ProcessorState
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorState::~ProcessorState()
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getStateIndicator
// Description	:	Get the current state value for this state machine
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorStateIndicator ProcessorState::getStateIndicator() const
{
	return mStateIndicator;
}
//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorStartupState
// Description	:	Overloaded constructor
// Parameter	:	processor - pointer to TransactionProcessor.
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorStartupState::ProcessorStartupState(TransactionProcessor *processor) : 
											 ProcessorState(processor, STARTUP_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ProcessorStartupState
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorStartupState::~ProcessorStartupState()
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onStart
// Description	:	Action start event
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void ProcessorStartupState::onStart()
{
	if (mProcessor)
	{
		mStateIndicator = PENDING_STATE;
		mProcessor->nextState(mStateIndicator);
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingStart
// Description	:	Action for processing start
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void ProcessorStartupState::onProcessingStart()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to start processing while in startup state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessing
// Description	:	Action for during processing
// Parameter	:	amount integer value to process
// Return		:	true - completed successfully
//					false - unable to process the amount 
//---------------------------------------------------------------------------------------------------------------------
bool ProcessorStartupState::onProcessing(const int amount)
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to process while in startup state.", WARNING_LEVEL);
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingFinish
// Description	:	Action for process finish event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorStartupState::onProcessingFinish()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to finish processing while in startup state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorPendingState
// Description	:	Overloaded constructor
// Parameter	:	processor - pointer to TransactionProcessor.
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
ProcessorPendingState::ProcessorPendingState(TransactionProcessor *processor) : 
											 ProcessorState(processor, PENDING_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onTimeout
// Description	:	Action for processing timeout event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorStartupState::onTimeout()
{
	Logger* logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Timeout while in startup state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ProcessorPendingState
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None		
//---------------------------------------------------------------------------------------------------------------------
ProcessorPendingState::~ProcessorPendingState()
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onStart
// Description	:	Action start event
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void ProcessorPendingState::onStart()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to unable to start while in pending state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingStart
// Description	:	Action for processing start
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorPendingState::onProcessingStart()
{
	if (mProcessor)
	{
		mStateIndicator = TRANSACTING_STATE;
		mProcessor->nextState(mStateIndicator);
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessing
// Description	:	Action for during processing
// Parameter	:	amount integer value to process
// Return		:	true - completed successfully
//					false - unable to process the amount
//---------------------------------------------------------------------------------------------------------------------
bool ProcessorPendingState::onProcessing(const int amount)
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to process while in pending state.", WARNING_LEVEL);
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingFinish
// Description	:	Action for process finish event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorPendingState::onProcessingFinish()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to unable to finishing process while in pending state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onTimeout
// Description	:	Action for processing timeout event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorPendingState::onTimeout()
{
	Logger* logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Timeout while in pending state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorStartupState
// Description	:	Overloaded constructor
// Parameter	:	processor - pointer to TransactionProcessor.
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ProcessorTransactingState::ProcessorTransactingState(TransactionProcessor *processor) :
													 ProcessorState(processor, TRANSACTING_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ProcessorTransactingState
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
ProcessorTransactingState::~ProcessorTransactingState()
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onStart
// Description	:	Action start event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorTransactingState::onStart()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to start to start while in transacting state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingStart
// Description	:	Action for processing start
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void ProcessorTransactingState::onProcessingStart()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to start processing to start while in transacting state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessing
// Description	:	Action for during processing
// Parameter	:	amount integer value to process
// Return		:	true - completed successfully
//					false - unable to process the amount
//---------------------------------------------------------------------------------------------------------------------
bool ProcessorTransactingState::onProcessing(const int amount)
{
	return mProcessor->onProcess(amount);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingFinish
// Description	:	Action for process finish event
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
void ProcessorTransactingState::onProcessingFinish()
{
	if (mProcessor)
	{
		mStateIndicator = PENDING_STATE;
		mProcessor->nextState(mStateIndicator);
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onTimeout
// Description	:	Action for processing timeout event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorTransactingState::onTimeout()
{
	if (mProcessor)
	{
		mStateIndicator = STARTUP_STATE;
		mProcessor->nextState(mStateIndicator);
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ProcessorInvalidState
// Description	:	Overloaded constructor
// Parameter	:	processor - pointer to TransactionProcessor.
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
ProcessorInvalidState::ProcessorInvalidState(TransactionProcessor *processor) :
											 ProcessorState(processor, INVALID_STATE)
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ProcessorInvalidState
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
ProcessorInvalidState::~ProcessorInvalidState()
{
	//Nothing else to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onStart
// Description	:	Action start event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorInvalidState::onStart()
{
	if (mProcessor)
	{
		mStateIndicator = STARTUP_STATE;
		mProcessor->nextState(mStateIndicator);
	}
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingStart
// Description	:	Action for processing start
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorInvalidState::onProcessingStart()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to start processing to start while in invalid state.", WARNING_LEVEL);
	return;
}


//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessing
// Description	:	Action for during processing
// Parameter	:	amount integer value to process
// Return		:	true - completed successfully
//					false - unable to process the amount	
//---------------------------------------------------------------------------------------------------------------------
bool ProcessorInvalidState::onProcessing(const int amount)
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to start processing to start while in invalid state.", WARNING_LEVEL);
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onProcessingFinish
// Description	:	Action for process finish event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorInvalidState::onProcessingFinish()
{
	Logger *logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Unable to finish processing to start while in invalid state.", WARNING_LEVEL);
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	onTimeout
// Description	:	Action for processing timeout event
// Parameter	:	None
// Return		:	None	
//---------------------------------------------------------------------------------------------------------------------
void ProcessorInvalidState::onTimeout()
{
	Logger* logger = Logger::getInstance();
	logger->logMessage("Unexpected event: Timeout while in invalid state.", WARNING_LEVEL);
}