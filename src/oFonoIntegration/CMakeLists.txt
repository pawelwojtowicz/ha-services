project( oFonoIntegration )

SET( OUTPUT_NAME ofonoMngr )

add_library( ${OUTPUT_NAME} SHARED
    CModemContext.cpp    
    CoFonoProxy.cpp
    CModemProxy.cpp
    CModem.cpp
    CModemManager.cpp
)

set_target_properties(${OUTPUT_NAME} PROPERTIES VERSION ${HOME_AUTOMATION_SERVICES_VERSION} SOVERSION ${HOME_AUTOMATION_SERVICES_VERSION} )
target_link_libraries( ${OUTPUT_NAME} global sdbus-c++ )
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} sdbus-c++ )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )
