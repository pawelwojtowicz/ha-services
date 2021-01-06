project (CSM )

SET( OUTPUT_NAME csm )

add_library ( ${OUTPUT_NAME} SHARED
CState.cpp
CTransition.cpp
CArgoConfigurator.cpp 
CStateMachine.cpp 
CActionFactory.cpp
)

target_link_libraries ( ${OUTPUT_NAME} global ucl xmlparser )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
