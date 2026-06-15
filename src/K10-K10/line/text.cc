#include <K10-K10/line/text.h>

terminal::Text::Text(const Line& new_) : contents_(1) {
  switch (new_.al_) {
    case terminal::style::alignment::LEFT:
      this->contents_[current_].left.push(new_);
      break;
    case terminal::style::alignment::CENTER:
      this->contents_[current_].center.push(new_);
      break;
    case terminal::style::alignment::RIGHT:
      this->contents_[current_].right.push(new_);
      break;
    default:
      break;
  }
  if (new_.break_) {
    ++current_;
    contents_.push_back({});
  }
}

void terminal::Text::operator=(const Line& new_) {
  contents_.clear();
  contents_.resize(1);
  current_ = 0;
  switch (new_.al_) {
    case terminal::style::alignment::LEFT:
      this->contents_[current_].left.push(new_);
      break;
    case terminal::style::alignment::CENTER:
      this->contents_[current_].center.push(new_);
      break;
    case terminal::style::alignment::RIGHT:
      this->contents_[current_].right.push(new_);
      break;
    default:
      break;
  }
  if (new_.break_) {
    ++current_;
  }
};
