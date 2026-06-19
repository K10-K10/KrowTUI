#ifndef INCLUDE_LINE_LINE_H_
#define INCLUDE_LINE_LINE_H_

#include <K10-K10/style/alignment.h>
#include <K10-K10/style/style.h>

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace krow {

class TextField;
class Block;
class List;

struct Text;

struct Line;

struct Span {
 public:
  Span(std::string s) { text_ = std::move(s); }
  Span style(style::Style& style_) const {
    Span result = *this;
    result.style_val = style_;
    return result;
  }

 private:
  friend struct Line;
  friend class TextField;
  friend class Block;
  friend class List;
  std::string text_;

  friend Line operator+(const Span& lhs, const Span& rhs);

  style::Style style_val = style::Default();
};

struct Line {
 public:
  Line() = default;

  Line(const Span& span) { contents_.push_back({span, al_}); }

  Line operator+(const Span& as) const {
    Line result = *this;
    result.contents_.push_back({as, al_});
    return result;
  }

  Line operator+(const Line& rhs) const {
    Line result = *this;
    for (size_t i = 0; i < rhs.contents_.size(); ++i) {
      result.contents_.push_back(rhs.contents_[i]);
    }
    return result;
  }

  Line& break_ln() {
    break_ = true;
    return *this;
  };

  Line& alignment_left() {
    al_ = style::alignment::LEFT;
    for (auto& item : contents_) {
      item.second = style::alignment::LEFT;
    }
    return *this;
  }

  Line& alignment_center() {
    al_ = style::alignment::CENTER;
    for (auto& item : contents_) {
      item.second = style::alignment::CENTER;
    }
    return *this;
  }

  Line& alignment_right() {
    al_ = style::alignment::RIGHT;
    for (auto& item : contents_) {
      item.second = style::alignment::RIGHT;
    }
    return *this;
  }

 protected:
  friend class TextField;
  friend class Block;
  friend class List;
  friend Text;

  bool get_break() const { return break_; }
  std::vector<std::pair<Span, style::alignment>> get_contents() {
    return contents_;
  }
  style::alignment get_al() const { return al_; }

 private:
  style::alignment al_ = style::alignment::LEFT;
  bool break_ = false;
  std::vector<std::pair<Span, style::alignment>> contents_;
  friend Line operator+(const Span& lhs, const Span& rhs);
};

inline Line operator+(const Span& lhs, const Span& rhs) {
  Line line;
  line.contents_.push_back({lhs, style::alignment::LEFT});
  line.contents_.push_back({rhs, style::alignment::LEFT});
  return line;
}

inline Span operator"" _s(const char* str, std::size_t len) {
  return Span(std::string(str, len));
}

}  // namespace krow

#endif
