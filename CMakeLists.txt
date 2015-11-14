project(kfiresaver3d)
cmake_minimum_required(VERSION 2.8)

find_package(Qt5Core)
find_package(Qt5OpenGL)
find_package(Qt5Multimedia)
find_package(Qt5Widgets)
find_package(OpenGL)
set(CMAKE_AUTOMOC ON)

add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCES
  src/kfiresaver.cpp
  src/kfiresaversetup.cpp
  src/main.cpp
  src/particle.cpp
)

set(UI
  src/kfiresaversetup.ui
)

set(DATA
  src/data.qrc
)

qt5_wrap_ui(UI_SOURCES ${UI})
qt5_add_resources(DATA_SOURCES ${DATA})

add_executable(kfiresaver3d
  ${SOURCES}
  ${UI_SOURCES}
  ${DATA_SOURCES}
)
target_link_libraries(kfiresaver3d
  Qt5::Core
  Qt5::Multimedia
  Qt5::OpenGL
  Qt5::Widgets
  ${OPENGL_LIBRARIES}
)
