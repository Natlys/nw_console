#ifndef CMD_STRUCTS_H
#define CMD_STRUCTS_H

#include <cmd_core.hpp>

namespace CMD
{
	struct CMD_API CWindowInfo
	{
	public:
		String strTitle = String("\0", 256);
		V4xywh xywhRect = { 0, 0, 1, 1 };
		V2wh whMaxSize = { 1, 1 };
		bool bIsFocused = false;
	public:
		inline Int16 GetWidth() const { return Abs(xywhRect.Right - xywhRect.Left); }
		inline Int16 GetHeight() const { return Abs(xywhRect.Bottom - xywhRect.Top); }
		inline V2xy GetSize() const { return { GetWidth(), GetHeight() }; }
	};
	struct CMD_API CEventsInfo
	{
		UInt64 unEvGetCount = 0;
		UInt64 unEvReadCount = 0;
		INPUT_RECORD irEvents[64];

		MouseState<CMD_MS_BTN_COUNT> msInfo;
		KeyboardState<CMD_KEY_COUNT> kbInfo;
	};
}

#endif	// CMD_STRUCTS_H