// gazepoint (https://github.com/aiguy110/gazepoint) integration.
// Holding the MOUSE thumb also holds U_GAZE_AIM_KEY, which gazepoint uses as
// its hotkey: the cursor jumps to where you look and head motion refines it.

#pragma once

#define U_GAZE_AIM_KEY F14   // KEY_F14 on Linux (XF86Launch5, unbound by default)
#define U_GAZE_REAIM_KEY F15 // KEY_F15: jump to gaze again mid-hold (e.g. drag)

#define U_GAZE_SLOW_KEY F16   // KEY_F16: hold for the low head gain
#define U_GAZE_SCROLL_KEY F17 // KEY_F17: hold to scroll with head motion
#define U_GAZE_LT(LAYER, TAP) &u_gaze_lt LAYER TAP
#define U_GAZE_REAIM &kp U_GAZE_REAIM_KEY
#define U_GAZE_SLOW &kp U_GAZE_SLOW_KEY
#define U_GAZE_SCROLL &kp U_GAZE_SCROLL_KEY
