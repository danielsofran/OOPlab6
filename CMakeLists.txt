cmake_minimum_required(VERSION 3.7.2)
project(lab6)

set(CMAKE_CXX_STANDARD 14)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(lab6 exceptions.h main.cpp domain.cpp domain.h tests.cpp tests.h repository.h service.cpp service.h validator.cpp validator.h uiconsole.cpp uiconsole.h)
