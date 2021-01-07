project (CSM )

SET( OUTPUT_NAME csm )

add_library ( ${OUTPUT_NAME} SHARED
CState.cpp
CTransition.cpp
CArgoConfigurator.cpp 
CStateMachine.cpp 
CActionFactory.cpp
)

set_target_properties(${OUTPUT_NAME} PROPERTIES VERSION ${HOME_AUTOMATION_SERVICES_VERSION} SOVERSION ${HOME_AUTOMATION_SERVICES_VERSION} )
target_link_libraries ( ${OUTPUT_NAME} global ucl xmlparser )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
