cmake_minimum_required(VERSION 2.8) 

PROJECT(TimeWalker)

add_definitions("-std=c++11 -g") 

INCLUDE_DIRECTORIES(../include)

AUX_SOURCE_DIRECTORY(. TimeWalker)

#ADD_LIBRARY (TimeWalker ${TimeWalker})
ADD_LIBRARY (TimeWalker SHARED ${TimeWalker})

TARGET_LINK_LIBRARIES(TimeWalker pthread)
