project (xmlparser)

add_compile_options( -fPIC )

add_library( xmlparser STATIC xmlParser.cpp )
target_include_directories( xmlparser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
