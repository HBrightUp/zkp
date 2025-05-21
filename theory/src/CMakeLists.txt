project(theory)

add_subdirectory(sdk/common)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    sdk::common
)


