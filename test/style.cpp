#include <K10-K10/style/alignment.h>
#include <K10-K10/style/style.h>
#include <gtest/gtest.h>

namespace __krow__ {
std::string to_ansi(const krow::style::Style& style);
}

using Style = krow::style::Style;
using Color = krow::style::Color;
using BasicColor = krow::style::BasicColor;

TEST(ANSI_STYLE_TEST, Basic) {
  Style s1 = krow::style::Default();
  EXPECT_EQ(__krow__::to_ansi(s1), "\033[39;49");

  Style s2 = krow::style::Default().fg(Color(BasicColor::Red));
  EXPECT_EQ(__krow__::to_ansi(s2), "\033[31;49");

  Style s3 = krow::style::Default().bg(Color(BasicColor::Blue));
  EXPECT_EQ(__krow__::to_ansi(s3), "\033[39;44");
}

TEST(ANSI_STYLE_TEST, Extended256) {
  Style s1 = krow::style::Default().fg(Color(123));
  EXPECT_EQ(__krow__::to_ansi(s1), "\033[38;5;123;49");

  Style s2 = krow::style::Default().bg(Color(210));
  EXPECT_EQ(__krow__::to_ansi(s2), "\033[39;48;5;210");
}

TEST(ANSI_STYLE_TEST, RGB) {
  Style s1 = krow::style::Default().fg(Color(255, 0, 0));
  EXPECT_EQ(__krow__::to_ansi(s1), "\033[38;2;255;0;0;49");

  Style s2 = krow::style::Default().bg(Color(0, 255, 128));
  EXPECT_EQ(__krow__::to_ansi(s2), "\033[39;48;2;0;255;128");
}

TEST(ALIGNMENT_TEST, LEFT) {
  EXPECT_EQ(
      __terminal__::calc_alignment(terminal::style::alignment::LEFT, {0, 6}, 4),
      0);
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::LEFT,
                                         {10, 6}, 4),
            10);
}

TEST(ALIGNMENT_TEST, CENTER) {
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::CENTER,
                                         {0, 6}, 4),
            1);
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::CENTER,
                                         {10, 11}, 5),
            13);
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::CENTER,
                                         {10, 10}, 5),
            12);
}

TEST(ALIGNMENT_TEST, RIGHT) {
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::RIGHT,
                                         {0, 6}, 4),
            2);
  EXPECT_EQ(__terminal__::calc_alignment(terminal::style::alignment::RIGHT,
                                         {10, 6}, 4),
            12);
}
