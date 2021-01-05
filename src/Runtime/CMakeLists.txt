project( Runtime )

SET( OUTPUT_NAME Runtime )

add_library( ${OUTPUT_NAME} SHARED
CExecutable.cpp
executableMain.cpp
CTimerManager.cpp
)

target_link_libraries( ${OUTPUT_NAME} Global)
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
