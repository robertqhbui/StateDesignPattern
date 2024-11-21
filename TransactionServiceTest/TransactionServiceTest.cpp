#include "gtest/gtest.h"
#include "TransactionCardProcessor.h"
#include "Server.h"
#include "ServerRemote.h"
#include "ProcessorState.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

class MockSlowServer : public Server
{

public:
	bool open()
	{
		return true;
	}
	bool close()
	{
		return true;
	}
	bool putTransaction(int value)
	{
		std::this_thread::sleep_for(31s);
		return true;
	}
};


TEST(Processor, CreateProcessorWithInvalidState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server));

	EXPECT_TRUE(processor->getStateIndicator() == INVALID_STATE);

}

TEST(Processor, CreateProcessorWithStartupState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

}

TEST(Processor, CreateProcessorWithInvalidStateThenStartupState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server));

	EXPECT_TRUE(processor->getStateIndicator() == INVALID_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

}


TEST(Processor, CreateProcessorWithStartupStateThenProcess)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	processor->process(123);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

}
TEST(Processor, CreateProcessorWithInvalidStateThenStartupThenPendingState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server));

	EXPECT_TRUE(processor->getStateIndicator() == INVALID_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == PENDING_STATE);

}

TEST(Processor, CreateProcessorWithStartupThenPendingState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == PENDING_STATE);

}

TEST(Processor, CreateProcessorWithStartupThenPendingTransactingPendingState)
{
	std::unique_ptr<Server> server = std::make_unique<ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == PENDING_STATE);

	processor->process(123);

	EXPECT_TRUE(processor->getStateIndicator() == PENDING_STATE);


}

TEST(Processor, CreateProcessowWithStartupPendingTransactingTimeoutStartupState)
{
	EXPECT_TRUE(true);	std::unique_ptr<Server> server = std::make_unique<MockSlowServer>();

	std::unique_ptr<TransactionCardProcessor> processor = std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

	processor->start();

	EXPECT_TRUE(processor->getStateIndicator() == PENDING_STATE);

	processor->process(123);

	EXPECT_TRUE(processor->getStateIndicator() == STARTUP_STATE);

}