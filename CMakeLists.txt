cmake_minimum_required(VERSION 2.8.12)

project(ChatApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Sql Quick WebSockets REQUIRED)
add_library(libTinyFsm)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc"
    "model/dataaccessobject.cpp"
    "model/dataaccessobject.h"
    "model/contactmodel.cpp"
    "model/contactmodel.h"
    "model/chatmodel.cpp"
    "model/chatmodel.h"
    "model/textmessage.cpp"
    "model/textmessage.h"
    "controller/logincontroller.cpp"
    "controller/logincontroller.h"
    "controller/navigator.cpp"
    "controller/navigator.h"
    "controller/chatcontroller.cpp"
    "controller/chatcontroller.h"
    "config.h"
    "websocketclient.cpp"
    "websocketclient.h")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Sql Qt5::WebSockets libTinyFsm)
target_include_directories(libTinyFsm PUBLIC "thirdPartyLib/tinyfsm/include")

