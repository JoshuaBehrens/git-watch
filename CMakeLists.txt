cmake_minimum_required(VERSION 3.17)
project(git_watch)

set(CONAN_DISABLE_CHECK_COMPILER ON)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run `conan install --build=missing -s build_type=Debug --install-folder=cmake-build-debug .` first")
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(
        git_watch
        src/main.cpp
        src/path.cpp
)
target_include_directories(git_watch PRIVATE include ${CONAN_INCLUDE_DIRS})
target_link_libraries(git_watch PRIVATE ${CONAN_LIBS})
