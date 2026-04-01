cmake_minimum_required(VERSION 3.25)

project(GameMath
    VERSION 0.0.1
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# C++ is required only for GoogleTest
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(WARNING
        "This project targets GCC 15+ for complete C23 support. "
        "Current compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}. "
        "Behaviour may differ or be incompatible."
    )
elseif(CMAKE_C_COMPILER_VERSION VERSION_LESS "15")
    message(WARNING
        "GCC 15 or later is required for full C23 support. "
        "Detected GCC ${CMAKE_C_COMPILER_VERSION}. "
        "Behaviour may differ or be incompatible."
    )
endif()

add_library(gamemath_lib STATIC
    Homework1.c
)

target_include_directories(gamemath_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Tests
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
