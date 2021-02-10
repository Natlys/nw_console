#include <nwc_pch.hpp>
#include "nwc_framebuf.h"

#include <nwc_engine.h>

namespace NWC
{
	CFrameBuf::CFrameBuf():m_pCout(nullptr),
		m_unPxCount(0), m_pPxData(nullptr),
		m_cpxClear(CPixel{ CPT_SOLID, CCN_BG_1 | CCN_FG_1 }),
		m_Info(CFrameBufInfo())
	{
		m_pCout = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	}
	CFrameBuf::~CFrameBuf() { CloseHandle(m_pCout); }

    // --setters

    // --==<core_methods>==--
    void CFrameBuf::Remake() {
		if (m_pPxData != nullptr) {
			DelTArr<CPixel>(CmdEngine::Get().GetMemory(), m_pPxData, m_unPxCount);
			m_pPxData = nullptr;
			m_unPxCount = 0;
		}

		V2xy whSize = { CmdEngine::Get().GetWndWidth() + 1, CmdEngine::Get().GetWndHeight() + 1 };

		if (m_Info.dwSize.X < whSize.X) { m_Info.dwSize.X = whSize.X; }
		if (m_Info.dwSize.Y < whSize.Y) { m_Info.dwSize.Y = whSize.Y; }
		m_Info.srWindow = { 0, 0, GetWidth(), GetHeight() };
		m_Info.bFullscreenSupported = true;
		m_Info.wAttributes = CCD_BG_BLACK | CCD_FG_GREEN;
		m_Info.dwCursorPosition = V2xy{ 0, 0 };
		m_Info.dwMaximumWindowSize = GetLargestConsoleWindowSize(m_pCout);
		//for (UInt8 cli = 0; cli < 16; cli++) { m_Info.ColorTable[cli] = 0x11'11'11 * cli; }
		m_Info.ColorTable[0] = 0x00'00'00;
		m_Info.ColorTable[1] = 0x00'00'7F;
		m_Info.ColorTable[2] = 0x00'7F'00;
		m_Info.ColorTable[3] = 0x00'7F'7F;
		m_Info.ColorTable[4] = 0x7F'00'00;
		m_Info.ColorTable[5] = 0x7F'00'7F;
		m_Info.ColorTable[6] = 0x7F'7F'00;
		m_Info.ColorTable[7] = 0x7F'7F'7F;

		m_Info.ColorTable[8] = 0x00'00'00;
		m_Info.ColorTable[9] = 0x00'00'FF;
		m_Info.ColorTable[10] = 0x00'FF'00;
		m_Info.ColorTable[11] = 0x00'FF'FF;
		m_Info.ColorTable[12] = 0xFF'00'00;
		m_Info.ColorTable[13] = 0xFF'00'FF;
		m_Info.ColorTable[14] = 0xFF'FF'00;
		m_Info.ColorTable[15] = 0xFF'FF'FF;

		m_Info.cbSize = sizeof(CFrameBufInfo);

		m_unPxCount = static_cast<Size>(GetWidth()) * static_cast<Size>(GetHeight());
		m_pPxData = NewTArr<CPixel>(CmdEngine::Get().GetMemory(), m_unPxCount);
		memset(m_pPxData, 0, m_unPxCount * sizeof(CPixel));
	
		if (!SetConsoleScreenBufferInfoEx(m_pCout, &m_Info)) { return; }
		if (!SetConsoleScreenBufferSize(m_pCout, m_Info.dwSize)) { return; }
	}
    // --==</core_methods>==--
}