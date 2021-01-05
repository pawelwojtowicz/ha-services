project (CSM )

SET( OUTPUT_NAME CSM )

add_library ( ${OUTPUT_NAME} SHARED
CState.cpp
CTransition.cpp
CArgoConfigurator.cpp 
CStateMachine.cpp 
CActionFactory.cpp
)

target_link_libraries ( ${OUTPUT_NAME} Global UCL XMLParser )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
