project( Runtime )

SET( OUTPUT_NAME Runtime )

add_library( ${OUTPUT_NAME} SHARED
CExecutable.cpp
executableMain.cpp
CTimerManager.cpp
)

target_link_libraries( ${OUTPUT_NAME} Global)
