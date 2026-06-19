#ifndef INCLUDE_KROW_H_
#define INCLUDE_KROW_H_

#include <K10-K10/app/app.h>
#include <K10-K10/input/cursor.h>
#include <K10-K10/input/keyboard.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/block.h>
#include <K10-K10/obj/input.h>
#include <K10-K10/obj/list.h>
#include <K10-K10/obj/text.h>
#include <K10-K10/style/border.h>
#include <K10-K10/style/color.h>
#include <K10-K10/style/style.h>

namespace krow {
inline __krow__::Render render;
inline __krow__::App app(render);
}  // namespace krow

#endif
