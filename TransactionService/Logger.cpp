#include "Logger.h"
#include <string>
#include <iostream>

// Initialize static members
Logger			*Logger::mInstance = nullptr;
std::mutex		Logger::mMutex;

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getInstance
// Description	:	Gets an instance object of the Logger
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
Logger *Logger::getInstance() {

	// Acquire lock before checking instance
	std::lock_guard<std::mutex> lock(mMutex); 	// Automatically releases lock
	if (mInstance == nullptr)
	{
		mInstance = new Logger();				// Create the instance only once
	}
	return mInstance;
}


//---------------------------------------------------------------------------------------------------------------------
// Name			:	logMessage
// Description	:	Sends the message to standard output
// Parameter	:	messageText - string
//					level - log level of message
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void Logger::logMessage(const std::string &messageText, const LOG_LEVEL level) const
{
	switch (level)
	{
		case INFO_LEVEL:
		{
			std::cout << "INFO: " + messageText << std::endl;
			break;
		}
		case WARNING_LEVEL:
		{
			std::cout << "WARNING: " + messageText << std::endl;
			break;
		}
		case ERROR_LEVEL:
		{
			std::cout << "ERROR: " + messageText << std::endl;
			break;
		}
		default:
		{
			std::cout << "UNKNOWN LEVEL: " + messageText << std::endl;
		}
	}
}