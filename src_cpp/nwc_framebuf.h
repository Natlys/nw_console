#ifndef NWC_FRAME_BUFFER_H
#define NWC_FRAME_BUFFER_H

#include <nwc_core.hpp>

namespace NWC
{
	/// CFrameBuf class
	class NWC_API CFrameBuf {
	public:
		CFrameBuf();
		~CFrameBuf();

		// --getters
		inline Int16 GetWidth() const { return static_cast<Int16>(m_Info.dwSize.X); }
		inline Int16 GetHeight() const { return static_cast<Int16>(m_Info.dwSize.Y); }
		inline CPixel* GetPxData() { return m_pPxData; }
		inline Size GetPxCount() { return m_unPxCount; }
		inline Ptr GetNative() { return m_pCout; }
		inline CFrameBufInfo& GetInfo() { return m_Info; }
		// --setters
		inline void SetSizeWH(UInt16 unWidth, UInt16 unHeight) { m_Info.dwSize = { static_cast<Int16>(unWidth), static_cast<Int16>(unHeight) }; }
		inline void SetClearPattern(CPixelTypes cpxPattern) { m_cpxClear.Char.UnicodeChar = cpxPattern; }
		inline void SetClearColor(UInt16 cColor) { m_cpxClear.Attributes = cColor; }
		// --core_methods
		void Remake();
		inline void Clear() { for (Size pxi = 0; pxi < m_unPxCount; pxi++) { m_pPxData[pxi] = m_cpxClear; } }
		inline void DrawPixelX(Size nX, CPixel pxDraw);
		inline void DrawPixelXY(Int16 nX, Int16 nY, CPixel pxDraw);
		inline void DrawPixelX(Size nX, UInt16 cColor, CPixelTypes pxType = CPT_SOLID);
		inline void DrawPixelXY(Int16 nX, Int16 nY, UInt16 cColor, CPixelTypes pxType = CPT_SOLID);
		inline void DrawByteXY(Int16 nX, Int16 nY, UInt16 cColor, Byte bt);
		inline void DrawBytesXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, UInt16 cColor, Byte* str, Size szLen = 1);
	private:
		Ptr m_pCout;
		UInt64 m_unPxCount;
		CPixel* m_pPxData;
		CPixel m_cpxClear;
		CFrameBufInfo m_Info;
	};
	// --==<drawing_methods>==--
	inline void CFrameBuf::DrawPixelX(Size nX, CPixel pxDraw) {
		if (nX + 1 >= m_unPxCount) { return; }
		UInt16 unWidth = GetWidth();
		m_pPxData[nX++] = pxDraw;
		if ((nX % unWidth) == 0) { return; }
		m_pPxData[nX] = pxDraw;
	}
	inline void CFrameBuf::DrawPixelXY(Int16 nX, Int16 nY, CPixel pxDraw) {
		if (nX < 0 || nY < 0) { return; }
		UInt16 unWidth = GetWidth();
		if (nX > unWidth) { return; }
		DrawPixelX(NWL_XY_TO_X(nX, nY, unWidth), pxDraw);
	}
	inline void CFrameBuf::DrawPixelX(Size nX, UInt16 cColor, CPixelTypes pxType) {
		if (nX + 1 >= m_unPxCount) { return; }
		UInt16 unWidth = GetWidth();
		CPixel cpx;
		cpx.Attributes = cColor;
		cpx.Char.UnicodeChar = pxType;
		m_pPxData[nX++] = cpx;
		if ((nX % unWidth) == 0) { return; }
		m_pPxData[nX] = cpx;
	}
	inline void CFrameBuf::DrawPixelXY(Int16 nX, Int16 nY, UInt16 cColor, CPixelTypes pxType) {
		if (nX < 0) { return; }
		UInt16 unWidth = GetWidth();
		if (nX > unWidth) { return; }
		DrawPixelX(NWL_XY_TO_X(nX, nY, unWidth), cColor);
	}
	inline void CFrameBuf::DrawByteXY(Int16 nX, Int16 nY, UInt16 cColor, Byte bt)
	{
		if (nX < 0 || nY < 0) { return; }
		UInt16 unWidth = GetWidth();
		if (nX > unWidth) { return; }
		Size szCrd = NWL_XY_TO_X(nX, nY, unWidth);
		if (szCrd >= m_unPxCount) { return; }
		m_pPxData[szCrd].Attributes = cColor;
		m_pPxData[szCrd].Char.UnicodeChar = static_cast<WChar>(bt);
	}
	inline void CFrameBuf::DrawBytesXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, UInt16 cColor, Byte* str, Size szLen) {
		if (nX0 > nX1) { nX0 = nX0 - nX1; nX1 = nX0 + nX1; nX1 = nX0 - nX1; }
		if (nY0 > nY1) { nY0 = nY0 - nY1; nY1 = nY0 + nY1; nY1 = nY0 - nY1; }
		for (Int32 ci = 0, ix = nX0; ci < szLen && nY0 != nY1; ci++, ix++) {
			if (ix > nX1 || str[ci] == '\n') { ix = 0; nY0 += 1; }
			else { DrawByteXY(ix, nY0, cColor, str[ci]); }
		}
	}
	// --==</drawing_methods>==--
}
#endif	// NWC_FRAME_BUFFER_H