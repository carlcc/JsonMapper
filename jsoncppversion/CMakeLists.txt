cmake_minimum_required(VERSION 3.2)

project(JsonMapper)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty)

add_library(JsonMapper INTERFACE)
target_include_directories(JsonMapper INTERFACE include)
target_link_libraries(JsonMapper INTERFACE myjsoncpp)

add_executable(JsonMapperTest test/main.cpp)
target_link_libraries(JsonMapperTest
PUBLIC
        JsonMapper
        rapidjson
        jsoncpp_lib_static
        )


add_executable(Test2 test/main2.cpp)