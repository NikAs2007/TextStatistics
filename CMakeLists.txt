cmake_minimum_required(VERSION 3.30.2)
project(TextStatistics)

set(PrName ${PROJECT_NAME})
set(MAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17) #версия с++
set(CMAKE_CXX_STANDARD_REQUIRED ON) #значит обязательно использовать указанный стандарт
set(CMAKE_CXX_EXTENSIONS OFF) #значит используем стандартный с++ без расширений

add_executable(${PrName} TextStatistics.cpp File.cpp Folder.cpp Manager.cpp)

target_include_directories(${PrName} PRIVATE .)