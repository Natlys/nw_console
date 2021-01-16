#ifndef CMD_CORE_HPP
#define CMD_CORE_HPP
/// The main header of configurations and definitions

#if defined CMD_LINK_DYNAMIC
#ifdef CMD_BUILD_DLL
#define CMD_API __declspec(dllexport)
#elif defined CMD_BUILD_EXE
#define CMD_API __declspec(dllimport)
#endif
#elif defined CMD_LINK_STATIC
#define CMD_API
#endif

#include <cmd_pch.hpp>
#include <cmd_def.hpp>

namespace CMD
{
	class CMD_API CMD_Window;
}

namespace CMD
{
	/// 0xFF'FF'FF'FF -> 32 bits
	/// counting from left:
	/// 4 bits - red; 4 bits - blue; 4 bits - green; 4 bits - alpha
	enum CPixelTypes : WChar {
		CPT_DITHER = 0x2489,
		CPT_1_4 = 0x2591,
		CPT_2_4 = 0x2592,
		CPT_3_4 = 0x2593,
		CPT_SOLID = 0x2588,
	};
	/// 0b0000'0000 -> 8 bits; 0x00 -> 8 bits
	/// right 4 bits - background -> 16 variations; right digit - back
	/// left 4 bits - foreground -> 16 variations; left digit - char
	enum CColorsDefault : UInt16 {
		CCD_FG_BLACK = 0x00,
		CCD_FG_DARK_BLUE = 0x01,
		CCD_FG_DARK_GREEN = 0x02,
		CCD_FG_DARK_CYAN = 0x03,
		CCD_FG_DARK_RED = 0x04,
		CCD_FG_DARK_MAGENTA = 0x05,
		CCD_FG_DARK_YELLOW = 0x06,
		CCD_FG_GREY = 0x07,
		CCD_FG_DARK_GREY = 0x08,
		CCD_FG_BLUE = 0x09,
		CCD_FG_GREEN = 0x0A,
		CCD_FG_CYAN = 0x0B,
		CCD_FG_RED = 0x0C,
		CCD_FG_MAGENTA = 0x0D,
		CCD_FG_YELLOW = 0x0E,
		CCD_FG_WHITE = 0x0F,
		CCD_BG_BLACK = 0x00,
		CCD_BG_DARK_BLUE = 0x10,
		CCD_BG_DARK_GREEN = 0x20,
		CCD_BG_DARK_CYAN = 0x30,
		CCD_BG_DARK_RED = 0x40,
		CCD_BG_DARK_MAGENTA = 0x50,
		CCD_BG_DARK_YELLOW = 0x60,
		CCD_BG_GREY = 0x70,
		CCD_BG_DARK_GREY = 0x80,
		CCD_BG_BLUE = 0x90,
		CCD_BG_GREEN = 0xA0,
		CCD_BG_CYAN = 0xB0,
		CCD_BG_RED = 0xC0,
		CCD_BG_MAGENTA = 0xD0,
		CCD_BG_YELLOW = 0xE0,
		CCD_BG_WHITE = 0xF0,
	};
	enum CColorsNum : UInt16 {
		CCN_FG_1 = 0x00, CCN_FG_2 = 0x01, CCN_FG_3 = 0x02, CCN_FG_4 = 0x03,
		CCN_FG_5 = 0x04, CCN_FG_6 = 0x05, CCN_FG_7 = 0x06, CCN_FG_8 = 0x07,
		CCN_FG_9 = 0x08, CCN_FG_10 = 0x09, CCN_FG_11 = 0x0A, CCN_FG_12 = 0x0B,
		CCN_FG_13 = 0x0C, CCN_FG_14 = 0x0D, CCN_FG_15 = 0x0E, CCN_FG_16 = 0x0F,

		CCN_BG_1 = 0x00, CCN_BG_2 = 0x10, CCN_BG_3 = 0x20, CCN_BG_4 = 0x30,
		CCN_BG_5 = 0x40, CCN_BG_6 = 0x50, CCN_BG_7 = 0x60, CCN_BG_8 = 0x70,
		CCN_BG_9 = 0x80, CCN_BG_10 = 0x90, CCN_BG_11 = 0xA0, CCN_BG_12 = 0xB0,
		CCN_BG_13 = 0xC0, CN_BG_14 = 0xD0, CCN_BG_15 = 0xE0, CCN_BG_16 = 0xF0,
	};
	enum MouseButtons : UInt16 {
		MSB_LEFT = CMD_MS_BTN_LEFT, MSB_RIGHT = CMD_MS_BTN_RIGHT,
		MIDDLE = CMD_MS_BTN_MIDDLE,
		MSB_ADD_1 = CMD_MS_BTN_3, MSB_ADD_2 = CMD_MS_BTN_4,
		MSB_LAST = CMD_MS_BTN_LAST, MSB_COUNT = CMD_MS_BTN_COUNT
	};
	enum KeyCodes : WChar {
		KC_NONE = 0,
		KC_BELL = 7, // "\a" - sound signal
		KC_BACKSPACE = 8, // Step backward - can be used for two symbols in one
		KC_HTAB = 9, KC_ENTER = 10, KC_VTAB = 11, // Hor + Vert tabulation and EndLine
		KC_SHIFT = 16, KC_CTRL = 17, KC_PAUSE = 19, KC_CAPS_LOCK = 20, KC_ESCAPE = 27,
		KC_LEFT = 37, KC_UP = 38, KC_RIGHT = 39, KC_DOWN = 40, KC_INSERT = 45, KC_DEL = 46,
		KC_HOME = 36,
		KC_SPACE = 32, KC_EXCLAIM = 33, KC_HASH = 35,
		KC_K0 = 48, KC_K1 = 49, KC_K2, KC_K3, KC_K4, KC_K5, KC_K6, KC_K7, KC_K8, KC_K9 = 57,
		KC_COLON = 58, KC_SEMICOLON = 59, KC_LESSER = 60, KC_EQUAL = 61, KC_GREATER = 62,
		KC_A = 65, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P = 80,
		KC_Q = 81, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_Y, KC_Z = 90,
		KC_a = 97, KC_b, KC_c, KC_d, KC_e, KC_f, KC_g, KC_h, KC_i, KC_j, KC_k, KC_l, KC_m, KC_n, KC_o, KC_p = 112,
		KC_q = 113, KC_r, KC_s, KC_t, KC_u, KC_v, KC_w, KC_x, KC_y, KC_z = 122,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
		KC_RECT_DITHER = 177, KC_QUAD = 254,
		KC_PGUP, KC_PGDN,
		KC_RETURN, KC_SCROLL,
		KC_NP_MUL, KC_NP_DIV, KC_NP_ADD, KC_NP_SUB, KC_NP_DECIMAL, KC_PERIOD,
		KC_COUNT = 255
	};
	enum EventCategories : UInt16 {
		EC_FOCUS = CMD_FOCUS_EVT, EC_WINDOW_SIZE = CMD_WND_SIZE_EVT, EC_MENU = CMD_MENU_EVT,
		EC_MOUSE = CMD_MS_EVT, EC_KEYBOARD = CMD_KEY_EVT,
	};
	enum EventTypes : UInt16 {
		ET_MOUSE_MOVED = CMD_MS_MOVED, ET_VSCROLL = CMD_MS_WHEELED, ET_HSCROLL = CMD_MS_HWHEELED,
	};
	enum SoundTypes : UInt16 {
		ST_BEEP = 0, ST_CMD_BELL
	};
}

#define XY_TO_X(x, y, w) (y * w + x)

#endif	// CMD_CORE_HPP