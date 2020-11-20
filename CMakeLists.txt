cmake_minimum_required(VERSION 3.0)

project(jsonmapper)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLE "Build examples" OFF)

if ("${JSON_MAPPER_RAPIDJSON_INCLUDE_PATH}" STREQUAL "")
    set(JSON_MAPPER_RAPIDJSON_INCLUDE_PATH thirdparty/rapidjson/include) # Add this so that we can find rapidjson
endif()

add_library(jsonmapper INTERFACE)
target_include_directories(jsonmapper INTERFACE 
    include
    ${JSON_MAPPER_RAPIDJSON_INCLUDE_PATH}
    )


# example
if (BUILD_EXAMPLE)
    file(GLOB_RECURSE JSON_MAPPER_FILES include/*)
    set(EXAMPLES example1 example2 example3)

    foreach(example ${EXAMPLES})
        add_executable(${example} example/${example}.cpp ${JSON_MAPPER_FILES})
        target_link_libraries(${example} PRIVATE jsonmapper)
    endforeach()
endif(BUILD_EXAMPLE)