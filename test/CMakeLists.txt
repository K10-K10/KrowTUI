set(TEST_SOURCES
  style.cpp
  modules.cpp
)

find_package(GTest REQUIRED)

add_executable(terminal_test ${TEST_SOURCES})

target_link_libraries(terminal_test PRIVATE
  K10-K10::terminal
  GTest::gtest_main
)

target_compile_definitions(terminal_test PRIVATE ENABLE_LOGGER)

include(GoogleTest)
gtest_discover_tests(terminal_test)
