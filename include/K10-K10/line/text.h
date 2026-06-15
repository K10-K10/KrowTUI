#ifndef INCLUDE_LINE_TEXT_H_
#define INCLUDE_LINE_TEXT_H_

#include <K10-K10/line/line.h>
#include <K10-K10/style/alignment.h>

#include <queue>
#include <vector>

namespace terminal {
struct Text {
 private:
  struct line {
    std::queue<Line> left;
    std::queue<Line> center;
    std::queue<Line> right;
  };

 public:
  Text(const Line& new_);
  void operator=(const Line& new_);
  std::vector<line> contents_;

 private:
  int current_ = 0;
};
}  // namespace terminal

#endif
