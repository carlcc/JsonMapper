cmake_minimum_required(VERSION 3.0)

project(jsonmapper)

include_directories(
    .
    include
    )

file(GLOB_RECURSE JSON_MAPPER_FILES include/*)

add_executable(jsonmapper main.cpp ${JSON_MAPPER_FILES})

install(TARGETS jsonmapper RUNTIME DESTINATION bin)
