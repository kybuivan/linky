// Copyright (c) 2023-2024 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <core/typedefs.hpp>

namespace linky::core {
enum keycode
{
    backspace = 0x08,
    tab = 0x09,
    clear = 0x0c,  // clear (on numpad)
    return = 0x0d, // enter
    shift = 0x10,
    control = 0x11, // ctrl
    menu = 0x12,    // alt
    pause = 0x13,   // pause/break
    captial = 0x14, // caps lock
    esc = 0x1b,     // escape
    space = 0x20,   // space bar

    prior = 0x21, // page up
    next = 0x22,  // page down
    end = 0x23,
    home = 0x24,

    left = 0x25,
    up = 0x26,
    right = 0x27,
    down = 0x28,

    snapshot = 0x2C, // print screen
    insert = 0x2D,   // ins
    delete = 0x2E,   // del

    lwin = 0x5B,
    rwin = 0x5C,
    apps = 0x5D,

    // clang-format off

    // -- numeric:

    _0 = 0x30,
    _1, _2, _3, _4, _5, _6, _7, _8, _9,

    // -- alpha:

    a = 0x41,
    b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,

    // -- numpad:

    num0 = 0x60,
    num1, num2, num3,
    num4, num5, num6,
    num7, num8, num9,
    multiply, add,
    separator, subtract, decimal, divide,

    // -- func

    f1 = 0x70,
    f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,

    // clang-format on

    numlock = 0x90,  // num lock
    slock = 0x91,    // scroll lock

    lshift = 0xA0,   // left shift
    rshift = 0xA1,   // right shift
    lcontrol = 0xA2, // left control
    rcontrol = 0xA3, // right control
    lmenu = 0xA4,    // left alt
    rmenu = 0xA5     // right alt
};

enum mouse_code
{
    button0 = 0,
    button1 = 1,
    button2 = 2,
    button3 = 3,
    button4 = 4,
    button5 = 5,
    button6 = 6,
    button7 = 7,

    mouse_last = button7,
    mouse_left = button0,
    mouse_right = button1,
    mouse_middle = button2,
};
}