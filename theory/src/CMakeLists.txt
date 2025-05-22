project(theory)

add_subdirectory(sdk/common)
add_subdirectory(sdk/maths)

add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    sdk::common
    sdk::maths
    test::test
)


