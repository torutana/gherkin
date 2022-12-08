#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN1_N       LT(1, KC_N)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN2_B       LT(2, KC_B)
#define FN3_C       LT(3, KC_C)
#define FN4_V       LT(4, KC_V)
#define FN5_B       LT(5, KC_B)
#define FN5_N       LT(5, KC_N)
#define FN5_M       LT(5, KC_M)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define ALT_M       ALGR_T(KC_M)
#define ALT_COMM    ALGR_T(KC_COMM)
#define ALT_SPC     ALGR_T(KC_SPC)
#define CTL_M       RCTL_T(KC_M)
#define CTL_ESC     RCTL_T(KC_ESC)
#define CTL_DOT     RCTL_T(KC_DOT)
#define SFT_ENT     RSFT_T(KC_ENT)
#define SFT_A       LSFT_T(KC_A)
#define CTL_A       CTL_T(KC_A)
#define SFT_Z       LSFT_T(KC_Z)
#define SFT_X       LSFT_T(KC_X)
#define SFT_TAB     LSFT_T(KC_TAB)

// TapnDance
// ダブルタップしたら別のキーに。
// ※keymaps の前に書く
enum {
      TD_Q_ESC,
};

void dance_q_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_Q);
    } else {
        register_code(KC_ESCAPE);
    }
}

void dance_q_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_Q);
    } else {
        unregister_code(KC_ESCAPE);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_finished, dance_q_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    TD(TD_Q_ESC), KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    CTL_A,        KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC,
    SFT_Z,        ALT_X,   FN3_C,   FN4_V,   FN2_B,   FN1_N,   FN5_M,   ALT_COMM,CTL_DOT, SFT_ENT
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_1,         KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,        KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______,      _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_EXLM,      KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F11,       KC_F12,  _______, _______, _______, _______, _______, _______, KC_GRV,  KC_DEL,
    _______,      _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______ 
  ),

  [3] = LAYOUT_ortho_3x10(
    KC_ESC,       _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    SFT_TAB,      _______, _______, _______, _______, _______, _______, KC_SLSH, KC_SCLN, KC_QUOT,
    _______,      _______, _______, _______, KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [4] = LAYOUT_ortho_3x10(
    KC_ESC,       _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    SFT_TAB,      _______, _______, _______, _______, _______, _______, KC_QUES, KC_COLN, KC_DQUO,
    _______,      _______, _______, _______, KC_SPC,  KC_SPC,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [5] = LAYOUT_ortho_3x10(
    KC_CALC,      KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR,
    _______,      _______, _______, _______, _______, _______, _______, _______, BL_DEC,  BL_INC,
    _______,      _______, _______, _______, RESET,   _______, _______, _______, _______, _______
  )

};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}

// TAPPING_TERM は細かく制御できる。※ホールドにするために押し続ける時間
// ホールドのつもりでも、この時間内に離してしまうとタップになってしまう。
// → 小さくするとホールドにしやすい
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
            return 150;
        case LT(2, KC_B):
            return 100;
        case LT(1, KC_N):
            return 200;
        default:
            return TAPPING_TERM;
    }
}

// permissive_hold をキーごとに指定できる。
// TAPPING_TERM より短に時間内に「ホールド＋タップ」を完遂しても「タップ＋タップ」にならず、あくまでも「ホールド＋タップ」として扱う。
// ただし PERMISSIVE_HOLD は、高速入力時にホールドになりやすい。
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(2, KC_B):
        case LT(1, KC_N):
            return true;
        default:
            return false;
    }
}

// ignore_mod_tap_interrupt 指定時、一部キーのみ無視できる。
// うっかりホールドになって、を防ぐ
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case LT(2, KC_B):
        //case LT(1, KC_N):
        case CTL_T(KC_A):
            return false;
        default:
            return true;
    }
}

// 「タップ」したつもりが「ホールド」になっていて、指を離しても何も入力されない場合を防ぐ
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case CTL_T(KC_A):
        case LT(5, KC_M):
        case LT(1, KC_N):
        case LT(2, KC_B):
            return true;
        default:
            return false;
    }
}