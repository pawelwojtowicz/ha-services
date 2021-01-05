project (UCL)

SET(OUTPUT_NAME UCL )

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

target_link_libraries( ${OUTPUT_NAME} Global )
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION usr/lib )


