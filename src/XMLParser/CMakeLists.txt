project (XMLParser)

add_compile_options( -fPIC )

add_library( XMLParser STATIC xmlParser.cpp )
target_include_directories( XMLParser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
