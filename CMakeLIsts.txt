cmake_minimum_required(VERSION 3.20)
project(my_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 11)

find_package(raylib 3.0 QUIET) # Requires at least version 3.0

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        FetchContent_MakeAvailable(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()

endif()

# Get jsoncpp

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

# Find source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Find header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/inc/*.h)

add_executable(jarvis.csj ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(jarvis.csj raylib)

get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})
target_link_libraries(jarvis.csj jsoncpp_lib)

target_link_libraries(jarvis.csj ${CURL_LIBRARIES})


# Set directories to search for header files
include_directories(${CMAKE_SOURCE_DIR}/inc)

add_library(jar ${STADYN} ${SOURCE_FILES} ${HEADER_FILES} ${JSONCPP_LIBRARIES} ${CURL_LIBRARIES})
target_link_libraries(jar raylib)
target_link_libraries(jar jsoncpp_lib)
target_link_libraries(jar ${CURL_LIBRARIES})
target_link_libraries(jarvis.csj jar)