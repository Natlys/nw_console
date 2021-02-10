#ifndef NWC_CORE_HPP
#define NWC_CORE_HPP
/// The main header of configurations and definitions

#if defined NWC_LINK_DYNAMIC
#ifdef NWC_BUILD_DLL
#define NWC_API __declspec(dllexport)
#elif defined NWC_BUILD_EXE
#define NWC_API __declspec(dllimport)
#endif
#else
#define NWC_API
#endif

#include <nwc_pch.hpp>

// ========<key_codes_nwc>========
#define NWC_KEY_NONE					0
#define NWC_KEY_FIRST					32
// printable_keys
#define NWC_KEY_SPACE_32				32
#define NWC_KEY_APOSTROPHE_39			39
#define NWC_KEY_COMMA_44				44
#define NWC_KEY_MINUS_45				45
#define NWC_KEY_PERIOD_46				46
#define NWC_KEY_APOSTROPHE_39			39
#define NWC_KEY_COMMA_44				44
#define NWC_KEY_MINUS_45				45
#define NWC_KEY_PERIOD_46				46
#define NWC_KEY_SLASH_47				47
#define NWC_KEY_0_48					48
#define NWC_KEY_1_49					49
#define NWC_KEY_2_50					50
#define NWC_KEY_3_51					51
#define NWC_KEY_4_52					52
#define NWC_KEY_5_53					53
#define NWC_KEY_6_54					54
#define NWC_KEY_7_55					55
#define NWC_KEY_8_56					56
#define NWC_KEY_9_57					57
#define NWC_KEY_SEMICOLON_59			59
#define NWC_KEY_EQUAL_61				61
// alphabet_upper_case
#define NWC_KEY_A_65					65
#define NWC_KEY_B_66					66
#define NWC_KEY_C_67					67
#define NWC_KEY_D_68					68
#define NWC_KEY_E_69					69
#define NWC_KEY_F_70					70
#define NWC_KEY_G_71					71
#define NWC_KEY_H_72					72
#define NWC_KEY_I_73					73
#define NWC_KEY_J_74					74
#define NWC_KEY_K_75					75
#define NWC_KEY_L_76					76
#define NWC_KEY_M_77					77
#define NWC_KEY_N_78					78
#define NWC_KEY_O_79					79
#define NWC_KEY_P_80					80
#define NWC_KEY_Q_81					81
#define NWC_KEY_R_82					82
#define NWC_KEY_S_83					83
#define NWC_KEY_T_84					84
#define NWC_KEY_U_85					85
#define NWC_KEY_V_86					86
#define NWC_KEY_W_87					87
#define NWC_KEY_X_88					88
#define NWC_KEY_Y_89					89
#define NWC_KEY_Z_90					90
// additional
#define NWC_KEY_LEFT_BRACKET_91			91
#define NWC_KEY_LEFT_BRACKET_91			91
#define NWC_KEY_BACKSLASH_92			92
#define NWC_KEY_RIGHT_BRACKET_93		93
// alphabet_lower_case
#define NWC_KEY_a_97					97
#define NWC_KEY_b_98					98
#define NWC_KEY_c_99					99
#define NWC_KEY_d_100				100
#define NWC_KEY_e_101				101
#define NWC_KEY_f_102				102
#define NWC_KEY_g_103				103
#define NWC_KEY_h_104				104
#define NWC_KEY_i_105				105
#define NWC_KEY_j_106				106
#define NWC_KEY_k_107				107
#define NWC_KEY_l_108				108
#define NWC_KEY_m_109				109
#define NWC_KEY_n_110				110
#define NWC_KEY_o_111				111
#define NWC_KEY_p_112				112
#define NWC_KEY_q_113				113
#define NWC_KEY_r_114				114
#define NWC_KEY_s_115				115
#define NWC_KEY_t_116				116
#define NWC_KEY_u_117				117
#define NWC_KEY_v_118				118
#define NWC_KEY_w_119				119
#define NWC_KEY_x_120				120
#define NWC_KEY_y_121				121
#define NWC_KEY_z_122				122
// functional_keys
#define NWC_KEY_ESCAPE_27			27
#define NWC_KEY_BACKSPACE_8			8
#define NWC_KEY_HTAB_9				9
#define NWC_KEY_ENTER_13			13
#define NWC_KEY_HTAB_11				11
#define NWC_KEY_INS_45				45            
#define NWC_KEY_DEL_46				46
#define NWC_KEY_ENTER_13			13
#define NWC_KEY_HTAB_11				11
#define NWC_KEY_INS_45				45            
#define NWC_KEY_DEL_46				46
#define NWC_KEY_RIGHT_38			39
#define NWC_KEY_LEFT_37				37
#define NWC_KEY_DOWN_40				40
#define NWC_KEY_UP_38				38
#define NWC_KEY_F1					' '
#define NWC_KEY_F2					' '
#define NWC_KEY_F3					' '
#define NWC_KEY_F4					' '
#define NWC_KEY_F5					' '
#define NWC_KEY_F6					' '
#define NWC_KEY_F7					' '
#define NWC_KEY_F8					' '
#define NWC_KEY_F9					' '
#define NWC_KEY_F10					' '
#define NWC_KEY_F11					' '
#define NWC_KEY_F12					' '
#define NWC_KEY_KP_0				' '
#define NWC_KEY_KP_1				' '
#define NWC_KEY_KP_2				' '
#define NWC_KEY_KP_3				' '
#define NWC_KEY_KP_4				' '
#define NWC_KEY_KP_5				' '
#define NWC_KEY_KP_6				' '
#define NWC_KEY_KP_7				' '
#define NWC_KEY_KP_8				' '
#define NWC_KEY_KP_9				' '
#define NWC_KEY_KP_DECIMAL			' '
#define NWC_KEY_KP_DIVIDE			' '
#define NWC_KEY_KP_MULTIPLY			' '
#define NWC_KEY_KP_SUBTRACT			' '
#define NWC_KEY_KP_ADD				' '
#define NWC_KEY_KP_ENTER_13			' '
#define NWC_KEY_KP_EQUAL			' '
#define NWC_KEY_SHIFT_LEFT			16
#define NWC_KEY_SHIFT_RIGHT			16
#define NWC_KEY_CONTROL_LEFT		17
#define NWC_KEY_CONTROL_RIGHT		17
#define NWC_KEY_ALT_LEFT			18
#define NWC_KEY_ALT_RIGHT			18

