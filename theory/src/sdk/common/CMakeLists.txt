project (common)

add_library(${PROJECT_NAME} src/common.cpp)
add_library(sdk::common ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)