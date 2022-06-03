cmake_minimum_required(VERSION 3.1)
project(BDD)

set(MAIN main.cpp)
set(HEADER_DIR header)
set(SOURCE_DIR source)
set(BDD_MANAGER_DIR subprojects/bdd_manager)

add_subdirectory(${BDD_MANAGER_DIR})

aux_source_directory(${SOURCE_DIR} BDD_CXXS)

add_executable(MAIN_BDD ${MAIN})
add_library(BDD_LIB STATIC ${BDD_CXXS})

target_include_directories(BDD_LIB PUBLIC ${HEADER_DIR})

target_link_libraries(BDD_LIB BDD_MANAGER_LIB)
target_link_libraries(MAIN_BDD BDD_LIB)