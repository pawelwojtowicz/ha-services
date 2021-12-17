cmake_minimum_required( VERSION 3.14)

project( ha-services )

SET( CMAKE_CXX_STANDARD 17 )
SET( CMAKE_CXX_FLAGS "-fpermissive")

set( HOME_AUTOMATION_SERVICES_VERSION "0.0.1")

add_subdirectory( src )
