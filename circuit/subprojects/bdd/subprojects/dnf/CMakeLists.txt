cmake_minimum_required(VERSION 3.1)
project(DNF_FROM_BDD)

# set(MAIN main.cpp)
set(HEADER_DIR header)
set(SOURCE_DIR source)

aux_source_directory(${SOURCE_DIR} DNF_FROM_BDD_CXXS)

# add_executable(MAIN_DNF ${MAIN})
add_library(DNF_FROM_BDD_LIB STATIC ${DNF_FROM_BDD_CXXS})

target_include_directories(DNF_FROM_BDD_LIB  PUBLIC ${HEADER_DIR})

# target_link_libraries(MAIN_DNF DNF_FROM_BDD_LIB)