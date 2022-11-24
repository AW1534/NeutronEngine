cmake_minimum_required(VERSION 3.23)

project(NeutronEngine)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(BOOST_STACKTRACE_USE_BACKTRACE)

find_package(glfw3 REQUIRED)
find_package(GLEW 2.0 REQUIRED)

#link_directories(lib/gcc/x64/release)
add_executable(NeutronEngine Neutron/Math/Vector2.cpp Neutron/Math/Vector2.h Neutron/Events.cpp Neutron/Events.h Neutron/Window.cpp Neutron/Window.h Neutron/Color.cpp Neutron/Color.h Neutron/Logger.cpp Neutron/Logger.h Neutron/Objects/GameObject.cpp Neutron/Objects/GameObject.h example.cpp Neutron/Drawable.cpp Neutron/Drawable.h Neutron/macros/input.h Neutron/macros/ansi.h Neutron/Helper.h Neutron/Math/Axis.cpp Neutron/Math/Axis.h Neutron/InputSystem.cpp Neutron/InputSystem.h)
target_link_libraries(NeutronEngine boost_stacktrace_backtrace glfw GLEW GLU GL Xrandr Xxf86vm Xi Xinerama X11 rt dl) # (fbxsdk) was omitted because dumb
#target_include_directories(NeutronEngine PRIVATE ./include)