cmake_minimum_required(VERSION 3.20)

project(trade-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(trade_sim_lib
    src/CsvMarketDataSource.cpp
    src/Portfolio.cpp
    src/PaperBroker.cpp
    src/MovingAverageCrossStrategy.cpp
    src/BacktestEngine.cpp
)

target_include_directories(trade_sim_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(trade-sim
    src/main.cpp
)

target_link_libraries(trade-sim PRIVATE trade_sim_lib)

enable_testing()

add_executable(portfolio_tests
    tests/PortfolioTests.cpp
)

target_link_libraries(portfolio_tests PRIVATE trade_sim_lib)

add_test(NAME PortfolioTests COMMAND portfolio_tests)

add_executable(broker_tests
    tests/BrokerTests.cpp
)

target_link_libraries(broker_tests PRIVATE trade_sim_lib)

add_test(NAME BrokerTests COMMAND broker_tests)

add_executable(strategy_tests
    tests/StrategyTests.cpp
)

target_link_libraries(strategy_tests PRIVATE trade_sim_lib)

add_test(NAME StrategyTests COMMAND strategy_tests)