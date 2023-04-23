/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T    ,                                      KC_Y     , KC_U     , KC_I     , KC_O    , KC_P    , KC_MINS ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G    ,                                      KC_H     , KC_J     , KC_K     , KC_L    , KC_SCLN , KC_QUOT ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B    ,                                      KC_N     , KC_M     , KC_COMM  , KC_DOT  , KC_SLSH , KC_BSLS ,
                  KC_LCTL  ,KC_LGUI  , KC_LALT  ,   LT(1,KC_SPC) ,LT(3,KC_LNG1),                   KC_BSPC ,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , MO(3)
  ),

  [1] = LAYOUT_universal(
    KC_GRV   , S(KC_1)  , S(KC_2) , S(KC_3)  , S(KC_4)  , S(KC_5]  ,                                     S(KC_6) , S(KC_7)  , S(KC_8) , S(KC_9)  , S(KC_0)  , KC_MINS  ,
    _______  , _______  , KC_UP   , _______  , KC_LBRC  , KC_RBRC  ,                                      KC_Q   , KC_LGUI  , KC_CAPS , G(KC_L)  , G(KC_H)  , _______  ,
    _______  , KC_LEFT  , KC_DOWN , KC_RIGHT , _______  , KC_EQL   ,                                    _______  , SGUI(4)  ,G(KC_TAB), _______  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                    KC_DEL  , KC_LANG2  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5   ,                                    KC_PSLS  , KC_7     , KC_8     , KC_9     , KC_0    , KC_PMNS  ,
    _______  , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10  ,                                    KC_PAST  , KC_4     , KC_5     , KC_6     , KC_EQL  , KC_BSPC  ,
    _______  , KC_F11   , KC_F12   , _______  , _______  , _______  ,                                   KC_0     , KC_1     , KC_2     , KC_3     , KC_PDOT , KC_ENT   ,
                  _______  , _______  , _______  ,         _______  , _______  ,                   _______   , _______  , _______       , _______  , ________
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , _______  ,                                  _______  , _______  , _______  , _______  , _______  , KBC_SAVE ,
    RGB_HUI  , RGB_SAI  , RGB_VAI  ,KC_BRIGHTNESS_UP, _______  , KC_VOLU ,                              KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2 , _______  , SCRL_DVI ,
    RGB_HUD  , RGB_SAD  , RGB_VAD  ,KC_BRIGHTNESS_DOWN,_______ , KC_VOLD ,                              KC_BTN5  , KC_LEFT  , KC_DOWN  , KC_UP   , KC_RGHT  , SCRL_DVD ,
                  _______  , KC_MUTE  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
  
   [4] = LAYOUT_universal(
    _______  ,  _______  , _______  , _______  , _______  , _______  ,                             _______  , _______  , _______    , _______    , _______  , _______  ,
    _______  ,  _______  , KC_BTN2  , KC_BTN3  , KC_BTN1  , CPI_I100  ,                                KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  , CPI_I1K  ,
    _______  ,  _______  , _______  , _______  , _______  , CPI_D100  ,                                KC_BTN5  , _______  , _______  , _______  , _______  , CPI_D1K  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) { 
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
