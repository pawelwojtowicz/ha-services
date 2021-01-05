add_executable( exampleService CExample.cpp CExample.h)

target_link_libraries( exampleService Global Runtime mosquittopp )
install( TARGETS exampleService RUNTIME DESTINATION usr/bin )
