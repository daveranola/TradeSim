cmake_minimum_required(VERSION 3.20)

project(trade-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(trade-sim
    src/main.cpp
 "src/CsvMarketDataSource.cpp" "src/Portfolio.cpp" "src/PaperBroker.cpp")

 target_include_directories(trade-sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)