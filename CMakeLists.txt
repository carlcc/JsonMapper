cmake_minimum_required(VERSION 3.0)

project(jsonmapper)

add_library(jsonmapper INTERFACE)
target_include_directories(jsonmapper INTERFACE 
    include
    . # Add this so that we can find rapidjson
    )


# example
file(GLOB_RECURSE JSON_MAPPER_FILES include/*)
set(EXAMPLES example1 example2 example3)

foreach(example ${EXAMPLES})
    add_executable(${example} example/${example}.cpp ${JSON_MAPPER_FILES})
    target_link_libraries(${example} PRIVATE jsonmapper)
endforeach()
