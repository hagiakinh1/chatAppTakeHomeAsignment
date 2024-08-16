cmake_minimum_required(VERSION 2.8.12)

project(ChatApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Sql Quick REQUIRED)
add_library(libTinyFsm)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc"
    "model/dataaccessobject.cpp"
    "model/dataaccessobject.h"
    "controller/navigator.cpp"
    "controller/navigator.h"
    "config.h")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Sql libTinyFsm)
target_include_directories(libTinyFsm PUBLIC "thirdPartyLib/tinyfsm/include")