#define NWC_KEY_LAST				256
#define NWC_KEY_COUNT				NWC_KEY_LAST
// ========</key_codes_nwc>========

// ========<device_codes_nwc>========
#define NWC_MS_BTN_0				0
#define NWC_MS_BTN_1				1
#define NWC_MS_BTN_2				2
#define NWC_MS_BTN_3				3
#define NWC_MS_BTN_4				4
#define NWC_MS_BTN_5				5
#define NWC_MS_BTN_6				6
#define NWC_MS_BTN_7				7
#define NWC_MS_BTN_LAST				NWC_MS_BTN_7
#define NWC_MS_BTN_LEFT				NWC_MS_BTN_0
#define NWC_MS_BTN_RIGHT			NWC_MS_BTN_1
#define NWC_MS_BTN_MIDDLE			NWC_MS_BTN_2
#define NWC_MS_BTN_LAST				NWC_MS_BTN_7
#define NWC_MS_BTN_COUNT			5
// ========</device_codes_nwc>========

// ========<event_types_nwc>========
#define NWC_BUTTON_RELEASE	0
#define NWC_BUTTON_PRESS	1

#define NWC_MS_PRESS_LEFT	0x0001
#define NWC_MS_PRESS_RIGHT	0x0002
#define NWC_MS_PRESS_2		0x0004
#define NWC_MS_PRESS_3		0x0008
#define NWC_MS_PRESS_4		0x0010

#define NWC_MS_PRESS_DOUBLE	0x0002

#define NWC_MS_MOVED		0x0001
#define NWC_MS_WHEELED		0x0004
#define NWC_MS_HWHEELED		0x0008

#define NWC_KEY_EVT			0x0001
#define NWC_MS_EVT			0x0002
#define NWC_WND_SIZE_EVT	0x0004
#define NWC_MENU_EVT		0x0008
#define NWC_FOCUS_EVT		0x0010
// ========</event_types_nwc>========

#define NWC_NO_SELECTION            0x0000
#define NWC_SELECTION_IN_PROGRESS   0x0001   // selection has begun
#define NWC_SELECTION_NOT_EMPTY     0x0002   // non-null select rectangle
#define NWC_MOUSE_SELECTION         0x0004   // selecting with mouse
#define NWC_MOUSE_DOWN              0x0008   // mouse is down

// --<type_alias>--
namespace NWC
{
	using CHistoryInfo = CONSOLE_HISTORY_INFO;
	using CSelectionInfo = CONSOLE_SELECTION_INFO;
	using CFrameBufInfo = CONSOLE_SCREEN_BUFFER_INFOEX;
	using CPixelInfo = CONSOLE_FONT_INFOEX;
	using CCursorInfo = CONSOLE_CURSOR_INFO;
	using CPixel = CHAR_INFO;
	using V2xy = COORD;
	using V2wh = COORD;
	using V4xywh = SMALL_RECT;
}
// --</type_alias>--

namespace NWC
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
		MSB_LEFT = NWC_MS_BTN_LEFT, MSB_RIGHT = NWC_MS_BTN_RIGHT,
		MIDDLE = NWC_MS_BTN_MIDDLE,
		MSB_ADD_1 = NWC_MS_BTN_3, MSB_ADD_2 = NWC_MS_BTN_4,
		MSB_LAST = NWC_MS_BTN_LAST, MSB_COUNT = NWC_MS_BTN_COUNT
	};
	enum KeyCodes : WChar {
		KC_NONE = 0,
		KC_BELL = 7, // "\a" - sound signal
		KC_BACKSPACE = 8, // Step backward - can be used for two symbols in one
		KC_HTAB = 9, KC_VTAB = 11, KC_ENTER = 13, // Hor + Vert tabulation and EndLine
		KC_SHIFT = 16, KC_CTRL = 17, KC_PAUSE = 19, KC_CAPS_LOCK = 20, KC_ESCAPE = 27,
		KC_LEFT = 37, KC_UP = 38, KC_RIGHT = 39, KC_DOWN = 40, KC_INSERT = 45, KC_DEL = 46,
		KC_HOME = 36,
		KC_SPACE = 32, KC_EXCLAIM = 33, KC_HASH = 35,
		KC_K0 = 48, KC_K1 = 49, KC_K2,
		KC_K3, KC_K4, KC_K5, KC_K6, KC_K7, KC_K8, KC_K9 = 57,
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
}

#endif	// NWC_CORE_HPP