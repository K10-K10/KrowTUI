#pragma once

#include <K10-K10/app/app.h>
#include <K10-K10/feat/feature.h>
#include <K10-K10/input/cursor.h>
#include <K10-K10/input/keyboard.h>
#include <K10-K10/layout/rect.h>
#include <K10-K10/obj/block.h>
#include <K10-K10/obj/input.h>
#include <K10-K10/obj/list.h>
#include <K10-K10/obj/text.h>
#include <K10-K10/style/color.h>

namespace terminal {
__terminal__::Render render;
__terminal__::App app(render);
}  // namespace terminal
