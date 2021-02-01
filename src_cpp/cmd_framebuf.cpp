#include <cmd_pch.hpp>
#include "cmd_framebuf.h"

#include <cmd_engine.h>

namespace CMD
{
	CFrameBuf::CFrameBuf():m_pCout(nullptr),
		m_szPxCount(0), m_pPxData(nullptr),
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
			DelTArr<CPixel>(CEngine::Get().GetMemory(), m_pPxData, m_szPxCount);
			m_pPxData = nullptr;
			m_szPxCount = 0;
		}

		V2xy whSize = { CEngine::Get().GetWndWidth() + 1, CEngine::Get().GetWndHeight() + 1 };

		if (m_Info.dwSize.X < whSize.X) { m_Info.dwSize.X = whSize.X; }
		if (m_Info.dwSize.Y < whSize.Y) { m_Info.dwSize.Y = whSize.Y; }
		m_Info.srWindow = { 0, 0, GetWidth(), GetHeight() };
		m_Info.bFullscreenSupported = true;
		m_Info.dwCursorPosition = V2xy{ 0, 0 };
		m_Info.dwMaximumWindowSize = GetLargestConsoleWindowSize(m_pCout);
		//for (UInt8 cli = 0; cli < 16; cli++) { m_Info.ColorTable[cli] = 0x11'11'11 * cli; }
		m_Info.ColorTable[0] = 0x00'00'00;
		m_Info.ColorTable[1] = 0x00'00'77;
		m_Info.ColorTable[2] = 0x00'77'00;
		m_Info.ColorTable[3] = 0x00'77'77;
		m_Info.ColorTable[4] = 0x77'00'00;
		m_Info.ColorTable[5] = 0x77'00'77;
		m_Info.ColorTable[6] = 0x77'77'00;
		m_Info.ColorTable[7] = 0x77'77'77;

		m_Info.ColorTable[8] = 0x00'00'00;
		m_Info.ColorTable[9] = 0x00'00'FF;
		m_Info.ColorTable[10] = 0x00'FF'00;
		m_Info.ColorTable[11] = 0x00'FF'FF;
		m_Info.ColorTable[12] = 0xFF'00'00;
		m_Info.ColorTable[13] = 0xFF'00'11;
		m_Info.ColorTable[14] = 0xFF'FF'00;
		m_Info.ColorTable[15] = 0xFF'FF'FF;

		m_Info.cbSize = sizeof(CFrameBufInfo);

		m_szPxCount = static_cast<Size>(GetWidth()) * static_cast<Size>(GetHeight());
		m_pPxData = NewTArr<CPixel>(CEngine::Get().GetMemory(), m_szPxCount);
		memset(m_pPxData, 0, m_szPxCount * sizeof(CPixel));
	
		if (!SetConsoleScreenBufferInfoEx(m_pCout, &m_Info)) { return; }
		if (!SetConsoleScreenBufferSize(m_pCout, m_Info.dwSize)) { return; }
	}
    // --==</core_methods>==--
}