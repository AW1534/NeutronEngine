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

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK REQUIRED gtk4)

include_directories (${GTK_INCLUDE_DIRS})
link_directories (${GTK_LIBRARY_DIRS})
add_executable (NeutronEditor ${NEUTRON_LIB_INCLUDE_FILES} ${NEUTRON_LIB_SOURCE_FILES})
add_definitions (${GTK_CFLAGS_OTHER})
target_link_libraries (NeutronEditor NeutronLogger ${GTK_LIBRARIES})
target_link_libraries (NeutronEditor NeutronLogger )


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