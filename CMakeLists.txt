cmake_minimum_required(VERSION 3.30)

project ("Vulkan Tutorial" VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download dependencies automatically
include(FetchContent)

#-------------------------------third parts------------------------#
# volk
FetchContent_Declare(
    volk
    GIT_REPOSITORY https://github.com/zeux/volk.git
    GIT_TAG vulkan-sdk-1.4.313.0
)
# only support WIN32 for now
if (WIN32)
   set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
endif()
FetchContent_MakeAvailable(volk)

# glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glm)

include_directories(${volk_SOURCE_DIR})
include_directories(${glfw_SOURCE_DIR}/include)
include_directories(${glm_SOURCE_DIR})

#------------------------------------------------------------------#

add_executable(vulkan_tutorial main.cpp)

target_link_libraries(vulkan_tutorial PUBLIC volk glfw)