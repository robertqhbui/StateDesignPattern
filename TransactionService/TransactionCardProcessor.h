#pragma once
#include "TransactionProcessor.h"
class TransactionCardProcessor : public TransactionProcessor
{
private:
	bool onProcess(const int amount);
public:
	TransactionCardProcessor(std::unique_ptr<Server> server);
	TransactionCardProcessor(std::unique_ptr<Server> server, const ProcessorStateIndicator stateIndicator);
	~TransactionCardProcessor();
	void			start();
	bool			process(const int amount);
};

