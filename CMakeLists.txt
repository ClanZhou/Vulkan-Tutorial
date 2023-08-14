cmake_minimum_required (VERSION 3.10)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)
project (vulkan_tutorial)

# glfw
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)

# glm
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glm)

# volk
set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/volk)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/volk)

add_executable(vulkan_tutorial main.cpp)

target_link_libraries(vulkan_tutorial PUBLIC glfw volk)