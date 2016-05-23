cmake_minimum_required(VERSION 3.3)
project(SocketTestApp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

if(WIN32)
    add_subdirectory(win-socket)
else()
    add_subdirectory(linux-socket)
endif()

add_subdirectory(udp-receiver)
add_subdirectory(message-container)

set(SOURCE_FILES main.cpp)
add_executable(SocketTestApp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} udp-receiver)
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_HEADERS_DIR})