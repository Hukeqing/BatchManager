cmake_minimum_required(VERSION 3.17)
project(BatchManager)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DDEBUG)
#add_definitions(-DWINDOWS)

add_executable(BatchManager main.cpp command/basic/command.h command/basic/environment.h common/exception.h command/not.h command/set.h command/var.h command/link.h command/join.h command/run.h command/for.h command/end.h command/__init__.h batch/process.h command/cmd.h)