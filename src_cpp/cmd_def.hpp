#ifndef CMD_DEF_HPP
#define CMD_DEF_HPP

// --<type_alias>--
namespace CMD
{
	// --number
	using Int8 = __int8;
	using Int16 = __int16;
	using Int32 = __int32;
	using Int64 = __int64;
	using UInt8 = unsigned __int8;
	using UInt16 = unsigned short;
	using UInt32 = unsigned int;
	using UInt64 = unsigned long int;
	using Float32 = float;
	using Float64 = double;
	using Float128 = long double;
	// --string
	using Char8 = char;
	using Char16 = wchar_t;
	using Char = char;
	using WChar = wchar_t;
	using UChar = unsigned char;

	using CString = const char*;
	using String = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
	using WString = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
	// --memory
	using Byte = char;
	using UByte = unsigned char;
	using Size = size_t;
	// --containers
	template <typename ValType, Size SzSpace> using SArray = std::array<ValType, SzSpace>;
	template <typename ValType> using DArray = std::vector<ValType>;
	template <typename KeyType, typename ValType> using HashMap = std::unordered_map<KeyType, ValType>;
	template <typename KeyType, typename ValType> using DStack = std::stack<KeyType, ValType>;
#if (defined CMD_PLATFORM_WINDOWS)
	using CHistoryInfo = CONSOLE_HISTORY_INFO;
	using CSelectionInfo = CONSOLE_SELECTION_INFO;
	using CFrameBufInfo = CONSOLE_SCREEN_BUFFER_INFOEX;
	using CPixelInfo = CONSOLE_FONT_INFOEX;
	using CPixel = CHAR_INFO;
	using V2xy = COORD;
	using V2wh = COORD;
	using V4xywh = SMALL_RECT;
#endif	// CMD_PLATFORM
}
// --</type_alias>--

// ========<key_codes_cmd>========
#define CMD_KEY_NONE					0
// printable_keys
#define CMD_KEY_SPACE_32				32
#define CMD_KEY_APOSTROPHE_39		39
#define CMD_KEY_COMMA_44				44
#define CMD_KEY_MINUS_45				45
#define CMD_KEY_PERIOD_46			46
#define CMD_KEY_SLASH_47				47
#define CMD_KEY_0_48					48
#define CMD_KEY_1_49					49
#define CMD_KEY_2_50					50
#define CMD_KEY_3_51					51
#define CMD_KEY_4_52					52
#define CMD_KEY_5_53					53
#define CMD_KEY_6_54					54
#define CMD_KEY_7_55					55
#define CMD_KEY_8_56					56
#define CMD_KEY_9_57					57
#define CMD_KEY_SEMICOLON_59			59
#define CMD_KEY_EQUAL_61				61
// alphabet_upper_case
#define CMD_KEY_A_65					65
#define CMD_KEY_B_66					66
#define CMD_KEY_C_67					67
#define CMD_KEY_D_68					68
#define CMD_KEY_E_69					69
#define CMD_KEY_F_70					70
#define CMD_KEY_G_71					71
#define CMD_KEY_H_72					72
#define CMD_KEY_I_73					73
#define CMD_KEY_J_74					74
#define CMD_KEY_K_75					75
#define CMD_KEY_L_76					76
#define CMD_KEY_M_77					77
#define CMD_KEY_N_78					78
#define CMD_KEY_O_79					79
#define CMD_KEY_P_80					80
#define CMD_KEY_Q_81					81
#define CMD_KEY_R_82					82
#define CMD_KEY_S_83					83
#define CMD_KEY_T_84					84
#define CMD_KEY_U_85					85
#define CMD_KEY_V_86					86
#define CMD_KEY_W_87					87
#define CMD_KEY_X_88					88
#define CMD_KEY_Y_89					89
#define CMD_KEY_Z_90					90
// additional
#define CMD_KEY_LEFT_BRACKET_91		91
#define CMD_KEY_BACKSLASH_92			92
#define CMD_KEY_RIGHT_BRACKET_93		93
// alphabet_lower_case
#define CMD_KEY_a_97					97
#define CMD_KEY_b_98					98
#define CMD_KEY_c_99					99
#define CMD_KEY_d_100				100
#define CMD_KEY_e_101				101
#define CMD_KEY_f_102				102
#define CMD_KEY_g_103				103
#define CMD_KEY_h_104				104
#define CMD_KEY_i_105				105
#define CMD_KEY_j_106				106
#define CMD_KEY_k_107				107
#define CMD_KEY_l_108				108
#define CMD_KEY_m_109				109
#define CMD_KEY_n_110				110
#define CMD_KEY_o_111				111
#define CMD_KEY_p_112				112
#define CMD_KEY_q_113				113
#define CMD_KEY_r_114				114
#define CMD_KEY_s_115				115
#define CMD_KEY_t_116				116
#define CMD_KEY_u_117				117
#define CMD_KEY_v_118				118
#define CMD_KEY_w_119				119
#define CMD_KEY_x_120				120
#define CMD_KEY_y_121				121
#define CMD_KEY_z_122				122
// functional_keys
#define CMD_KEY_ESCAPE_27			27
#define CMD_KEY_BACKSPACE_8			8
#define CMD_KEY_HTAB_9				9
#define CMD_KEY_ENTER_13				13
#define CMD_KEY_HTAB_11				11
#define CMD_KEY_INS_45				45            
#define CMD_KEY_DEL_46				46
#define CMD_KEY_RIGHT_38				39
#define CMD_KEY_LEFT_37				37
#define CMD_KEY_DOWN_40				40
#define CMD_KEY_UP_38				38
#define CMD_KEY_F1					' '
#define CMD_KEY_F2					' '
#define CMD_KEY_F3					' '
#define CMD_KEY_F4					' '
#define CMD_KEY_F5					' '
#define CMD_KEY_F6					' '
#define CMD_KEY_F7					' '
#define CMD_KEY_F8					' '
#define CMD_KEY_F9					' '
#define CMD_KEY_F10					' '
#define CMD_KEY_F11					' '
#define CMD_KEY_F12					' '
#define CMD_KEY_KP_0					' '
#define CMD_KEY_KP_1					' '
#define CMD_KEY_KP_2					' '
#define CMD_KEY_KP_3					' '
#define CMD_KEY_KP_4					' '
#define CMD_KEY_KP_5					' '
#define CMD_KEY_KP_6					' '
#define CMD_KEY_KP_7					' '
#define CMD_KEY_KP_8					' '
#define CMD_KEY_KP_9					' '
#define CMD_KEY_KP_DECIMAL			' '
#define CMD_KEY_KP_DIVIDE			' '
#define CMD_KEY_KP_MULTIPLY			' '
#define CMD_KEY_KP_SUBTRACT			' '
#define CMD_KEY_KP_ADD				' '
#define CMD_KEY_KP_ENTER_13			' '
#define CMD_KEY_KP_EQUAL				' '
#define CMD_KEY_SHIFT_LEFT			16
#define CMD_KEY_SHIFT_RIGHT			16
#define CMD_KEY_CONTROL_LEFT			17
#define CMD_KEY_CONTROL_RIGHT		17
#define CMD_KEY_ALT_LEFT				18
#define CMD_KEY_ALT_RIGHT			18

