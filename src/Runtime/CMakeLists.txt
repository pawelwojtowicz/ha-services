project( runtime )

SET( OUTPUT_NAME runtime )

add_library( ${OUTPUT_NAME} SHARED
CExecutable.cpp
executableMain.cpp
CTimerManager.cpp
)

target_link_libraries( ${OUTPUT_NAME} global)
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
