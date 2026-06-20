#include <K10-K10/line/line.h>
#include <K10-K10/line/text.h>
#include <K10-K10/style/alignment.h>

#include <cstddef>
#include <vector>

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

  Line left_accum, center_accum, right_accum;

  for (size_t i = 0; i < new_.contents_.size(); ++i) {
    const auto& item = new_.contents_[i];

    switch (item.second) {
      case krow::style::alignment::LEFT:
        left_accum.contents_.push_back(item);
        break;
      case krow::style::alignment::CENTER:
        center_accum.contents_.push_back(item);
        break;
      case krow::style::alignment::RIGHT:
        right_accum.contents_.push_back(item);
        break;
      default:
        break;
    }
    if (i == new_.contents_.size() - 1 || new_.break_) {
      if (!left_accum.contents_.empty())
        contents_[current_].left.push(left_accum);
      if (!center_accum.contents_.empty())
        contents_[current_].center.push(center_accum);
      if (!right_accum.contents_.empty())
        contents_[current_].right.push(right_accum);

      left_accum.contents_.clear();
      center_accum.contents_.clear();
      right_accum.contents_.clear();

      if (new_.break_ && i < new_.contents_.size() - 1) {
        ++current_;
        contents_.resize(current_ + 1);
      }
    }
  }

  return *this;
}

krow::Text krow::operator+(const krow::Text& lhs, const krow::Line& rhs) {
  krow::Text text = lhs;

  if (text.contents_.empty()) {
    text.contents_.resize(1);
    text.current_ = 0;
  }

  krow::Text::line& current_line = text.contents_[text.current_];

  Line left_accum, center_accum, right_accum;
  for (const auto& item : rhs.contents_) {
    switch (item.second) {
      case krow::style::alignment::LEFT:
        left_accum.contents_.push_back(item);
        break;
      case krow::style::alignment::CENTER:
        center_accum.contents_.push_back(item);
        break;
      case krow::style::alignment::RIGHT:
        right_accum.contents_.push_back(item);
        break;
      default:
        break;
    }
  }

  if (!left_accum.contents_.empty()) current_line.left.push(left_accum);
  if (!center_accum.contents_.empty()) current_line.center.push(center_accum);
  if (!right_accum.contents_.empty()) current_line.right.push(right_accum);

  if (rhs.break_) {
    text.contents_.resize(text.contents_.size() + 1);
    text.current_ = text.contents_.size() - 1;
  }

  return text;
}
