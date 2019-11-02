cmake_minimum_required(VERSION 2.8) 

PROJECT(RightTimer)

add_definitions("-std=c++11 -g") 

INCLUDE_DIRECTORIES(../include)

AUX_SOURCE_DIRECTORY(. RightTimer)

#ADD_LIBRARY (RightTimer ${RightTimer})
ADD_LIBRARY (RightTimer SHARED ${RightTimer})

TARGET_LINK_LIBRARIES(RightTimer pthread)
