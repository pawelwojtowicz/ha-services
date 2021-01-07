#include "CExample.h"
#include <stdio.h>

Example::CExample gs;

namespace Example
{
CExample::CExample()
: Runtime::CRuntimeUnit("Example")
{
}

CExample::~CExample()
{
}

}
