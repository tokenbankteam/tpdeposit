cmake_minimum_required(VERSION 3.5)
project(tpdeposit VERSION 1.0.0)

find_package(eosio.cdt)

add_contract(tpdeposit tpdeposit ${CMAKE_CURRENT_SOURCE_DIR}/src/tpdeposit.cpp)
target_include_directories(tpdeposit
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.system/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../eosio.token/include)

set_target_properties(tpdeposit
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

#target_ricardian_directory( tpdeposit ${CMAKE_CURRENT_SOURCE_DIR}/ricardian )