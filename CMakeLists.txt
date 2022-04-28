cmake_minimum_required(VERSION 3.22)
project(ls)

set(CMAKE_CXX_STANDARD 17)

add_executable(ls
        CommandLineArgsParser.cpp
        DirIterator.cpp
        DirEntry.cpp
        main.cpp)
