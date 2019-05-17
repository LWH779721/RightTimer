cmake_minimum_required(VERSION 2.8) 

PROJECT(RightTimerTest)

INCLUDE_DIRECTORIES(../include) 

ADD_EXECUTABLE(RightTimer_test RightTimer_test.cpp)  
TARGET_LINK_LIBRARIES(RightTimer_test RightTimer)
