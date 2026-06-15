// #ifndef INCLUDE_OBJ_TEXT_H_
// #define INCLUDE_OBJ_TEXT_H_

// #include <K10-K10/layout/rect.h>
// #include <K10-K10/obj/obj.h>
// #include <K10-K10/style/style.h>

// #include <string>

namespace krow {

// class Text : private Object {
//  public:
//   explicit Text() = default;
//   ~Text() = default;
//   Text& position(const Rect& r);
//   Text& contents(const std::string& text);
//   std::string contents() const;
//   void draw() override;

//   Text& text_style(const style::Style& s) {
//     text_style_ = s;
//     return *this;
//   }

 private:
  krow::style::Style text_style_;
  Rect rect = {0, 0, 0, 0};
  std::string text_ = "";
};

}  // namespace krow

// #endif
