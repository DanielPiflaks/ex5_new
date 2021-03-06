cmake_minimum_required(VERSION 3.8)
project(ex5)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -pthread")
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES_CLIENT src/client/Board.cpp src/client/Board.h src/client/Player.h src/client/HumanPlayer.h src/client/HumanPlayer.cpp src/client/Player.cpp src/client/Game.h src/client/Game.cpp src/client/GameParameters.cpp src/client/GameParameters.h src/client/BoardCoordinates.cpp src/client/BoardCoordinates.h src/client/GameLogic.cpp src/client/GameLogic.h src/client/StandartGameLogic.cpp src/client/StandartGameLogic.h src/client/AIPlayer.h src/client/AIPlayer.cpp src/client/MiniMaxSimulator.cpp src/client/MiniMaxSimulator.h src/client/RemotePlayer.cpp src/client/RemotePlayer.h src/client/Client.cpp src/client/Client.h src/client/HumanPlayerSender.cpp src/client/HumanPlayerSender.h src/client/GuiDisplay.h src/client/ConsoleGuiDisplay.cpp src/client/ConsoleGuiDisplay.h)
set(TESTS_FILES_CLIENT src/client/tests/MiniMaxSimulatorTest.cpp src/client/tests/BoardTest.cpp src/client/tests/GameLogicTest.cpp src/client/tests/ReadIpPortFileTest.cpp)
set(SOURCE_FILES_SERVER  src/server/Server.cpp src/server/Server.h src/server/Command.h src/server/StartGameCommand.cpp src/server/StartGameCommand.h src/server/GetListGamesCommand.cpp src/server/GetListGamesCommand.h src/server/JoinGameCommand.cpp src/server/JoinGameCommand.h src/server/CloseGameCommand.cpp src/server/CloseGameCommand.h src/server/CommandsManager.cpp src/server/CommandsManager.h src/server/GameManager.cpp src/server/GameManager.h)
set(TESTS_FILES_SERVER src/server/tests/ReadPortFromFileTest.cpp)

add_executable(ex5_server ${SOURCE_FILES_SERVER} src/server/main_server.cpp src/server/HandelClient.cpp src/server/HandelClient.h src/server/Task.h src/server/ThreadPool.cpp src/server/ThreadPool.h)
add_executable(ex5_client ${SOURCE_FILES_CLIENT} src/client/main.cpp)
add_executable(ex5_tests_Client ${SOURCE_FILES_CLIENT} ${TESTS_FILES_CLIENT} src/client/tests/gtest_main.cpp)
add_executable(ex5_tests_Server ${SOURCE_FILES_SERVER} ${TESTS_FILES_SERVER} src/server/tests/gtest_main.cpp)

target_link_libraries(ex5_tests_Client gtest gtest_main pthread)
target_link_libraries(ex5_tests_Server gtest gtest_main pthread)
add_test(ex5 ex5)
