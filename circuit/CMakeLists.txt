cmake_minimum_required(VERSION 3.1)
project(CIRCUIT)

set(MAIN command/main.cpp)
set(SPEED_TEST command/speed.cpp)
set(HEADER_DIR header)
set(SOURCE_DIR source)

set(CIRCUIT_DIR ${SOURCE_DIR}/Circuit)
set(GATE_DIR    ${SOURCE_DIR}/Gate)
set(IMPORTER_DIR   ${SOURCE_DIR}/Importer)
set(BDD_EXPORTER_DIR   ${SOURCE_DIR}/BddExporter)
set(DNF_EXPORTER_DIR   ${SOURCE_DIR}/DnfExporter)
set(PERMISSIBLE_SET_BUILDER_DIR   ${SOURCE_DIR}/PermissibleSetBuilder)
set(TIMER_DIR   ${SOURCE_DIR}/Timer)

set(BDD_DIR subprojects/bdd)
set(DNF_DIR subprojects/dnf)

add_subdirectory(${BDD_DIR})
add_subdirectory(${DNF_DIR})


aux_source_directory(${CIRCUIT_DIR} CIRCUIT_CXXS)
aux_source_directory(${GATE_DIR}    GATE_CXXS)
aux_source_directory(${IMPORTER_DIR}    IMPORTER_CXXS)
aux_source_directory(${BDD_EXPORTER_DIR}    BDD_EXPORTER_CXXS)
aux_source_directory(${DNF_EXPORTER_DIR}    DNF_EXPORTER_CXXS)
aux_source_directory(${PERMISSIBLE_SET_BUILDER_DIR}    PERMISSIBLE_SET_BUILDER_CXXS)
aux_source_directory(${TIMER_DIR}   TIMER_CXXS)


add_executable(MAIN_CIRCUIT ${MAIN})
add_executable(SPEED_TEST_EXEC ${SPEED_TEST})

add_library(CIRCUIT_LIB STATIC  ${CIRCUIT_CXXS})
add_library(GATE_LIB    STATIC  ${GATE_CXXS})
add_library(IMPORTER_LIB    STATIC  ${IMPORTER_CXXS})
add_library(BDD_EXPORTER_LIB   STATIC  ${BDD_EXPORTER_CXXS})
add_library(DNF_EXPORTER_LIB   STATIC  ${DNF_EXPORTER_CXXS})
add_library(PERMISSIBLE_SET_BUILDER_LIB   STATIC  ${PERMISSIBLE_SET_BUILDER_CXXS})
add_library(TIMER_LIB   STATIC  ${TIMER_CXXS})


target_include_directories(CIRCUIT_LIB  PUBLIC ${HEADER_DIR})
target_include_directories(GATE_LIB     PUBLIC ${HEADER_DIR})
target_include_directories(IMPORTER_LIB     PUBLIC ${HEADER_DIR})
target_include_directories(BDD_EXPORTER_LIB    PUBLIC ${HEADER_DIR})
target_include_directories(DNF_EXPORTER_LIB    PUBLIC ${HEADER_DIR})
target_include_directories(PERMISSIBLE_SET_BUILDER_LIB    PUBLIC ${HEADER_DIR})
target_include_directories(TIMER_LIB    PUBLIC ${HEADER_DIR})


target_link_libraries(IMPORTER_LIB CIRCUIT_LIB GATE_LIB)
target_link_libraries(CIRCUIT_LIB GATE_LIB)
target_link_libraries(BDD_EXPORTER_LIB CIRCUIT_LIB GATE_LIB BDD_LIB )
target_link_libraries(DNF_EXPORTER_LIB CIRCUIT_LIB GATE_LIB BDD_LIB DNF_LIB )
target_link_libraries(PERMISSIBLE_SET_BUILDER_LIB CIRCUIT_LIB GATE_LIB DNF_LIB )

target_link_libraries(MAIN_CIRCUIT      IMPORTER_LIB CIRCUIT_LIB BDD_EXPORTER_LIB DNF_EXPORTER_LIB PERMISSIBLE_SET_BUILDER_LIB GATE_LIB)
target_link_libraries(SPEED_TEST_EXEC   IMPORTER_LIB CIRCUIT_LIB BDD_EXPORTER_LIB DNF_EXPORTER_LIB PERMISSIBLE_SET_BUILDER_LIB GATE_LIB TIMER_LIB)


set_target_properties(SPEED_TEST_EXEC PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)


# Test section

set(TEST_DIR test)
set(timeout 5)

add_executable(BASIC ${TEST_DIR}/basic.cpp)
target_link_libraries(BASIC CIRCUIT_LIB)

enable_testing()
add_test(BASIC_27 BASIC S27.BEN)
set_tests_properties(BASIC_27 PROPERTIES TIMEOUT ${timeout})