#include <K10-K10/line/line.h>
#include <K10-K10/line/text.h>
#include <K10-K10/style/alignment.h>

#include <cstddef>

krow::Text::Text(const Line& new_) {
  contents_.resize(1);
  current_ = 0;

  for (const auto& item : new_.contents_) {
    const auto& span = item.first;
    const auto& align = item.second;

    Line single_element_line;
    single_element_line.contents_.push_back(item);

    if (align == style::alignment::LEFT) {
      contents_[current_].left.push(single_element_line);
    } else if (align == style::alignment::CENTER) {
      contents_[current_].center.push(single_element_line);
    } else if (align == style::alignment::RIGHT) {
      contents_[current_].right.push(single_element_line);
    }
  }
}

krow::Text& krow::Text::operator=(const Line& new_) {
  contents_.clear();
  current_ = 0;

  contents_.resize(1);

  Line left, center, right;

  for (size_t i = 0; i < new_.contents_.size(); ++i) {
    switch (new_.contents_[i].second) {
      case krow::style::alignment::LEFT:
        left = left + new_.contents_[i].first;
        break;
      case krow::style::alignment::CENTER:
        center = center + new_.contents_[i].first;
        break;
      case krow::style::alignment::RIGHT:
        right = right + new_.contents_[i].first;
        break;
      default:
        break;
    }
    if (contents_.size() <= current_) {
      contents_.resize(current_ + 1);
    }

    contents_[current_].left.push(left);
    contents_[current_].center.push(center);
    contents_[current_].right.push(right);

    if (new_.break_) {
      ++current_;
      contents_.resize(current_ + 1);
    }

    return *this;
  }
  return *this;
}
