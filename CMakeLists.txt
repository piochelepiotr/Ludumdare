CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

PROJECT(LD34)

FIND_PACKAGE(SFML COMPONENTS audio graphics window system REQUIRED)

SET(
    SRCS

	src/IHM/widget.cpp
	src/IHM/layout.cpp
	src/IHM/textbutton.cpp
	src/IHM/verticalmenu.cpp
	src/IHM/focusgroup.cpp
	src/IHM/selectorwidget.cpp
	src/IHM/dialogbutton.cpp
	src/dialogbox.cpp

	src/anchor/anchoritem.cpp
	src/anchor/anchorpool.cpp

	src/state.cpp
	src/statestack.cpp

	src/math/spline.cpp

	src/rosetree/rosetree.cpp
	src/rosetree/branch.cpp
	src/rosetree/flower.cpp

	src/insect/insect.cpp
	src/insect/behaviour.cpp

	src/gameworld.cpp
	src/gamestate.cpp
	src/gamestateanchorlistener.cpp
	src/insectanchorlistener.cpp

	src/editor/nodeanchorlistener.cpp
	src/editor/editlevelstate.cpp

	src/titlestate.cpp
	src/menustate.cpp

	src/player.cpp
	src/application.cpp
    src/main.cpp
)

ADD_EXECUTABLE(
    LD34
    ${SRCS}
)

ADD_DEFINITIONS(
    --std=c++11
    -g
    -Wall
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
