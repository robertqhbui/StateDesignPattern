#include "ServerRemote.h"

//---------------------------------------------------------------------------------------------------------------------
// Name			:	ServerRemote
// Description	:	Default constructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ServerRemote::ServerRemote(): Server()
{
	//Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~ServerRemote
// Description	:	Default destructor
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
ServerRemote::~ServerRemote()
{
	//Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	open
// Description	:	Open connection to the remnote server
// Parameter	:	None
// Return		:	true if can open connect to the remove server
//					false otherwise
//---------------------------------------------------------------------------------------------------------------------
bool ServerRemote::open()
{
	return true;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	close
// Description	:	Close the connection to the remote server
// Parameter	:	None
// Return		:	true if can close connect to the remove server
//					false otherwise
//---------------------------------------------------------------------------------------------------------------------
bool ServerRemote::close()
{
	return true;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	putTransaction
// Description	:	Send the data to the remove server
// Parameter	:	int - the value to send to the remote server
// Return		:	true if successfult send the data to the remove server
//					false otherwise
//---------------------------------------------------------------------------------------------------------------------
bool ServerRemote::putTransaction(const int value)
{
	return true;
}
