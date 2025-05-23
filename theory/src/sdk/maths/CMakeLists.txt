project (maths)

add_library(${PROJECT_NAME}  src/prime.cpp)
add_library(sdk::maths ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
    sdk::common
)
