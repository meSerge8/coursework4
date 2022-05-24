cmake_minimum_required(VERSION 3.1)
project(BDD_MANAGER)

set(MAIN main.cpp)
set(HEADER_DIR header)
set(SOURCE_DIR source)

set(BDD_MANAGER_DIR ${SOURCE_DIR}/bdd_manager)
set(VERTEX_DIR      ${SOURCE_DIR}/vertex)
set(VARIABLE_DIR    ${SOURCE_DIR}/variable)


aux_source_directory(${BDD_MANAGER_DIR} BDD_MANAGER_CXXS)
aux_source_directory(${VERTEX_DIR}      VERTEX_CXXS)
aux_source_directory(${VARIABLE_DIR}    VARIABLE_CXXS)


add_executable(MAIN_BDD_MANAGER ${MAIN})
add_library(BDD_MANAGER_LIB STATIC ${BDD_MANAGER_CXXS})
add_library(VERTEX_LIB      STATIC ${VERTEX_CXXS})
add_library(VARIABLE_LIB    STATIC ${VARIABLE_CXXS})


target_include_directories(BDD_MANAGER_LIB  PUBLIC ${HEADER_DIR})
target_include_directories(VERTEX_LIB       PUBLIC ${HEADER_DIR})
target_include_directories(VARIABLE_LIB     PUBLIC ${HEADER_DIR})


target_link_libraries(BDD_MANAGER_LIB VERTEX_LIB VARIABLE_LIB)
target_link_libraries(MAIN_BDD_MANAGER BDD_MANAGER_LIB)