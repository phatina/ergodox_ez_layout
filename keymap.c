#include <action_layer.h>
#include <debug.h>
#include <ergodox_ez.h>
#include <version.h>

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  VIM_WRITE,
  VIM_QUIT,
  VIM_FUZZY_OPEN,
  VIM_FUZZY_BUFFER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ergodox(
        /* left hand */
        KC_ESCAPE, KC_1,KC_2,KC_3,KC_4,KC_5,KC_LEFT,      // 7
        KC_TAB,    KC_Q,KC_W,KC_E,KC_R,KC_T,KC_MINUS,        // 7
        KC_LCTL,   KC_A,KC_S,KC_D,KC_F,KC_G,                // 6
        KC_LSHIFT, KC_Z,KC_X,KC_C,KC_V,KC_B,KC_LBRACKET,  // 7
        KC_LCTL,   KC_QUOTE,KC_TRANSPARENT,KC_LGUI,KC_LALT, // 5

        KC_TRANSPARENT,KC_INSERT,                        // 2
        KC_HOME,                                         // 1
        KC_SPACE,KC_BSPACE,KC_END,                       // 3

        /* right hand */
        KC_RIGHT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,
        KC_EQUAL,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,
        KC_RBRACKET,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_LSHIFT,
        KC_GRAVE,KC_QUOTE,KC_LBRACKET,KC_RBRACKET,MO(1),

        KC_PSCREEN,KC_TRANSPARENT,
        KC_PGUP,
        KC_PGDOWN,KC_DELETE,LT(1,KC_ENTER)),

  [1] = LAYOUT_ergodox(
        /* left hand */
        KC_GRAVE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,
        KC_TRANSPARENT,VIM_QUIT,VIM_WRITE,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
        KC_CAPSLOCK,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,
        KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,VIM_FUZZY_BUFFER,KC_LCBR,
        KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,LALT(KC_SPACE),KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,

        /* right hand */
        KC_PSCREEN,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,
        KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,VIM_FUZZY_OPEN,KC_TRANSPARENT,KC_F12,
        KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,
        KC_RCBR,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
        KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,

        KC_TRANSPARENT,KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed)
      return true;

  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      eeconfig_init();
      return false;
    case VRSN:
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      return false;
    case RGB_SLD:
      rgblight_mode(1);
      return false;

    /* VIM */
    case VIM_WRITE:
      SEND_STRING(SS_TAP(X_ESCAPE) ":w" SS_TAP(X_ENTER));
      return false;
    case VIM_QUIT:
      SEND_STRING(SS_TAP(X_ESCAPE) ":q" SS_TAP(X_ENTER));
      return false;

    /* VIM -- Fuzzy Finder */
    case VIM_FUZZY_OPEN:
      SEND_STRING(SS_TAP(X_ESCAPE) "\\o");
      return false;
    case VIM_FUZZY_BUFFER:
      SEND_STRING(SS_TAP(X_ESCAPE) "\\b");
      return false;
  }

  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }
    return state;

};
