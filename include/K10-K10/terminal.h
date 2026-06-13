#ifndef INCLUDE_TERMINAL_H_
#define INCLUDE_TERMINAL_H_

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

namespace terminal {
inline __terminal__::Render render;
inline __terminal__::App app(render);
}  // namespace terminal

#endif
