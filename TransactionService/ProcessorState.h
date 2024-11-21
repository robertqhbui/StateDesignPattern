#pragma once


class TransactionProcessor;


enum ProcessorStateIndicator
{
	INVALID_STATE = 0,
	STARTUP_STATE,
	PENDING_STATE,
	TRANSACTING_STATE
};

class ProcessorState
{
private:
	ProcessorState();

protected:
	//Reference to the state machine - mProcessor. The state does not own the state machine.
	//It is up the creator of the state machine to manage its lifecycle
	TransactionProcessor			*mProcessor;
	ProcessorStateIndicator			mStateIndicator;

public:
	ProcessorState(TransactionProcessor *processor);
	ProcessorState(TransactionProcessor *processor, const ProcessorStateIndicator stateIndicator);
	virtual ~ProcessorState();

	ProcessorStateIndicator			getStateIndicator() const;
	virtual void					onStart() = 0;
	virtual void					onProcessingStart() = 0;
	virtual bool					onProcessing(const int amount) = 0;
	virtual void					onProcessingFinish() = 0;
	virtual void					onTimeout() = 0;
};


class ProcessorStartupState: public ProcessorState
{

public:
	ProcessorStartupState(TransactionProcessor *processor);
	~ProcessorStartupState();
	void							onStart();
	void							onProcessingStart();
	bool							onProcessing(const int amount);
	void							onProcessingFinish();
	void							onTimeout();
};

class ProcessorPendingState : public ProcessorState
{

public:
	ProcessorPendingState(TransactionProcessor *processor);
	~ProcessorPendingState();
	void							onStart();
	void							onProcessingStart();
	bool							onProcessing(const int amount);
	void							onProcessingFinish();
	void							onTimeout();
};

class ProcessorTransactingState : public ProcessorState
{

public:
	ProcessorTransactingState(TransactionProcessor *processor);
	~ProcessorTransactingState();
	void							onStart();
	void							onProcessingStart();
	bool							onProcessing(const int amount);
	void							onProcessingFinish();
	void							onTimeout();
};


class ProcessorInvalidState : public ProcessorState
{

public:
	ProcessorInvalidState(TransactionProcessor *processor);
	~ProcessorInvalidState();
	void							onStart();
	void							onProcessingStart();
	bool							onProcessing(const int amount);
	void							onProcessingFinish();
	void							onTimeout();
};


