cmake_minimum_required(VERSION 3.10)

project(Tetris VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

if (WIN32)
	string(REPLACE "/include/SDL2" "/include/" SDL2_PARENT_DIR ${SDL2_INCLUDE_DIR})
	add_executable(Tetris WIN32 ${TARGET_SOURCES})
else()
	add_executable(Tetris ${TARGET_SOURCES})
endif()


target_include_directories(Tetris PRIVATE ${SDL2_PARENT_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Tetris ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${SRC_FILES} DESTINATION src)