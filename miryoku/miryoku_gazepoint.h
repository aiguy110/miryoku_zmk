// gazepoint (https://github.com/aiguy110/gazepoint) integration.
// Holding the MOUSE thumb also holds U_GAZE_AIM_KEY, which gazepoint uses as
// its hotkey: the cursor jumps to where you look and head motion refines it.

#pragma once

#define U_GAZE_AIM_KEY F14   // KEY_F14 on Linux (XF86Launch5, unbound by default)
#define U_GAZE_REAIM_KEY F15 // KEY_F15: jump to gaze again mid-hold (e.g. drag)

#define U_GAZE_LT(LAYER, TAP) &u_gaze_lt LAYER TAP
#define U_GAZE_REAIM &kp U_GAZE_REAIM_KEY
