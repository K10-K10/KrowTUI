#ifndef INCLUDE_LINE_TEXT_H_
#define INCLUDE_LINE_TEXT_H_

#include <K10-K10/line/line.h>

#include <queue>
#include <vector>

namespace krow {
class TextField;
class Block;
class List;

struct Text;

Text operator+(const Text& lhs, const Span& rhs);
Text operator+(const Text& lhs, const Line& rhs);

struct Text {
 private:
  struct line {
    std::queue<Line> left;
    std::queue<Line> center;
    std::queue<Line> right;
  };

 public:
  Text() : contents_(1), current_(0) {}
  Text(const Line& new_);
  Text& operator=(const Line& new_);
  bool empty() {
    if (contents_.empty()) {
      return true;
    }
    if (contents_[0].left.empty() && contents_[0].center.empty() &&
        contents_[0].right.empty()) {
      return true;
    }
    return false;
  }

 private:
  friend Text operator+(const Text& lhs, const Line& rhs);
  friend Text operator+(const Text& lhs, const Line& rhs);
  friend class TextField;
  friend class Block;
  friend class List;
  std::vector<line> contents_;
  int current_ = 0;
};

}  // namespace krow

#endif
