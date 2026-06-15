#ifndef INCLUDE_LINE_LINE_H_
#define INCLUDE_LINE_LINE_H_

#include <K10-K10/style/alignment.h>
#include <K10-K10/style/style.h>

#include <string>
#include <vector>

namespace terminal {

struct Text;

struct Line;

struct Span {
 public:
  Span(std::string s) { text_ = s; }
  Span& style(style::Style style_) {
    style_val = style_;
    return *this;
  }

 private:
  friend struct Line;
  friend Line operator+(const Span& lhs, const Span& rhs);

  std::string text_;
  style::Style style_val = style::Default();
};

struct Line {
 public:
  Line() = default;

  Line(const Span& span) { contents_.push_back(span); }

  Line operator+(const Span& as) const {
    Line result = *this;
    result.contents_.push_back(as);
    return result;
  }

  Line operator+(const Line& rhs) const {
    Line result = *this;
    result.contents_.insert(result.contents_.end(), rhs.contents_.begin(),
                            rhs.contents_.end());
    return result;
  }

  inline Line& break_ln() {
    break_ = true;
    return *this;
  };

  inline Line& alignment_left() {
    al_ = style::alignment::left;
    return *this;
  }

  inline Line& alignment_center() {
    al_ = style::alignment::center;
    return *this;
  }

  inline Line& alignment_right() {
    al_ = style::alignment::right;
    return *this;
  }

 protected:
  friend Text;
  std::vector<Span> contents_;
  bool break_ = false;
  style::alignment al_ = style::alignment::left;

 private:
  friend Line operator+(const Span& lhs, const Span& rhs);
};

inline Line operator+(const Span& lhs, const Span& rhs) {
  Line line;
  line.contents_.push_back(lhs);
  line.contents_.push_back(rhs);
  return line;
}

inline Span operator"" _s(const char* str, std::size_t len) {
  return Span(std::string(str, len));
}

}  // namespace terminal

#endif
