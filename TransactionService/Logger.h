#pragma once
#include <mutex>

enum LOG_LEVEL
{
	INFO_LEVEL = 0,
	WARNING_LEVEL,
	ERROR_LEVEL
};
class Logger
{
private:
	Logger() {}

	//Not allowing create an instance using new or copy 
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static std::mutex		mMutex; // Mutex for thread safety
	static Logger*			mInstance;

public:
	static Logger			*getInstance();
	virtual void			logMessage(const std::string &messageText, const LOG_LEVEL level = INFO_LEVEL) const;
};
