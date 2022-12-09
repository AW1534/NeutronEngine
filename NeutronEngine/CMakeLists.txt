cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)

find_package(glfw3 REQUIRED)
find_package(GLEW 2.0 REQUIRED)

## ---------- NeutronEngine ---------- ##

project(NeutronEngine DESCRIPTION "A libre Game Engine written in C++")

file(GLOB_RECURSE NEUTRON_LIB_INCLUDE_FILES "./Neutron/include/*.h")

#link_directories(lib/gcc/x64/release)
#link_directories(/usr/lib/pkgconfig/../../lib)
add_library(NeutronEngine STATIC Neutron/src/Math/Vector2.cpp Neutron/src/Events.cpp Neutron/src/Window.cpp Neutron/src/Color.cpp Neutron/src/Logger.cpp Neutron/src/Components/RendererComponents.cpp Neutron/src/Math/Axis.cpp Neutron/src/InputSystem.cpp Neutron/src/Components/BaseComponent.cpp Neutron/src/Helper.cpp Neutron/src/Components/Transform.cpp Neutron/src/Shader.cpp Neutron/include/Neutron/Shader.h Neutron/include/Neutron/Utils/Files.h Neutron/src/Utils/Files.cpp)
#add_executable(NeutronEngine Neutron/Math/Vector2.cpp Neutron/Math/Vector2.h Neutron/Events.cpp Neutron/Events.h Neutron/Window.cpp Neutron/Window.h Neutron/Color.cpp Neutron/Color.h Neutron/Logger.cpp Neutron/Logger.h Neutron/Objects/GameObject.cpp Neutron/Objects/GameObject.h example.cpp Neutron/Components/Drawable.cpp Neutron/Components/Drawable.h Neutron/macros/input.h Neutron/macros/ansi.h Neutron/Helper.h Neutron/Math/Axis.cpp Neutron/Math/Axis.h Neutron/InputSystem.cpp Neutron/InputSystem.h Neutron/Components/BaseComponent.cpp Neutron/Components/BaseComponent.h Neutron/Math/Matrix.h Neutron/Helper.cpp Neutron/Proxy.h Neutron/Math/Concepts.h)
target_link_libraries(NeutronEngine boost_stacktrace_backtrace glfw GLEW GLU GL Xrandr Xxf86vm Xi Xinerama X11 rt dl mono-2.0 m pthread) # (fbxsdk) was omitted because dumb
#target_include_directories(NeutronEngine PRIVATE ./include)

## -------- NeutronExampleC++ -------- ##

project(NeutronExampleC++ DESCRIPTION "An example project for NeutronEngine made with pure cpp")

project(NeutronExampleC++)
file(GLOB_RECURSE NEC_FILES "../NeutronExample/cpp/*")
add_executable(NeutronExampleC++ ${NEC_FILES})
target_link_libraries(NeutronExampleC++ NeutronEngine)
include_directories(./Neutron/include)

## ------ NeutronExampleLogging ------ ##

project(NeutronExampleLogging DESCRIPTION "An example project for NeutronEngine made to show off Logging")

project(NeutronExampleLogging)
file(GLOB_RECURSE NEC_FILES "../NeutronExample/Logging/*")
add_executable(NeutronExampleLogging ${NEC_FILES})
target_link_libraries(NeutronExampleLogging NeutronEngine)
include_directories(./Neutron/include)