project( global
         VERSION 1.0
         DESCRIPTION "Global types for the project" )

add_library( global INTERFACE )
target_include_directories ( global INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
