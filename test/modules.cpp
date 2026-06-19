#include <K10-K10/utils/string_helper.h>
#include <gtest/gtest.h>

#include <vector>

TEST(STRING_VISUAL_WIDTH_TEST, SINGLE_MULTI) {
  EXPECT_EQ(__krow__::get_visual_width(""), 0);
  EXPECT_EQ(__krow__::get_visual_width(" "), 1);
  EXPECT_EQ(__krow__::get_visual_width("Hello, World!"), 13);
  EXPECT_EQ(__krow__::get_visual_width("あいうえお"), 10);
  EXPECT_EQ(__krow__::get_visual_width("你好"), 4);
}

TEST(STRING_VISUAL_WIDTH_TEST, MULTI) {
  std::vector<__krow__::VisualChar> test1 = {
      {"T", 1}, {"e", 1}, {"s", 1}, {"t", 1}, {"!", 1}};
  EXPECT_EQ(__krow__::split_by_visual_character("Test!"), test1);

  std::vector<__krow__::VisualChar> test2 = {
      {"H", 1},  {"e", 1},  {"l", 1},  {"l", 1},  {"o", 1},
      {"こ", 2}, {"ん", 2}, {"に", 2}, {"ち", 2}, {"は", 2}};
  EXPECT_EQ(__krow__::split_by_visual_character("Helloこんにちは"), test2);
  auto result3 = __krow__::split_by_visual_character("test你好こんにちは!");

  EXPECT_EQ(result3.size(), 12);

  int total_width = 0;
  for (const auto& vc : result3) {
    total_width += vc.width;
  }
  EXPECT_EQ(total_width, 19);
}
