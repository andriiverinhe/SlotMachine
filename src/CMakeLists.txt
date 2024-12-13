cmake_minimum_required(VERSION 3.10)
project(SlotMachine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    backend/Drum.cpp
    backend/Drums.cpp
    backend/Figure.cpp
    backend/SlotMachine.cpp

    backend/Drum.hpp
    backend/Drums.hpp
    backend/Figure.hpp
    backend/SlotMachine.hpp

    GUI/desktop/Controller.cpp
    GUI/desktop/Controller.hpp

    GUI/desktop/main.cpp
    GUI/desktop/View.cpp
    GUI/desktop/View.hpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

