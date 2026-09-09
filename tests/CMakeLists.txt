# ── Settings ─────────────────────────────────────────────────────────────────
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Google Test ──────────────────────────────────────────────────────────────
include(GoogleTest)
enable_testing()

# ───────────────────────────────────────────────────────────────────────────── 
# Target: c_linalg_test
# Alias: c_linalg::c_linalg_test
# Type: Executable
# Dependencies: GTest::gtest_main,
#               GTest::gmock_main,
#               c_linalg::c_linalg_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_executable(c_linalg_test)

# Target alias
add_executable(c_linalg::c_linalg_test
    ALIAS c_linalg_test
)

# Target sources
target_sources(c_linalg_test
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/c_linalg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/c_linalg_test.cpp
)

# Target dependencies
target_link_libraries(c_linalg_test
    PRIVATE
        c_linalg::c_linalg_headers
        GTest::gtest_main
        GTest::gmock_main
)

# Test discovery
gtest_discover_tests(c_linalg_test)
