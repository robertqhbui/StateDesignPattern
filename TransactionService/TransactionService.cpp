#include "TransactionCardProcessor.h"
#include "ServerRemote.h"

//---------------------------------------------------------------------------------------------------------------------
// Name			:	main
// Description	:	The entry to the system
// Parameter	:	None
// Return		:	None
//---------------------------------------------------------------------------------------------------------------------
int main()
{
	
	std::unique_ptr<ServerRemote> server = std::make_unique< ServerRemote>();

	std::unique_ptr<TransactionCardProcessor> processor = 
											std::make_unique<TransactionCardProcessor>(std::move(server), STARTUP_STATE);

	processor->process(123);

}
