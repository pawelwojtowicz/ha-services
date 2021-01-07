project (ucl)

SET(OUTPUT_NAME ucl )

add_library( ${OUTPUT_NAME} SHARED 
CFastHash.cpp
CFile.cpp
CMemoryInfo.cpp
CSemaphore.cpp
CSerializable.cpp
CSerialPort.cpp
CSharedMemory.cpp 
CThread.cpp
CTokenizer.cpp
CUnixDomainSocket.cpp
FileSystem.cpp
SystemEnvironment.cpp
)


set_target_properties(${OUTPUT_NAME} PROPERTIES VERSION ${HOME_AUTOMATION_SERVICES_VERSION} SOVERSION ${HOME_AUTOMATION_SERVICES_VERSION} )
target_link_libraries( ${OUTPUT_NAME} global )
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )


