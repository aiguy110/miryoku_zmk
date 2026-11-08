// Gaming layer: plain keys (no home-row mods, no hold-taps) on the left half,
// alphas shifted one column right so WASD sits under ring/middle/index.
//
// Enter:  hold MEDIA (left outer thumb), double-tap the T position.
//         (Also on NAV / MOUSE / NUM / SYM / FUN, next to the other mode keys.)
// Exit:   hold the GAME outer thumb (GAME_FN), double-tap the left pinky
//         bottom key. GAME_FN thumb keys are unusable (the same thumb is
//         holding Fn), so they just pass through.

#pragma once

#define MIRYOKU_LAYER_GAME \
&kp TAB,           &kp Q,             &kp W,             &kp E,             &kp R,             &kp Y,             &kp U,             &kp I,             &kp O,             &kp P,             \
&kp LSHFT,         &kp A,             &kp S,             &kp D,             &kp F,             &kp H,             &kp J,             &kp K,             &kp L,             &kp SQT,           \
&kp LCTRL,         &kp Z,             &kp X,             &kp C,             &kp V,             &kp N,             &kp M,             &kp COMMA,         &kp DOT,           &kp SLASH,         \
U_NP,              U_NP,              &u_game_lt U_GAME_FN ESC,&kp SPACE,    &kp LALT,          &kp RET,           &kp BSPC,          &kp DEL,           U_NP,              U_NP

#define MIRYOKU_LAYER_GAME_FN \
&kp N1,            &kp N2,            &kp N3,            &kp N4,            &kp N5,            &kp GRAVE,          &trans,            &trans,            &trans,            &trans,            \
&kp N6,            &kp N7,            &kp N8,            &kp N9,            &kp N0,            &trans,            &trans,            &trans,            &trans,            &trans,            \
&u_to_U_BASE,      &kp T,             &kp G,             &kp B,             &kp M,             &trans,            &trans,            &trans,            &trans,            &trans,            \
U_NP,              U_NP,              U_NA,              &trans,            &trans,            &trans,            &trans,            &trans,            U_NP,              U_NP

#define MIRYOKU_LAYERMAPPING_GAME MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_GAME_FN MIRYOKU_MAPPING
