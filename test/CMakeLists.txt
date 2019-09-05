cmake_minimum_required(VERSION 2.8) 

PROJECT(RightTimerTest)

add_definitions("-std=c++11") 

INCLUDE_DIRECTORIES(../include) 

ADD_EXECUTABLE(RightTimer_test RightTimer_test.cpp)  
TARGET_LINK_LIBRARIES(RightTimer_test RightTimer)
