cmake_minimum_required(VERSION 2.8) 

PROJECT(TimeWalkerTest)

add_definitions("-std=c++11") 

INCLUDE_DIRECTORIES(../include) 

ADD_EXECUTABLE(Alarm Alarm.cpp)  
TARGET_LINK_LIBRARIES(Alarm TimeWalker)

ADD_EXECUTABLE(WifiConnect WifiConnect.cpp)  
TARGET_LINK_LIBRARIES(WifiConnect TimeWalker)
