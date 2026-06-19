#include <K10-K10/debug/logger.h>
#include <gtest/gtest.h>

TEST(DEBUG_TEST, LOGGER) {
  __krow__::logger::clear_logs();
  __krow__::logger::add_log(__krow__::logger::log_type::success, "initialize");

  std::vector<__krow__::logger::log_value> expected;

  __krow__::logger::log_value val;
  val.type = __krow__::logger::log_type::success;
  val.message = "initialize";

  expected.push_back(val);

  EXPECT_EQ(__krow__::logger::get_logs(), expected);
}
