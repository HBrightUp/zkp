project (test)

add_library(${PROJECT_NAME} src/prime_test.cpp src/group_test.cpp)
add_library(test::test ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    sdk::common
    sdk::maths
)
