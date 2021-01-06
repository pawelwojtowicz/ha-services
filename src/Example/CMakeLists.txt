add_executable( exampleService CExample.cpp CExample.h)

target_link_libraries( exampleService global runtime mosquittopp )
install( TARGETS exampleService RUNTIME DESTINATION bin )
