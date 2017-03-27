cmake_minimum_required(VERSION 3.6)
project(mesple_client)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp network/Client.cpp network/ClientException.cpp)
add_executable(mesple_client ${SOURCE_FILES})
