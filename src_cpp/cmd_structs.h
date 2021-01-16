#ifndef CMD_STRUCTS_H
#define CMD_STRUCTS_H

#include <cmd_core.hpp>

namespace CMD
{
	class IdStack : protected std::stack<UInt32>
	{
	public:
		IdStack() : std::stack<UInt32>() { push(1); }
		// -- getters
		inline UInt32 GetFreeId() { UInt32 unFreeId = top(); if (size() == 1) { top()++; } else { pop(); } return unFreeId; }
		// -- setters
		inline void SetFreeId(UInt32 unFreeId) { if (unFreeId != top()) { push(unFreeId); } }
	};
}
namespace CMD
{
	struct CMD_API CWindowInfo
	{
	public:
		String strTitle = "cwindow";
		V4xywh xywhRect = { 0, 0, 1, 1 };
		V2wh whMaxSize = { 1, 1 };
		bool bIsFocused = false;
	public:
		inline Int16 GetWidth() const {
			return static_cast<Int16>(std::abs(
				static_cast<Int16>(xywhRect.Right) - static_cast<Int16>(xywhRect.Left)));
		}
		inline Int16 GetHeight() const {
			return static_cast<Int16>(std::abs(
				static_cast<Int16>(xywhRect.Bottom) - static_cast<Int16>(xywhRect.Top)));
		}
		inline V2xy GetSize() const { return { GetWidth(), GetHeight() }; }
	};
	struct CMD_API ButtonState {
		bool bNext = false, bLast = false;
		bool bPressed = false, bReleased = false, bHeld = false;
	};
	struct CMD_API CEventsInfo
	{
		UInt64 unEvGetCount = 0;
		UInt64 unEvReadCount = 0;
		INPUT_RECORD irEvents[64];

		struct {
			union {
				V2xy xyMove = { 0, 0 };
				struct { UInt16 xMove, yMove; };
			};
			struct {
				ButtonState bState{ 0 };
				union {
					V2xy xyHeld = { 0, 0 };
					struct { UInt16 xHeld, yHeld; };
				};
			struct { double xDelta = 0.0, yDelta = 0.0; } Scroll;
			} Buttons[MSB_COUNT];
		} MouseInfo;
		struct {
			union {
				WChar unicode;
				Char ascii;
			} cTypedChars[KC_COUNT]{ 0 };
			ButtonState bsButtons[KC_COUNT]{ 0 };
		} KeyboardInfo;
	};
}

#endif	// CMD_STRUCTS_H