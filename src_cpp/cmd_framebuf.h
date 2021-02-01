#ifndef CMD_FRAME_BUFFER_H
#define CMD_FRAME_BUFFER_H

#include <cmd_core.hpp>
#include <cmd_structs.h>

namespace CMD
{
	/// CFrameBuf class
	class CMD_API CFrameBuf {
	public:
		CFrameBuf();
		~CFrameBuf();

		// --getters
		inline Int16 GetWidth() const { return static_cast<Int16>(m_Info.dwSize.X); }
		inline Int16 GetHeight() const { return static_cast<Int16>(m_Info.dwSize.Y); }
		inline CPixel* GetPxData() { return m_pPxData; }
		inline Size GetPxCount() { return m_szPxCount; }
		inline Ptr GetNative() { return m_pCout; }
		inline CFrameBufInfo& GetInfo() { return m_Info; }
		// --setters
		inline void SetSizeWH(UInt16 unWidth, UInt16 unHeight) { m_Info.dwSize = { static_cast<Int16>(unWidth), static_cast<Int16>(unHeight) }; }
		inline void SetClearPattern(CPixelTypes cpxPattern) { m_cpxClear.Char.UnicodeChar = cpxPattern; }
		inline void SetClearColor(UInt16 cColor) { m_cpxClear.Attributes = cColor; }
		// --core_methods
		void Remake();
		inline void Clear() { for (Size pxi = 0; pxi < m_szPxCount; pxi++) { m_pPxData[pxi] = m_cpxClear; } }
		inline void DrawPixelX(Size xCrd, CPixel pxDraw);
		inline void DrawPixelXY(UInt16 xCrd, UInt16 yCrd, CPixel pxDraw);
		inline void DrawPixelX(Size xCrd, UInt16 cColor, CPixelTypes pxType = CPT_SOLID);
		inline void DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, CPixelTypes pxType = CPT_SOLID);
		inline void DrawByteXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte bt);
		inline void DrawBytesXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte* str, UInt32 unLen = 1);
	private:
		Ptr m_pCout;
		Size m_szPxCount;
		CPixel* m_pPxData;
		CPixel m_cpxClear;
		CFrameBufInfo m_Info;
	};
	// --==<drawing_methods>==--
	inline void CFrameBuf::DrawPixelX(Size xCrd, CPixel pxDraw) {
		if (xCrd + 1 >= m_szPxCount) { return; }
		UInt16 unWidth = GetWidth();
		m_pPxData[xCrd++] = pxDraw;
		if ((xCrd % unWidth) == 0) { return; }
		m_pPxData[xCrd] = pxDraw;
	}
	inline void CFrameBuf::DrawPixelXY(UInt16 xCrd, UInt16 yCrd, CPixel pxDraw) {
		UInt16 unWidth = GetWidth();
		if (xCrd > unWidth) { xCrd -= (unWidth + 1); }
		DrawPixelX(NWL_XY_TO_X(xCrd, yCrd, unWidth), pxDraw);
	}
	inline void CFrameBuf::DrawPixelX(Size xCrd, UInt16 cColor, CPixelTypes pxType) {
		if (xCrd + 1 >= m_szPxCount) { return; }
		UInt16 unWidth = GetWidth();
		CPixel cpx;
		cpx.Attributes = cColor;
		cpx.Char.UnicodeChar = pxType;
		m_pPxData[xCrd++] = cpx;
		if ((xCrd % unWidth) == 0) { return; }
		m_pPxData[xCrd] = cpx;
	}
	inline void CFrameBuf::DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, CPixelTypes pxType) {
		UInt16 unWidth = GetWidth();
		if (xCrd > unWidth) { xCrd -= (unWidth + 1); }
		DrawPixelX(NWL_XY_TO_X(xCrd, yCrd, unWidth), cColor);
	}
	inline void CFrameBuf::DrawByteXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte bt)
	{
		UInt16 unWidth = GetWidth();
		if (xCrd > unWidth) { xCrd -= unWidth; yCrd++; }
		Size szCrd = NWL_XY_TO_X(xCrd, yCrd, unWidth);
		if (szCrd >= m_szPxCount) { return; }
		m_pPxData[szCrd].Attributes = cColor;
		m_pPxData[szCrd].Char.UnicodeChar = static_cast<WChar>(bt);
	}
	inline void CFrameBuf::DrawBytesXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte* str, UInt32 unLen) {
		for (UInt32 ci = 0; ci < unLen; ci++) { DrawByteXY(xCrd + ci, yCrd, cColor, str[ci]); }
	}
	// --==</drawing_methods>==--
}
#endif	// CMD_FRAME_BUFFER_H