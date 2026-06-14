#include <K10-K10/debug/logger.h>
#include <gtest/gtest.h>

TEST(DEBUG_TEST, LOGGER) {
  __terminal__::logger::clear_logs();
  __terminal__::logger::add_log(__terminal__::logger::log_type::success,
                                "initialize");

  std::vector<__terminal__::logger::log_value> expected;

  __terminal__::logger::log_value val;
  val.type = __terminal__::logger::log_type::success;
  val.message = "initialize";

  expected.push_back(val);

  EXPECT_EQ(__terminal__::logger::get_logs(), expected);
}
