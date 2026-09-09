# CLAUDE.md

Personal fork of [manna-harbour/miryoku_zmk](https://github.com/manna-harbour/miryoku)
(`git@github.com:aiguy110/miryoku_zmk`). Builds a **Corne** on **nice_nano_v2**,
Bluetooth-only, via GitHub Actions.

## Where the build config actually lives

**`.github/workflows/auto-build.yml` is the source of truth for this keyboard.**
Not `miryoku/custom_config.h` — that file is empty in the repo and is *generated at
build time*.

```yaml
board:   ["nice_nano_v2"]
shield:  ["corne_left","corne_right","settings_reset"]
alphas:  ["QWERTY"]
nav:     ["vi"]
layers:  ["default"]     # non-flipped
mapping: ["default"]
```

`.github/workflows/main.yml:119-130` turns each non-`default` input into a
`#define MIRYOKU_<OPTION>_<VALUE>` appended to `custom_config.h` before the build.
So this build compiles with `MIRYOKU_ALPHAS_QWERTY` and `MIRYOKU_NAV_VI` defined.

**Do not conclude "custom_config.h is empty, therefore defaults apply."** That would
give you Colemak-DH and the stock MEDIA layer, both wrong for this board.

Auto-build only triggers on push to / PR against `master`. Pushing a topic branch
builds nothing.

## Local customizations vs. upstream

Only two things diverge from upstream miryoku:

1. **`miryoku/miryoku_babel/miryoku_layer_alternatives.h:117`** — home-row mods on the
   QWERTY base layer, reordered pinky→index to **Shift, Ctrl, Super, Alt**
   (commit `1cc0e5d`). Upstream is GUI, Alt, Ctrl, Shift.

   ```
   U_MT(LSHFT, A), U_MT(LCTRL, S), U_MT(LGUI, D), U_MT(LALT, F), ...
   ```

   ⚠️ **This edit is base-layer only.** MEDIA / NAV / MOUSE / NUM / SYM / FUN all
   still carry the upstream order (`GUI, Alt, Ctrl, Shift` pinky→index), so
   **Shift is on the index finger on every non-base layer** but on the pinky on base.
   Miryoku has no config option for mod order — it is hardcoded per layer in
   `miryoku_layer_alternatives.h`, which is why this was a manual edit.

2. **`config/corne.conf`** — keyboard name, deep sleep, mouse keys.

   ```
   CONFIG_ZMK_SLEEP=y
   CONFIG_ZMK_IDLE_SLEEP_TIMEOUT=600000   # 10 min
   CONFIG_ZMK_POINTING=y
   CONFIG_ZMK_KEYBOARD_NAME="Josiah_Chocofi"
   ```

## Reading the keymap

Layer content resolves through three files:

- `miryoku/miryoku_babel/miryoku_layer_alternatives.h` — every layer variant
- `miryoku/miryoku_babel/miryoku_layer_selection.h` — picks the variant from the
  `MIRYOKU_*` defines
- `miryoku/mapping/42/corne.h` — maps the 10-per-row logical layout onto physical keys

Two traps when tracing a key position:

- **Pick the right variant.** `nav: vi` selects `MIRYOKU_ALTERNATIVES_MEDIA_VI`
  (`miryoku_layer_selection.h:234`), *not* `MIRYOKU_ALTERNATIVES_MEDIA`. The VI
  variant shifts the whole Bluetooth row one key left. `layers: default` means
  the non-`_FLIP` variants — the `_FLIP` ones mirror the halves and are easy to
  misread as the real layout.
- **The outer pinky columns are dead.** `mapping/42/corne.h` emits `XXX` (`&none`)
  for the leftmost column of the left half and the rightmost column of the right
  half. Only the inner 5 columns per hand are live, so "rightmost key" in the
  source is the *second* column from the edge physically.

### Base layer (QWERTY, non-flipped) thumbs

```
left:  ESC(MEDIA)  SPACE(NAV)  TAB(MOUSE)   |   right: RET(SYM)  BSPC(NUM)  DEL(FUN)
```

MEDIA is the **outermost left thumb**.

## Bluetooth pairing

BT profile keys are on the **MEDIA layer, bottom row, right hand**
(`miryoku_layer_alternatives.h:334`, the VI variant):

| QWERTY position | N | M | , | . | / |
|---|---|---|---|---|---|
| binding | BT 0 | BT 1 | BT 2 | **BT 3** | out_tog |

(Stock non-VI MEDIA puts `out_tog` on `N` and shifts BT 0–3 right by one. Don't use
that table for this build.)

Tapping `&bt BT_SEL n` only *switches* profiles — if the slot holds a stale bond the
board connects to it instead of advertising, and no host sees it. The shifted
mod-morph is what puts it into pairing mode
(`miryoku/miryoku_shift_functions.dtsi:20-24`):

```
u_bt_sel_3:  unshifted = &bt BT_SEL 3
             shifted   = &bt BT_SEL 3 &bt BT_CLR
```

Shift on the MEDIA layer is the **left index home-row key** (`F` position,
`miryoku_layer_alternatives.h:333`) — upstream mod order, see caveat above.

**To pair on profile 3:**

1. Hold outermost **left thumb** (ESC / MEDIA)
2. Hold **left index home row** (`F`)
3. Tap **right ring, bottom row** (`.`)

Then pair from the host.

Gotchas:

- Profiles are 0-indexed and only 0–3 are bound. "Slot 3" = the fourth profile = `.`.
- Remove the old bond **on the host** too; otherwise re-pairing fails silently.
- Hosts cache the device name against the old bond, so a host that knew the board
  before may still show a previous name (`CONFIG_ZMK_KEYBOARD_NAME` has been changed
  several times here — see commits `a97138b`, `c607dba`, `3849b39`).
- Deep sleep is on at 10 min idle — tap a key to wake before the sequence.
- Profile changes are handled by the central half; if the halves aren't connected to
  each other, presses on the peripheral won't reach it.
- `settings_reset` is already in the build shield list — flash it to wipe all bonds
  if a profile stays wedged.
