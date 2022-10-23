cmake_minimum_required(VERSION 3.23)
project(NeutronEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(NeutronEngine example.cpp neutron/Vector2.cpp neutron/Vector2.h neutron/Events.cpp neutron/Events.h neutron/Window.cpp neutron/Window.h neutron/Color.cpp neutron/Color.h neutron/macros.h neutron/Logger.cpp neutron/Logger.h neutron/Exception.cpp neutron/Exception.h)

find_package(glfw3 REQUIRED)
target_link_libraries(NeutronEngine glfw GLU GL Xrandr Xxf86vm Xi Xinerama X11 rt dl)