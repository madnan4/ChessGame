cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_CXX_STANDARD 20)

# Add the main executable
add_executable(ChessGame main.cpp chessboard.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(ChessGame PRIVATE GTest::GTest GTest::Main)

add_executable(ChessGameTests tests.cpp chessboard.cpp)
target_link_libraries(ChessGameTests PRIVATE GTest::GTest GTest::Main)


enable_testing()
add_test(NAME ChessGameTests COMMAND ChessGameTests)
