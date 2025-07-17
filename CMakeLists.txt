cmake_minimum_required(VERSION 3.16)
project(KitchenRoutingLibrary LANGUAGES CXX)

# Require C++17 or higher
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Needs to check those variables especially for Debug/Release VS2022
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add library
add_library(KitchenRoutingLibrary SHARED
    src/Item.cpp
    src/Kitchen.cpp
    src/KitchenArea.cpp
    src/Menu.cpp
    src/Order.cpp
)

target_include_directories(KitchenRoutingLibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# TODO: Debug builds for GCC/Clang
if(MSVC)
    target_compile_options(KitchenRoutingLibrary PRIVATE /W4 /permissive-)
else()
    target_compile_options(KitchenRoutingLibrary PRIVATE -O3 -Wall -Wextra -Wpedantic -Werror)
endif()

# Generate Doxygen
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

add_subdirectory(app)