#define CMD_KEY_LAST					256
// ========</key_codes_cmd>========

// ========<device_codes_cmd>========
#define CMD_MS_BTN_0				0
#define CMD_MS_BTN_1				1
#define CMD_MS_BTN_2				2
#define CMD_MS_BTN_3				3
#define CMD_MS_BTN_4				4
#define CMD_MS_BTN_5				5
#define CMD_MS_BTN_6				6
#define CMD_MS_BTN_7				7
#define CMD_MS_BTN_LAST			CMD_MS_BTN_7
#define CMD_MS_BTN_LEFT			CMD_MS_BTN_0
#define CMD_MS_BTN_RIGHT			CMD_MS_BTN_1
#define CMD_MS_BTN_MIDDLE		CMD_MS_BTN_2
#define CMD_MS_BTN_COUNT			5
// ========</device_codes_cmd>========

// ========<event_types_cmd>========
#define CMD_RELEASE				0
#define CMD_PRESS				1

#define CMD_MS_PRESS_LEFT		0x0001
#define CMD_MS_PRESS_RIGHT		0x0002
#define CMD_MS_PRESS_2			0x0004
#define CMD_MS_PRESS_3			0x0008
#define CMD_MS_PRESS_4			0x0010

#define CMD_MS_PRESS_DOUBLE		0x0002

#define CMD_MS_MOVED				0x0001
#define CMD_MS_WHEELED			0x0004
#define CMD_MS_HWHEELED			0x0008

#define CMD_KEY_EVT				0x0001
#define CMD_MS_EVT				0x0002
#define CMD_WND_SIZE_EVT			0x0004
#define CMD_MENU_EVT				0x0008
#define CMD_FOCUS_EVT			0x0010
// ========</event_types_cmd>========

#define CONSOLE_NO_SELECTION            0x0000
#define CONSOLE_SELECTION_IN_PROGRESS   0x0001   // selection has begun
#define CONSOLE_SELECTION_NOT_EMPTY     0x0002   // non-null select rectangle
#define CONSOLE_MOUSE_SELECTION         0x0004   // selecting with mouse
#define CONSOLE_MOUSE_DOWN              0x0008   // mouse is down

#endif	// CMD_DEF_HPP