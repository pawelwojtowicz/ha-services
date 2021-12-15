project( oFonoIntegration )

SET( OUTPUT_NAME ofonoMngr )

add_library( ${OUTPUT_NAME} SHARED
    CModemManager.cpp
    CoFonoProxy.cpp
)

set_target_properties(${OUTPUT_NAME} PROPERTIES VERSION ${HOME_AUTOMATION_SERVICES_VERSION} SOVERSION ${HOME_AUTOMATION_SERVICES_VERSION} )
target_link_libraries( ${OUTPUT_NAME} global dbus-c++-1 )
target_include_directories( ${OUTPUT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} dbus-c++-1 )
install( TARGETS ${OUTPUT_NAME} RUNTIME DESTINATION lib )