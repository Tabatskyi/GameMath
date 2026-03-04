include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Prevent GoogleTest from overriding compiler/linker options on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(gamemath_tests
    test_homework1.cpp
)

target_link_libraries(gamemath_tests
    PRIVATE
        gamemath_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(gamemath_tests)
