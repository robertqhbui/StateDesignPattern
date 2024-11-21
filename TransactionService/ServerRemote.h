#pragma once
#include "Server.h"
class ServerRemote : public Server
{
public:
	ServerRemote();
	~ServerRemote();

	bool		open();
	bool		close();
	bool		putTransaction(const int value);

};

