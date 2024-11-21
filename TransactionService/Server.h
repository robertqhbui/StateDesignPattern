#pragma once
class Server
{
public:
	Server();
	virtual	~Server();
	virtual bool	open() = 0;
	virtual bool	close() = 0;
	virtual bool	putTransaction(const int value) = 0;
	
};

