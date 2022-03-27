cmake_minimum_required(VERSION 3.21)
project(lab6)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab6 exceptions.h main.cpp domain.cpp domain.h tests.cpp tests.h repository.cpp repository.h service.cpp service.h validator.cpp validator.h uiconsole.cpp uiconsole.h)
