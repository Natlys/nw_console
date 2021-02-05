#ifndef CMD_ENGINE_H
#define CMD_ENGINE_H

#include <nwlib/nwl_engine.h>

#include <cmd_core.hpp>
#include <cmd_structs.h>
#include <cmd_framebuf.h>

namespace CMD
{
	/// CmdEngine class
	class CMD_API CmdEngine : public AEngine<CmdEngine>
	{
	public:
		CmdEngine();
		~CmdEngine();

		// --getters
		inline CFrameBuf* GetFrameBuf()				{ return &m_fmBuf; }
		
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
		inline void DrawLineX(Int16 nX0, Int16 nX1, CPixel cpx);
		inline void DrawLineY(Int16 nY0, Int16 nY1, CPixel cpx);
		inline void DrawLineXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, CPixel cpx);
		inline void DrawRectXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, CPixel cpx);
		inline void DrawRectXYWH(Int16 nX, Int16 nY, Int16 nW, Int16 nH, CPixel cpx);
		inline void DrawBytesXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, UInt16 cColor, Byte* str, UInt16 unLen);
	private:
		inline void PollEvents();
		inline void SwapBuffers();
		inline void UpdateCursor();
		inline void UpdateKeyboard();
	private:
		CFrameBuf m_fmBuf;
		Ptr m_pCout, m_pCin;

		CWindowInfo m_wInfo;
		CPixelInfo m_pxInfo;
		CCursorInfo m_curInfo;
		CEventsInfo m_evInfo;
	};
	inline void CmdEngine::DrawLineX(Int16 nX0, Int16 nX1, CPixel cpx) {
		UInt16 unHeight = m_fmBuf.GetHeight();
		for (UInt16 ix = nX0; ix <= nX1; ix++) {
			for (UInt16 iy = 0; iy <= unHeight; iy++) {
				m_fmBuf.DrawPixelXY(ix, iy, cpx);
			}
		}
	}
	inline void CmdEngine::DrawLineY(Int16 nY0, Int16 nY1, CPixel cpx) {
		UInt16 unWidth = m_fmBuf.GetWidth();
		for (UInt16 iy = nY0; iy <= nY1; iy++) {
			for (UInt16 ix = 0; ix <= unWidth; ix += 2) {
				m_fmBuf.DrawPixelXY(ix, iy, cpx);
			}
		}
	}
	inline void CmdEngine::DrawLineXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, CPixel cpx) {
		Int16 nDeltaX = nX1 - nX0;
		Int16 nDeltaY = nY1 - nY0;
		Int16 nDirX = nDeltaX < 0 ? -1 : 1;
		Int16 nDirY = nDeltaY < 0 ? -1 : 1;
		Int16 nErr = 0;
		Int16 nDeltaErr = nDeltaY;
		for (Int16 nX = nX0, nY = nY0; nX != nY1; nX += nDirX) {
			m_fmBuf.DrawPixelXY(nX, nY, cpx);
			nErr += nDeltaErr;
			if (nErr > nDeltaX) {
				nY += nDirY;
				nErr -= (nDeltaX);
			}
		}
	}
	inline void CmdEngine::DrawRectXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, CPixel cpx) {
		UInt16 unWidth = m_fmBuf.GetWidth();
		UInt16 unHeight = m_fmBuf.GetHeight();
		Int16 nDeltaX = nX0 > nX1 ? -1 : +1;
		Int16 nDeltaY = nY0 > nY1 ? -1 : +1;
		nY1 += nDeltaY;
		for (Int16 iy = nY0; iy != nY1; iy += nDeltaY) {
			for (Int16 ix = nX0; ix != nX1; ix += nDeltaX) {
				m_fmBuf.DrawPixelXY(ix, iy, cpx);
			}
		}
	}
	inline void CmdEngine::DrawRectXYWH(Int16 nX, Int16 nY, Int16 nW, Int16 nH, CPixel cpx) {
		DrawRectXY(nX, nY, nX + nW, nY + nH, cpx);
	}
	inline void CmdEngine::DrawBytesXY(Int16 nX0, Int16 nY0, Int16 nX1, Int16 nY1, UInt16 cColor, Byte* str, UInt16 unLen) {
		m_fmBuf.DrawBytesXY(nX0, nY0, nX1, nY1, cColor, str, unLen);
	}
}
#endif	// CMD_ENGINE_H