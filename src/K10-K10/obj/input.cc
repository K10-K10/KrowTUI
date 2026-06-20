#include <K10-K10/core/screen.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/line/line.h>
#include <K10-K10/obj/input.h>
#include <K10-K10/style/alignment.h>
#include <K10-K10/style/style.h>
#include <K10-K10/utils/string_helper.h>

#include <algorithm>
#include <cstddef>
#include <queue>
#include <string>
#include <vector>

namespace krow {

Text& TextField::operator[](size_t index) {
  if (index >= contents_.size()) {
    contents_.resize(index + 1);
  }
  return contents_[index];
}

TextField& TextField::contents(const std::vector<Text>& text) {
  contents_ = text;
  max_length_ = 0;

  for (const auto& t_obj : contents_) {
    int row_width = 0;
    for (const auto& row : t_obj.contents_) {
      auto check_len = [](std::queue<Line> q) {
        int len = 0;
        while (!q.empty()) {
          for (const auto& c : q.front().contents_) {
            len += ::__krow__::get_visual_width(c.first.text_);
          }
          q.pop();
        }
        return len;
      };
      row_width +=
          check_len(row.left) + check_len(row.center) + check_len(row.right);
    }
    max_length_ = std::max(max_length_, row_width);
  }
  return *this;
}

TextField& TextField::move_cursor(int x, int y) {
  if (x < 0 || y < 0) {
    return *this;
  }
  if (y >= contents_.size()) {
    return *this;
  }

  int text_glyph_count = 0;
  for (const auto& row : contents_[y].contents_) {
    auto count_q = [](std::queue<Line> q) {
      int cnt = 0;
      while (!q.empty()) {
        for (const auto& c : q.front().contents_) {
          auto chars = ::__krow__::split_by_visual_character(c.first.text_);
          cnt += chars.size();
        }
        q.pop();
      }
      return cnt;
    };
    text_glyph_count +=
        count_q(row.left) + count_q(row.center) + count_q(row.right);
  }

  if (x > text_glyph_count) {
    return *this;
  }

  cursor_x = x;
  cursor_y = y;
  return *this;
}

TextField& TextField::insert_char(const std::string& c) {
  if (cursor_y >= contents_.size()) {
    return *this;
  }
  std::vector<std::string> glyphs;
  for (const auto& row : contents_[cursor_y].contents_) {
    auto collect = [&](std::queue<Line> q) {
      while (!q.empty()) {
        for (const auto& span_element : q.front().contents_) {
          auto chars =
              ::__krow__::split_by_visual_character(span_element.first.text_);
          for (const auto& vc : chars) {
            glyphs.push_back(vc.get_c());
          }
        }
        q.pop();
      }
    };
    collect(row.left);
    collect(row.center);
    collect(row.right);
  }

  if (cursor_x >= glyphs.size()) {
    glyphs.resize(cursor_x, " ");
    glyphs.push_back(c);
  } else {
    glyphs.insert(glyphs.begin() + cursor_x, c);
  }

  std::string merged_str;
  for (const auto& g : glyphs) {
    merged_str += g;
  }
  Line new_line = Line();
  const Span s = merged_str;
  s.style(text_style_);
  new_line.contents_.push_back({s, style::alignment::LEFT});
  contents_[cursor_y] = new_line;

  cursor_x++;
  return *this;
}

TextField& TextField::delete_char() {
  if (cursor_y >= contents_.size()) {
    return *this;
  }

  std::vector<std::string> glyphs;
  for (const auto& row : contents_[cursor_y].contents_) {
    auto collect = [&](std::queue<Line> q) {
      while (!q.empty()) {
        for (const auto& span_element : q.front().contents_) {
          auto chars =
              ::__krow__::split_by_visual_character(span_element.first.text_);
          for (const auto& vc : chars) {
            glyphs.push_back(vc.get_c());
          }
        }
        q.pop();
      }
    };
    collect(row.left);
    collect(row.center);
    collect(row.right);
  }

  if (cursor_x < glyphs.size()) {
    glyphs.erase(glyphs.begin() + cursor_x);

    std::string merged_str;
    for (const auto& g : glyphs) {
      merged_str += g;
    }

    Line new_line = Line();
    const Span s = merged_str;
    s.style(text_style_);
    new_line.contents_.push_back({s, style::alignment::LEFT});
    contents_[cursor_y] = new_line;
  }
  return *this;
}

void TextField::draw() {
  const int l = rect.x;
  const int w = (rect.w == FULL) ? ::__krow__::screen.width() : rect.w;
  const int t = rect.y;
  const int h = (rect.h == FULL) ? ::__krow__::screen.height() : rect.h;
  if (w < 1 || h < 1) {
    return;
  }

  const int offset_x = std::max(0, cursor_x - w + 1);
  const int offset_y = std::max(0, cursor_y - h + 1);

  for (int screen_y = 0; screen_y < h; ++screen_y) {
    const int data_y = offset_y + screen_y;
    const int cy = t + screen_y;

    for (int sx = 0; sx < w; ++sx) {
      ::__krow__::screen.put(cy, l + sx, {" ", text_style_});
    }

    if (data_y >= contents_.size()) {
      continue;
    }

    std::vector<::__krow__::VisualChar> all_vchars;
    for (const auto& row : contents_[data_y].contents_) {
      auto process_queue = [&](std::queue<Line> q) {
        while (!q.empty()) {
          for (const auto& span_item : q.front().contents_) {
            auto v_chars =
                ::__krow__::split_by_visual_character(span_item.first.text_);
            for (auto& vc : v_chars) {
              all_vchars.push_back(vc);
            }
          }
          q.pop();
        }
      };
      process_queue(row.left);
      process_queue(row.center);
      process_queue(row.right);
    }

    const int current_visual_x = 0;
    int current_screen_x = 0;
    for (size_t glyph_idx = 0; glyph_idx < all_vchars.size(); ++glyph_idx) {
      const auto& vc = all_vchars[glyph_idx];

      if (static_cast<int>(glyph_idx) < offset_x) {
        continue;
      }

      if (current_screen_x >= w) {
        break;
      }

      const bool is_cursor =
          (static_cast<int>(glyph_idx) == cursor_x && data_y == cursor_y);

      const krow::style::Style final_style =
          is_cursor ? cursor_style_ : text_style_;

      ::__krow__::screen.put(cy, l + current_screen_x,
                             {vc.get_c(), final_style});
      current_screen_x += vc.get_width();
    }

    if (data_y == cursor_y && cursor_x == static_cast<int>(all_vchars.size())) {
      const int screen_x = cursor_x - offset_x;
      if (screen_x >= 0 && screen_x < w) {
        ::__krow__::screen.put(cy, l + screen_x, {" ", cursor_style_});
      }
    }
  }
}

}  // namespace krow
