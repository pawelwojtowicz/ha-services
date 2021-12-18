#pragma once

namespace oFonoIntegration
{
static const char* s_ofonoEndpoint = "org.ofono";
static const char* s_modemManagerIfName = "org.ofono.Manager";
static const char* s_modemAddedSignalName = "ModemAdded";
static const char* s_modemRemovedSignalName = "ModemRemoved";
static const char* s_getModemsMethodName = "GetModems";

static const char* s_messageManagerIfName = "org.ofono.MessageManager";
static const char* s_sendSMSMethodName = "SendMessage";
static const char* s_incommingMessageSignalName = "IncomingMessage";
static const char* s_immediateMessageSignalName = "ImmediateMessage";


using toFonoModemInformation = std::vector<sdbus::Struct<sdbus::ObjectPath,std::map<std::string,sdbus::Variant>>>;
using tStringArray = std::vector<std::string>;
using tMessageInfoDict = std::map<std::string, sdbus::Variant>;
}