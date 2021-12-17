add_executable( modemManager main.cpp )

target_link_libraries( modemManager ofonoMngr )
install( TARGETS modemManager RUNTIME DESTINATION bin )
