cmake_minimum_required(VERSION 3.1)
project(DNF)

set(MAIN main.cpp)
set(HEADER_DIR header)
set(SOURCE_DIR source)

aux_source_directory(${SOURCE_DIR}/dnf DNF_CXXS)
aux_source_directory(${SOURCE_DIR}/conj CONJ_CXXS)

add_library(CONJ_LIB STATIC  ${CONJ_CXXS})
add_library(DNF_LIB STATIC ${DNF_CXXS})

target_include_directories(CONJ_LIB  PUBLIC ${HEADER_DIR})
target_include_directories(DNF_LIB          PUBLIC ${HEADER_DIR})

target_link_libraries(DNF_LIB CONJ_LIB)