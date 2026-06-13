#include <K10-K10/style/style.h>
#include <gtest/gtest.h>

namespace __terminal__ {
std::string to_ansi(const terminal::style::Style& style);
}

using Style = terminal::style::Style;
using Color = terminal::style::Color;
using BasicColor = terminal::style::BasicColor;

TEST(ANSI_STYLE_TEST, Basic) {
  Style s1 = terminal::style::Default();
  EXPECT_EQ(__terminal__::to_ansi(s1), "\033[39;49");

  Style s2 = terminal::style::Default().fg(Color(BasicColor::Red));
  EXPECT_EQ(__terminal__::to_ansi(s2), "\033[31;49");

  Style s3 = terminal::style::Default().bg(Color(BasicColor::Blue));
  EXPECT_EQ(__terminal__::to_ansi(s3), "\033[39;44");
}

TEST(ANSI_STYLE_TEST, Extended256) {
  Style s1 = terminal::style::Default().fg(Color(123));
  EXPECT_EQ(__terminal__::to_ansi(s1), "\033[38;5;123;49");

  Style s2 = terminal::style::Default().bg(Color(210));
  EXPECT_EQ(__terminal__::to_ansi(s2), "\033[39;48;5;210");
}

TEST(ANSI_STYLE_TEST, RGB) {
  Style s1 = terminal::style::Default().fg(Color(255, 0, 0));
  EXPECT_EQ(__terminal__::to_ansi(s1), "\033[38;2;255;0;0;49");

  Style s2 = terminal::style::Default().bg(Color(0, 255, 128));
  EXPECT_EQ(__terminal__::to_ansi(s2), "\033[39;48;2;0;255;128");
}
