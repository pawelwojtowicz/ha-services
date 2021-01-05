#include "CExample.h"
#include <stdio.h>

Example::CExample gs;

namespace Example
{
CExample::CExample()
: Runtime::CExecutable("Example")
{
}

CExample::~CExample()
{
}

Int32 CExample::Run()
{
printf("Test\n");
return 0;
}

}
