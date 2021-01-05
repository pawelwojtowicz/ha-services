project( Global
         VERSION 1.0
         DESCRIPTION "Global types for the project" )

add_library( Global INTERFACE )
target_include_directories ( Global INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
