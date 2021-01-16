#ifndef CMD_ENGINE_H
#define CMD_ENGINE_H

#include <cmd_core.hpp>
#include <cmd_structs.h>
#include <cmd_gui.h>

namespace CMD
{
	/// CmdEngine class
	class CMD_API CmdEngine
	{
		using Widgets = HashMap<UInt32, CWidget*>;
	public:
		CmdEngine();
		CmdEngine(const CmdEngine& rCpy) = delete;
		void operator=(const CmdEngine& rCpy) = delete;
	public:
		~CmdEngine();

		// --getters
		static inline CmdEngine& Get()					{ static CmdEngine s_CEngine; return s_CEngine; }
		inline std::thread* GetRunThread()				{ return &m_thrRun; }
		inline const Int16 GetWndWidth()		const	{ return m_cwInfo.GetWidth(); }
		inline const Int16 GetWndHeight()		const	{ return m_cwInfo.GetHeight(); }
		inline const CWindowInfo& GetWndInfo()	const	{ return m_cwInfo; }
		inline const CPixelInfo& GetPxInfo()	const	{ return m_cpxInfo; }
		inline const CFrameBufInfo& GetFBInfo()	const	{ return m_cfbInfo; }
		inline const CEventsInfo& GetEvInfo()	const	{ return m_cevInfo; }
		inline const DArray<CPixel>& GetPxBuf()	const	{ return m_cpxBuf; }
		
		inline UInt16 GetMouseMoveX()				{ return m_cevInfo.MouseInfo.xMove; }
		inline UInt16 GetMouseMoveY()				{ return m_cevInfo.MouseInfo.yMove; }
		inline V2xy GetMouseMoveXY()				{ return m_cevInfo.MouseInfo.xyMove; }
		inline UInt16 GetMouseHeldX(UInt16 msCode)	{ return m_cevInfo.MouseInfo.Buttons[msCode].xHeld; }
		inline UInt16 GetMouseHeldY(UInt16 msCode)	{ return m_cevInfo.MouseInfo.Buttons[msCode].yHeld; }
		inline V2xy GetMouseHeldXY(UInt16 msCode)	{ return m_cevInfo.MouseInfo.Buttons[msCode].xyHeld; }

		inline bool GetMousePressed(MouseButtons msCode) const { return m_cevInfo.MouseInfo.Buttons[msCode].bState.bPressed; }
		inline bool GetMouseReleased(MouseButtons msCode) const { return m_cevInfo.MouseInfo.Buttons[msCode].bState.bReleased; }
		inline bool GetMouseHeld(MouseButtons msCode) const { return m_cevInfo.MouseInfo.Buttons[msCode].bState.bHeld; }
		inline bool GetKeyPressed(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bPressed; }
		inline bool GetKeyReleased(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bReleased; }
		inline bool GetKeyHeld(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bHeld; }
		
		inline void* GetCout() { return m_pCout; }
		inline void* GetCIn() { return m_pCin; }
		// --setters
		void SetTitle(const char* strTitle);
		void SetWndInfo(const CWindowInfo& rcwInfo);
		void SetWndSize(UInt16 nWidth, UInt16 nHeight);
		void SetPxInfo(const CPixelInfo& rcpxInfo);
		void SetPxSize(UInt16 nWidth, UInt16 nHeight);
		void SetFBInfo(const CFrameBufInfo& rfbInfo);
		bool ResetWindow();
		inline void SetClearPattern(CPixelTypes cpxPattern) { m_cpxClear.Char.UnicodeChar = cpxPattern; }
		inline void SetClearColor(UInt16 cColor) { m_cpxClear.Attributes = cColor; }
		inline void ClearPxBuf() { for (Size pxi = 0; pxi < m_cpxBuf.size(); pxi++) { m_cpxBuf[pxi] = m_cpxClear; } }
		// --predicates
		inline bool IsRunning() const { return m_bIsRunning; }

