#ifndef CMD_ENGINE_H
#define CMD_ENGINE_H

#include <nwlib/nwl_engine.h>

#include <cmd_core.hpp>
#include <cmd_structs.h>
#include <cmd_framebuf.h>

namespace CMD
{
	/// CEngine class
	class CMD_API CEngine : public AEngine<CEngine>
	{
	public:
		CEngine();
		~CEngine();

		// --getters
		inline CFrameBuf* GetFrameBuf()				{ return &m_fb; }
		
		inline const CWindowInfo& GetWndInfo()	const	{ return m_wInfo; }
		inline const CPixelInfo& GetPxInfo()	const	{ return m_pxInfo; }
		inline const CEventsInfo& GetEvInfo()	const	{ return m_evInfo; }

		inline const Int16 GetWndWidth()		const	{ return m_wInfo.GetWidth(); }
		inline const Int16 GetWndHeight()		const	{ return m_wInfo.GetHeight(); }

		inline UInt16 GetMouseMoveX()				const	{ return static_cast<UInt16>(m_evInfo.msInfo.xMove); }
		inline UInt16 GetMouseMoveY()				const	{ return static_cast<UInt16>(m_evInfo.msInfo.yMove); }
		inline UInt16 GetMouseDeltaX()				const	{ return static_cast<UInt16>(m_evInfo.msInfo.xMoveDelta); }
		inline UInt16 GetMouseDeltaY()				const	{ return static_cast<UInt16>(m_evInfo.msInfo.yMoveDelta); }
		inline UInt16 GetMouseHeldX(UInt16 msCode)	const	{ return static_cast<UInt16>(m_evInfo.msInfo.xHeld[msCode]); }
		inline UInt16 GetMouseHeldY(UInt16 msCode)	const	{ return static_cast<UInt16>(m_evInfo.msInfo.yHeld[msCode]); }

		inline bool GetMousePressed(MouseButtons msCode)	const	{ return m_evInfo.msInfo.bsButtons[msCode].bPressed; }
		inline bool GetMouseReleased(MouseButtons msCode)	const	{ return m_evInfo.msInfo.bsButtons[msCode].bReleased; }
		inline bool GetMouseHeld(MouseButtons msCode)		const	{ return m_evInfo.msInfo.bsButtons[msCode].bHeld; }

		inline bool GetKeyPressed(KeyCodes kCode)			const	{ return m_evInfo.kbInfo.bsKeys[kCode].bPressed; }
		inline bool GetKeyReleased(KeyCodes kCode)			const	{ return m_evInfo.kbInfo.bsKeys[kCode].bReleased; }
		inline bool GetKeyHeld(KeyCodes kCode)				const	{ return m_evInfo.kbInfo.bsKeys[kCode].bHeld; }
		// --setters
		void SetWndSize(UInt16 nWidth, UInt16 nHeight);
		void SetTitle(const char* strTitle);
		void SetPxSize(UInt16 nWidth, UInt16 nHeight);
		
		void SetWndInfo(const CWindowInfo& rwInfo);
		void SetPxInfo(const CPixelInfo& rpxInfo);
		void SetCursorInfo(const CCursorInfo& rcurInfo);
		// --core_methods
		virtual void Run() override;
		virtual bool Init() override;
		virtual void Quit() override;
		virtual void Update() override;
		virtual void OnEvent(AEvent& rEvt) override;
		// --drawing_methods
		inline void DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor);
		inline void DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor);
		inline void DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor);
		inline void DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor);
		inline void DrawBytesXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte* str, UInt16 unLen);
		inline void DrawRectXYWH(UInt16 nX, UInt16 nY, UInt16 nW, UInt16 nH, UInt16 cColor);
	private:
		inline void PollEvents();
		inline void SwapBuffers();
		inline void UpdateCursor();
		inline void UpdateKeyboard();
	private:
		CFrameBuf m_fb;
		Ptr m_pCout, m_pCin;

		CWindowInfo m_wInfo;
		CPixelInfo m_pxInfo;
		CCursorInfo m_curInfo;
		CEventsInfo m_evInfo;
	};
	inline void CEngine::DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor) {
		UInt16 unHeight = m_fb.GetHeight();
		for (UInt16 ix = xCrd0; ix <= xCrd1; ix++) {
			for (UInt16 iy = 0; iy <= unHeight; iy++) {
				m_fb.DrawPixelXY(ix, iy, cColor);
			}
		}
	}
	inline void CEngine::DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor) {
		UInt16 unWidth = m_fb.GetWidth();
		for (UInt16 iy = yCrd0; iy <= yCrd1; iy++) {
			for (UInt16 ix = 0; ix <= unWidth; ix += 2) {
				m_fb.DrawPixelXY(ix, iy, cColor);
			}
		}
	}
	inline void CEngine::DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor) {
		Int16 nDeltaX = xCrd1 - xCrd0;
		Int16 nDeltaY = yCrd1 - yCrd0;
		Int16 nDirX = nDeltaX < 0 ? -1 : 1;
		Int16 nDirY = nDeltaY < 0 ? -1 : 1;
		Int16 nErr = 0;
		Int16 nDeltaErr = nDeltaY;
		for (Int16 nX = xCrd0, nY = yCrd0; nX != xCrd1; nX += nDirX) {
			m_fb.DrawPixelXY(nX, nY, cColor);
			nErr += nDeltaErr;
			if (nErr > nDeltaX) {
				nY += nDirY;
				nErr -= (nDeltaX);
			}
		}
	}
	inline void CEngine::DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor) {
		UInt16 unWidth = m_fb.GetWidth();
		UInt16 unHeight = m_fb.GetHeight();
		if (nLt > nRt) { nLt = nLt - nRt; nRt = nRt + nLt; nLt = nRt - nLt; }
		if (nTp > nBt) { nTp = nTp - nBt; nBt = nBt + nTp; nTp = nBt - nTp; }
		if (nLt > unWidth) { nLt = unWidth; }
		if (nRt > unWidth) { nRt = unWidth; }
		if (nTp > unHeight) { nTp = unHeight; }
		if (nBt > unHeight) { nBt = unHeight; }
		if (nBt - nTp > unHeight) { return; }
		for (UInt16 iy = nTp; iy <= nBt; iy++) {
			for (UInt16 ix = nLt; ix <= nRt; ix += 2) {
				m_fb.DrawPixelXY(ix, iy, cColor);
			}
		}
	}
	inline void CEngine::DrawRectXYWH(UInt16 nX, UInt16 nY, UInt16 nW, UInt16 nH, UInt16 cColor) {
		DrawRectXY(nX, nY, nX + nW, nY + nH, cColor);
	}
	inline void CEngine::DrawBytesXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, Byte* str, UInt16 unLen) {
		m_fb.DrawBytesXY(xCrd, yCrd, cColor, str, unLen);
	}
}
#endif	// CMD_ENGINE_H