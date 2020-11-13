cmake_minimum_required(VERSION 2.8) 

PROJECT(TimeWalker)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
