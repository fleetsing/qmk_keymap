/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUMERAL,
    LAYER_NAVIGATION,
    LAYER_POINTER,
    LAYER_AUTOMOUSE,
    LAYER_MEDIA,
    LAYER_FUNCTION,
    LAYER_SYMBOLS,
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define ENT_NUM LT(LAYER_NUMERAL, KC_ENT)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#define MO_FUN MO(LAYER_FUNCTION)
#define OSM_SFT OSM(MOD_LSFT)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                                                   \
    KC_ESC,     KC_J,       KC_M,       KC_W,       KC_Z,       KC_X,       KC_Q,       KC_SCLN,    KC_QUOT,    KC_LBRC,    \
    KC_N,       KC_R,       KC_T,       KC_S,       KC_G,       KC_P,       KC_H,       KC_A,       KC_E,       KC_I,       \
    KC_B,       KC_L,       KC_D,       KC_C,       KC_V,       KC_K,       KC_F,       KC_O,       KC_U,       KC_Y,       \
                            SPC_NAV,    XXXXXXX,    ENT_NUM,    MO_FUN,     OSM_SFT

/** Convenience row shorthands. */
#define ________________________DEAD_HALF_ROW_____________________  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
#define _______________________HOME_ROW_GACS_L____________________  KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,    XXXXXXX
#define _______________________HOME_ROW_GACS_R____________________  XXXXXXX,    KC_RGUI,    KC_RALT,    KC_RCTL,    KC_RSFT

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                                               \
    ________________________DEAD_HALF_ROW_____________________, KC_PSCR,    KC_F7,      KC_F8,      KC_F9,      KC_F12,     \
    _______________________HOME_ROW_GACS_L____________________, KC_SCRL,    KC_F4,      KC_F5,      KC_F6,      KC_F11,     \
    ________________________DEAD_HALF_ROW_____________________, KC_PAUS,    KC_F1,      KC_F2,      KC_F3,      KC_F10,     \
                            XXXXXXX,    XXXXXXX,    _______,    XXXXXXX,    XXXXXXX

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
#define LAYOUT_LAYER_MEDIA                                                                                                  \
    XXXXXXX,    RGB_RMOD,   RGB_TOG,    RGB_MOD,    XXXXXXX,    XXXXXXX,    RGB_RMOD,   RGB_TOG,    RGB_MOD,    XXXXXXX,    \
    KC_MPRV,    KC_VOLD,    KC_MUTE,    KC_VOLU,    KC_MNXT,    KC_MPRV,    KC_VOLD,    KC_MUTE,    KC_VOLU,    KC_MNXT,    \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    EE_CLR,     QK_BOOT,    QK_BOOT,    EE_CLR,     XXXXXXX,    XXXXXXX,    XXXXXXX,    \
                            _______,    KC_MPLY,    KC_MSTP,    KC_MSTP,    KC_MPLY

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                                                \
    QK_BOOT,    EE_CLR,     XXXXXXX,    DPI_MOD,    S_D_MOD,    S_D_MOD,    DPI_MOD,    XXXXXXX,    EE_CLR,     QK_BOOT,    \
    KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,    XXXXXXX,    XXXXXXX,    MS_BTN1,    MS_BTN2,    XXXXXXX,    XXXXXXX,    \
    _______,    DRGSCRL,    SNIPING,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    SNIPING,    DRGSCRL,    _______,    \
                            MS_BTN1,    XXXXXXX,    MS_BTN2,    MS_BTN3,    MS_BTN1

/** \brief Automatic mouse layer. */
#define LAYOUT_LAYER_AUTOMOUSE                                                                                              \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
                            MS_BTN1,    XXXXXXX,    MS_BTN2,    MS_BTN2,    MS_BTN1

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                                                             \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PGUP,    S(KC_TAB),  KC_UP,      KC_TAB,     XXXXXXX,    \
    KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,    KC_DEL,     KC_BSPC,    KC_LEFT,    KC_DOWN,    KC_RGHT,    XXXXXXX,    \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_PGDN,    KC_HOME,    KC_INS,     KC_END,     KC_ENT,     \
                            _______,    _______,    XXXXXXX,    KC_ENT,     KC_BSPC

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                                                \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_7,       KC_8,       KC_9,       XXXXXXX,    \
    KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,    KC_DEL,     KC_BSPC,    KC_4,       KC_5,       KC_6,       KC_0,       \
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_1,       KC_2,       KC_3,       KC_ENT,     \
                            KC_SPC,     XXXXXXX,    _______,    XXXXXXX,    _______

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                                                \
    KC_LCBR,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RCBR,    ________________________DEAD_HALF_ROW_____________________, \
    KC_COLN,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_PLUS,    _______________________HOME_ROW_GACS_R____________________, \
    KC_TILD,    KC_EXLM,    KC_AT,      KC_HASH,    KC_PIPE,    ________________________DEAD_HALF_ROW_____________________, \
                            KC_LPRN,    KC_RPRN,    KC_UNDS,    _______,    XXXXXXX

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LSFT_T(L10), LCTL_T(L11), LALT_T(L12), LGUI_T(L13),        L14,  \
             R15,  RGUI_T(R16), LALT_T(R17), RCTL_T(R18), RSFT_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
    ),
    [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
    [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
    [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
    [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
    [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
    [LAYER_AUTOMOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_AUTOMOUSE),
    [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

#ifdef POINTING_DEVICE_ENABLE
bool set_scrolling = false;
// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 100.0
#define SCROLL_DIVISOR_V 100.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;
#endif

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
    #ifdef POINTING_DEVICE_COMBINED
      // Hack to fix slave side being a lower sensitivity
      // if (!is_keyboard_master()) {
      //     pointing_device_set_cpi_on_side(is_keyboard_left(), PMW33XX_CPI + 1000);
      // }
        pointing_device_set_cpi_on_side(false, PMW33XX_CPI);
        pointing_device_set_cpi_on_side(true, PMW33XX_CPI);
    #endif
}

#ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        right_report.h = (int8_t)scroll_accumulated_h;
        right_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        right_report.x = 0;
        right_report.y = 0;
    } else {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        left_report.h = (int8_t)scroll_accumulated_h;
        left_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        left_report.x = 0;
        left_report.y = 0;
    }

    // Clear the X and Y values of the mouse report

    return pointing_device_combine_reports(left_report, right_report);
}
#endif

void pointing_device_init_user(void) {
    set_auto_mouse_layer(LAYER_AUTOMOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
