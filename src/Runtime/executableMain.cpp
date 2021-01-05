#include "CExecutable.h"

Runtime::CExecutable* __pExecutable;

int main(int argc, char** argv )
{
	int retVal = 0;

	if ( 0 != __pExecutable )
	{
		__pExecutable->InitModule(argc,argv);

		retVal = __pExecutable->Run();

		__pExecutable->Shutdown();
	}

	return retVal;
}

