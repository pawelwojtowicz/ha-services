project( runtime )

SET( OUTPUT_NAME runtime )

add_library( ${OUTPUT_NAME} SHARED
CExecutable.cpp
CRuntimeUnit.cpp
CMessenger.cpp
executableMain.cpp
CTimerManager.cpp
CLogger.cpp
CLogger.h
CLoggerMsg.cpp
CLoggerMsg.h
ILogger.h
Logger.h
)

set_target_properties(${OUTPUT_NAME} PROPERTIES VERSION ${HOME_AUTOMATION_SERVICES_VERSION} SOVERSION ${HOME_AUTOMATION_SERVICES_VERSION} )
target_link_libraries( ${OUTPUT_NAME} global)
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
