#include "CExample.h"
#include <stdio.h>

Example::CExample gs;

namespace Example
{
CExample::CExample()
: Runtime::CRuntimeUnit("Example")
{
    int timerId = GetTimerManager().CreateTimer(this);
    GetTimerManager().SetTimer(timerId,0,5);
    GetTimerManager().StartTimer(timerId);
}

CExample::~CExample()
{
}

void CExample::NotifyTimer( const Int32& timerId )
{
    printf("Timer\n");
}
}
