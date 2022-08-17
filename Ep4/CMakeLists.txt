cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROJECT_NAME TutorialMod4)
project(${PROJECT_NAME})

# For the source and header files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Including the directories
target_include_directories(${PROJECT_NAME} PRIVATE
    libs/minhook/include
    libs/gd.h/include
    libs/gd.h/
    libs/cocos-headers/cocos2dx/
    libs/cocos-headers/cocos2dx/include
    libs/cocos-headers/cocos2dx/kazmath/include
    libs/cocos-headers/cocos2dx/platform/win32
    libs/cocos-headers/cocos2dx/platform/third_party/win32
    libs/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
    libs/cocos-headers/extensions/
)

add_subdirectory(libs/minhook)
# Linkers
target_link_libraries(${PROJECT_NAME} minhook)

# cocos2dx
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/cocos-headers/cocos2dx/libcocos2d.lib)

# cocos2dx extensions
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/cocos-headers/extensions/libExtensions.lib)