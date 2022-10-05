#pragma once

#define ERROR   0x08
#define WARNING 0x04
#define INFO    0x02
#define DATA    0x01
#include "CLoggerMsg.h"

#define HA_LOG( zone, logMsg )                        \
        if ( CLoggerMsg::ZoneEnabled( zone ) )        \
        {                                             \
          CLoggerMsg msg( zone, __FILE__, __LINE__);  \
          msg.LogText  logMsg ;                       \
        }