#pragma once
class Timer
{
public:
	Timer();
	~Timer();
	void start(int timeoutAmount);
	void stop();
	void onTimeout();
};

