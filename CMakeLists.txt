cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(LOGGER_COMPILE_VERBOSE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)
    add_compile_definitions(COMPILE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(COMPILE_RELEASE)
endif()

## ---------- NeutronLogger ---------- ##
project(NeutronLogger DESCRIPTION "A logging system for C++")

file(GLOB_RECURSE NEUTRON_LOG_INCLUDE_FILES "./NeutronLogger/include/*.h")
file(GLOB_RECURSE NEUTRON_LOG_SOURCE_FILES "./NeutronLogger/src/*.cpp")

file (GLOB_RECURSE NEUTRON_LOG_INCLUDE_FILES "./NeutronLogger/include/*.h")
add_library(NeutronLogger STATIC ${NEUTRON_LOG_SOURCE_FILES})
include_directories(NeutronLogger/include)

## ---------- NeutronEditor ---------- ##

project(NeutronEditor DESCRIPTION "The official editor for NeutronEngine")

file(GLOB_RECURSE NEUTRON_LIB_INCLUDE_FILES "./NeutronEditor/*.h")
file(GLOB_RECURSE NEUTRON_LIB_SOURCE_FILES "./NeutronEditor/*.cpp")

set(CMAKE_PREFIX_PATH "/mnt/secondary/Qt/6.4.1/gcc_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

#qt_add_resources(RC_SRC "NeutronEditor/resources/qml.qrc")

set(OLD_AUTORCC ${CMAKE_AUTORCC})
set(CMAKE_AUTORCC ON)

qt_add_resources(NeutronEditor "app_images"
        PREFIX "/NeutronEditor"
        FILES /resources/branding/icon.png
        )

add_executable (NeutronEditor ${NEUTRON_LIB_INCLUDE_FILES} ${NEUTRON_LIB_SOURCE_FILES} NeutronEditor/src/MainWindow.cpp NeutronEditor/src/MainWindow.h NeutronEditor/src/main.cpp)
#qt_add_executable(NeutronEditor ${NEUTRON_LIB_INCLUDE_FILES} ${NEUTRON_LIB_SOURCE_FILES} NeutronEditor/src/MainWindow.cpp NeutronEditor/src/MainWindow.h NeutronEditor/src/main.cpp NeutronEditor/resources/qml.qrc)

target_link_libraries (NeutronEditor NeutronLogger boost_stacktrace_backtrace Qt6::Widgets)

set(CMAKE_AUTORCC ${OLD_AUTORCC})

add_library(myGame SHARED ${ALL_SOURCES} ${RC_SRC})


## ---------- NeutronEngine ---------- ##

project(NeutronEngine DESCRIPTION "A libre Game Engine written in C++")

file(GLOB_RECURSE NEUTRON_LIB_INCLUDE_FILES "./NeutronEngine/Neutron/include/*.h")

add_library(NeutronEngine STATIC NeutronEngine/Neutron/src/Math/Vector2.cpp NeutronEngine/Neutron/src/Events.cpp NeutronEngine/Neutron/src/Window.cpp NeutronEngine/Neutron/src/Color.cpp NeutronEngine/Neutron/src/Components/RendererComponents.cpp NeutronEngine/Neutron/src/Math/Axis.cpp NeutronEngine/Neutron/src/InputSystem.cpp NeutronEngine/Neutron/src/Components/BaseComponent.cpp NeutronEngine/Neutron/src/Helper.cpp NeutronEngine/Neutron/src/Components/Transform.cpp NeutronEngine/Neutron/src/Shader.cpp NeutronEngine/Neutron/include/Neutron/Shader.h NeutronEngine/Neutron/src/Utils/Files.cpp NeutronEngine/Neutron/src/Utils/Files.cpp NeutronEngine/Neutron/src/Helper.cpp NeutronEngine/Neutron/include/Neutron/Utils/Files.h NeutronEngine/Neutron/include/Neutron/macros/ansi.h)
target_link_libraries(NeutronEngine NeutronLogger boost_stacktrace_backtrace glfw GLEW GLU GL Xrandr Xxf86vm Xi Xinerama X11 rt dl mono-2.0 m pthread)

## -------- NeutronExampleC++ -------- ##

project(NeutronExampleC++ DESCRIPTION "An example project for NeutronEngine made with pure cpp")

project(NeutronExampleC++)

file(GLOB_RECURSE NEC_FILES "./NeutronExample/cpp/*")
add_executable(NeutronExampleC++ ${NEC_FILES})
target_link_libraries(NeutronExampleC++ NeutronEngine)
include_directories(NeutronEngine/Neutron/include)

## ------ NeutronExampleLogging ------ ##

project(NeutronExampleLogging DESCRIPTION "An example project for NeutronEngine made to show off Logging")

project(NeutronExampleLogging)
file(GLOB_RECURSE NEL_FILES "./NeutronExample/Logging/*")
add_executable(NeutronExampleLogging ${NEL_FILES})
target_link_libraries(NeutronExampleLogging NeutronEngine)
include_directories(NeutronEngine/Neutron/include)

project(NeutronEngine) # this is literally just here because CLion uses the last CMake project as the project name, so this is just here to make it say NeutronEngine instead of NeutronExampleLogging