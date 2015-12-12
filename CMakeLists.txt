CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

PROJECT(LD34)

FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS
    src/main.cpp
	src/application.cpp
	src/textureholder.cpp
	src/titlestate.cpp
	src/state.cpp
	src/statestack.cpp
	src/font.cpp
	src/gamestate.cpp
	src/player.cpp
	src/IHM/widget.cpp
	src/IHM/layout.cpp
	src/IHM/textbutton.cpp
	src/IHM/verticalmenu.cpp
)

ADD_EXECUTABLE(
    LD34
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
    -g
)

INCLUDE_DIRECTORIES(
    ${SFML_INCLUDE_DIR}
	src/
)

TARGET_LINK_LIBRARIES(
    LD34
    ${SFML_AUDIO_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
)
