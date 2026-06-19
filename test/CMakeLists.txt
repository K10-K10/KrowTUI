set(TEST_SOURCES
  style.cpp
  modules.cpp
  logger.cpp
)

find_package(GTest REQUIRED)

add_executable(krow_test ${TEST_SOURCES})

target_link_libraries(krow_test PRIVATE
  K10-K10::krow
  GTest::gtest_main
)

target_compile_definitions(krow_test PRIVATE ENABLE_LOGGER)

include(GoogleTest)
gtest_discover_tests(krow_test)