		// --core_methods
		bool Init();
		void Run();
		void Quit();
		// --drawing_methods
		inline void DrawPixelX(Size xCrd, UInt16 cColor);
		inline void DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor);
		inline void DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor);
		inline void DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor);
		inline void DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor);
		inline void DrawStrXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, const char* str);
		inline void DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor);
		// --other_methods
		void MakeSound(SoundTypes sType = ST_BEEP);
		void ChangeSoundFreq(Int32 unFreq);
		void ChangeSoundDur(Int32 unDur);
	private:
		inline void Update();
		inline void OnEvent();
	private:
		bool m_bIsRunning;
		std::thread m_thrRun;

		void *m_pCout, *m_pCin;
		void *m_pCoutOrig, *m_pCinOrig;
		
		CWindowInfo m_cwInfo;
		CPixelInfo m_cpxInfo;
		CFrameBufInfo m_cfbInfo;
		CEventsInfo m_cevInfo;

		DArray<CPixel> m_cpxBuf;
		CPixel m_cpxClear;
		CPixel m_cpxDraw;

		std::chrono::steady_clock::time_point m_tpCurrTime;
		std::chrono::steady_clock::time_point m_tpLastTime;
		double m_nDeltaTime;

		UInt32 m_unSoundFreq;
		UInt32 m_unSoundDur;
	};
	inline void CmdEngine::DrawPixelX(Size xCrd, UInt16 cColor) {
		if (xCrd + 1 >= m_cpxBuf.size()) { return; }
		UInt16 unWidth = GetWndWidth();
		UInt64 unWritten = 0;
		FillConsoleOutputAttribute(m_pCout, cColor, 2,
			{ static_cast<Int16>(xCrd % unWidth), static_cast<Int16>(xCrd / unWidth) }, &unWritten);
		FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2,
			{ static_cast<Int16>(xCrd % unWidth), static_cast<Int16>(xCrd / unWidth) }, &unWritten);
	}
	inline void CmdEngine::DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor) {
		UInt16 unWidth = GetWndWidth();
		UInt16 unHeight = GetWndHeight();
		if (xCrd >= unWidth || yCrd > unHeight) { return; }
		UInt64 unWritten = 0;
		FillConsoleOutputAttribute(m_pCout, cColor, 2,
			{ static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
		FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2,
			{ static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
	}
	inline void CmdEngine::DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor) {
		UInt16 unWidth = GetWndWidth();
		UInt16 unHeight = GetWndHeight();
		if (xCrd0 < 0 || xCrd0 >= unWidth || xCrd1 < 0 || xCrd1 >= unWidth) { return; }
		UInt64 unWritten = 0;
		for (UInt16 ix = xCrd0; ix <= xCrd1; ix++) {
			for (UInt16 iy = 0; iy <= unHeight; iy++) {
				FillConsoleOutputAttribute(m_pCout, cColor, 2,
					{ static_cast<Int16>(ix), static_cast<Int16>(iy) }, &unWritten);
				FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2,
					{ static_cast<Int16>(ix), static_cast<Int16>(iy) }, &unWritten);
			}
		}
	}
	inline void CmdEngine::DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor) {
		UInt16 unWidth = GetWndWidth();
		UInt16 unHeight = GetWndHeight();
		if (yCrd0 < 0 || yCrd0 >= unHeight || yCrd1 < 0 || yCrd1 >= unHeight) { return; }
		UInt64 unWritten = 0;
		for (UInt16 iy = yCrd0; iy <= yCrd1; iy++) {
			FillConsoleOutputAttribute(m_pCout, cColor, unWidth,
				{ static_cast<Int16>(0), static_cast<Int16>(iy) }, &unWritten);
			FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, unWidth,
				{ static_cast<Int16>(0), static_cast<Int16>(iy) }, &unWritten);
		}
	}
	inline void CmdEngine::DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor) {
		Int16 nDeltaX = xCrd1 - xCrd0;
		Int16 nDeltaY = yCrd1 - yCrd0;
		Int16 nDirX = nDeltaX < 0 ? -1 : 1;
		Int16 nDirY = nDeltaY < 0 ? -1 : 1;
		Int16 nErr = 0;
		Int16 nDeltaErr = nDeltaY;
		for (Int16 nX = xCrd0, nY = yCrd0; nX != xCrd1; nX += nDirX) {
			DrawPixelXY(nX, nY, cColor);
			nErr += nDeltaErr;
			if (nErr > nDeltaX) {
				nY += nDirY;
				nErr -= (nDeltaX);
			}
		}
	}
	inline void CmdEngine::DrawStrXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, const char* str) {
		UInt16 unWidth = GetWndWidth();
		UInt16 unHeight = GetWndHeight();
		UInt16 unLen = static_cast<UInt16>(strlen(str));
		UInt16 unStrEndX = xCrd + unLen;
		if (xCrd > unWidth || yCrd > unHeight) { return; }
		UInt64 unWritten = 0;
		for (UInt16 ci = 0; ci < unLen; ci++, xCrd++) {
			if (xCrd > unWidth) { xCrd = 0; yCrd++; }
			FillConsoleOutputAttribute(m_pCout, cColor, 1,
				{ static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
			FillConsoleOutputCharacterW(m_pCout, str[ci], 1,
				{ static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
		}
	}
	inline void CmdEngine::DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor) {
		UInt16 unWidth = GetWndWidth();
		UInt16 unHeight = GetWndHeight();
		if (nLt > nRt) { nLt = nLt - nRt; nRt = nRt + nLt; nLt = nRt - nLt; }
		if (nTp > nBt) { nTp = nTp - nBt; nBt = nBt + nTp; nTp = nBt - nTp; }
		if (nLt > unWidth) { nLt = unWidth; }
		if (nRt > unWidth) { nRt = unWidth; }
		if (nTp > unHeight) { nTp = unHeight; }
		if (nBt > unHeight) { nBt = unHeight; }
		UInt64 unWritten = 0;
		UInt16 unLen = nRt - nLt + 1;
		for (UInt16 nY = nTp; nY <= nBt; nY++) {
			FillConsoleOutputAttribute(m_pCout, cColor, unLen,
				{ static_cast<Int16>(nLt), static_cast<Int16>(nY) }, &unWritten);
			FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, unLen,
				{ static_cast<Int16>(nLt), static_cast<Int16>(nY) }, &unWritten);
		}
	}
}

#endif	// CMD_ENGINE_H