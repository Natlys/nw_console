#include "cmd_pch.hpp"
#include "cmd_engine.h"

#define CMD_INPUT_FLAGS ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT

namespace CMD
{
    CmdEngine::CmdEngine() :
        m_cwInfo(CWindowInfo()),
        m_cpxInfo(CPixelInfo()),
        m_cfbInfo(CFrameBufInfo()),
        m_pCout(nullptr), m_pCin(nullptr),
        m_pCoutOrig(nullptr), m_pCinOrig(nullptr),
        m_cpxBuf(),
        m_cpxClear(CPixel{ CPixelTypes::CPT_SOLID, CColorsNum::CCN_BG_1 | CColorsNum::CCN_FG_1 }),
        m_cpxDraw(CPixel{ CPixelTypes::CPT_SOLID, CColorsNum::CCN_BG_1 | CColorsNum::CCN_FG_16 }),
        m_unSoundFreq(6'000), m_unSoundDur(1)
    {
        m_pCout = m_pCoutOrig = GetStdHandle(STD_OUTPUT_HANDLE);
        m_pCinOrig = m_pCin = GetStdHandle(STD_INPUT_HANDLE);
    }
    CmdEngine::~CmdEngine()
    {
        SetConsoleActiveScreenBuffer(m_pCoutOrig);
        system("\a");
    }

    // --setters
    void CmdEngine::SetTitle(const char* strTitle) { m_cwInfo.strTitle = strTitle; }

    void CmdEngine::SetWndInfo(const CWindowInfo& rcwInfo) { m_cwInfo.xywhRect = rcwInfo.xywhRect; }
    void CmdEngine::SetWndSize(UInt16 nWidth, UInt16 nHeight) {
        m_cwInfo.xywhRect.Left = m_cwInfo.xywhRect.Top = 0;
        m_cfbInfo.dwSize.X = (m_cwInfo.xywhRect.Right = nWidth) + 1;
        m_cfbInfo.dwSize.Y = (m_cwInfo.xywhRect.Bottom = nHeight) + 1;
    }
    void CmdEngine::SetPxInfo(const CPixelInfo& rcpxInfo) { m_cpxInfo = rcpxInfo; }
    void CmdEngine::SetPxSize(UInt16 nWidth, UInt16 nHeight){
        m_cpxInfo.dwFontSize.X = nWidth;
        m_cpxInfo.dwFontSize.Y = nHeight;
        m_cpxInfo.FontFamily = FF_DONTCARE;
        m_cpxInfo.FontWeight = FW_NORMAL;
        m_cpxInfo.nFont = 0;
        swprintf_s(m_cpxInfo.FaceName, L"Consolas");
        m_cpxInfo.cbSize = sizeof(m_cpxInfo);
    }
    void CmdEngine::SetFBInfo(const CFrameBufInfo& rfbInfo) { m_cfbInfo = rfbInfo; }

    bool CmdEngine::ResetWindow() {
        if (m_cfbInfo.dwSize.X <= 0 || m_cfbInfo.dwSize.Y <= 0 ||
            m_cwInfo.GetWidth() > m_cfbInfo.dwSize.X || m_cwInfo.GetHeight() > m_cfbInfo.dwSize.Y) {
            Quit(); return false;
        }

        {   // pixels
            if (!SetCurrentConsoleFontEx(m_pCout, TRUE, &m_cpxInfo)) { Quit(); return false; }
        }
        {   // framebuffer
            m_cpxBuf.resize(static_cast<Size>(m_cfbInfo.dwSize.X) * static_cast<Size>(m_cfbInfo.dwSize.Y));

            m_cfbInfo.dwMaximumWindowSize = m_cwInfo.whMaxSize = GetLargestConsoleWindowSize(m_pCout);
            if (m_cwInfo.GetWidth() > m_cwInfo.whMaxSize.X || m_cwInfo.GetHeight() > m_cwInfo.whMaxSize.Y) {
                m_cwInfo.xywhRect = { 0, 0, m_cwInfo.whMaxSize.X, m_cwInfo.whMaxSize.Y };
            }

            m_cfbInfo.dwMaximumWindowSize = m_cwInfo.whMaxSize;
            m_cfbInfo.srWindow = m_cwInfo.xywhRect;
            m_cfbInfo.wAttributes = 0b0000'1010;
            m_cfbInfo.wPopupAttributes = 0b0000'0010;
            m_cfbInfo.bFullscreenSupported = 1;
            m_cfbInfo.dwCursorPosition = V2xy{ 0, 0 };
            m_cfbInfo.cbSize = sizeof(m_cfbInfo);
            // in the hex every 2 digits are one byte;
            // here is abgr representation from left to right
            // or rgba from right to left
            // Here I make monochromatic pallete
            for (UInt8 cli = 0; cli < 16; cli++) m_cfbInfo.ColorTable[cli] = 0x11'11'11 * cli;

            V4xywh xywhMinRect = { 0, 0, 1, 1 };
            if (!SetConsoleWindowInfo(m_pCout, TRUE, &xywhMinRect)) { Quit(); return false; }
            if (!SetConsoleScreenBufferInfoEx(m_pCout, &m_cfbInfo)) { Quit(); return false; }
            if (!SetConsoleScreenBufferSize(m_pCout, m_cfbInfo.dwSize)) { Quit(); return false; }
            if (!SetConsoleActiveScreenBuffer(m_pCout)) { Quit(); return false; }
        }
        {   // window
            if (!SetConsoleWindowInfo(m_pCout, TRUE, &m_cwInfo.xywhRect)) { Quit(); return false; }
        }
        return true;
    }

    // --<core_methods>--
    bool CmdEngine::Init()
    {
        if (m_pCoutOrig == INVALID_HANDLE_VALUE || m_pCinOrig == INVALID_HANDLE_VALUE) { return false; }

        if (!SetConsoleMode(m_pCin, CMD_INPUT_FLAGS)) { return false; }

        if (!ResetWindow()) { Quit(); return false; }

        return true;
    }
    void CmdEngine::Quit()
    {
        if (!m_bIsRunning) { return; }
        m_bIsRunning = false;
        system("\a");
    }
    void CmdEngine::Run() {
        m_bIsRunning = true;
        m_thrRun = std::thread([this]()->void { while (m_bIsRunning) { Update(); } });
    }

    inline void CmdEngine::Update()
    {
        m_tpCurrTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> durElapsed = m_tpCurrTime - m_tpLastTime;
        m_tpLastTime = m_tpCurrTime;
        m_nDeltaTime = durElapsed.count();
        
        Char strTitle[256];
        sprintf(&strTitle[0], "%s::updates/sec = %3.2f", &m_cwInfo.strTitle[0], 1.0f / m_nDeltaTime);
        SetConsoleTitleA(&strTitle[0]);

        OnEvent();
        if (GetKeyPressed(CMD::KC_ESCAPE)) { Quit(); }
    }
    // --</core_methods>--

    // --<on_event_methods>--
    inline void CmdEngine::OnEvent() {
        GetNumberOfConsoleInputEvents(m_pCin, &m_cevInfo.unEvGetCount);

        if (m_cevInfo.unEvGetCount > 0) {
            ReadConsoleInputA(m_pCin, m_cevInfo.irEvents, m_cevInfo.unEvGetCount, &m_cevInfo.unEvReadCount);
            for (UInt16 evi = 0; evi < m_cevInfo.unEvGetCount; evi++) {
                MOUSE_EVENT_RECORD& rmsevt = m_cevInfo.irEvents[evi].Event.MouseEvent;
                KEY_EVENT_RECORD& rkevt = m_cevInfo.irEvents[evi].Event.KeyEvent;
                
                WINDOW_BUFFER_SIZE_RECORD& rwszevt = m_cevInfo.irEvents[evi].Event.WindowBufferSizeEvent;
                MENU_EVENT_RECORD& rmnevt = m_cevInfo.irEvents[evi].Event.MenuEvent;
                FOCUS_EVENT_RECORD& rfevt = m_cevInfo.irEvents[evi].Event.FocusEvent;
                
                switch (m_cevInfo.irEvents[evi].EventType) {
                case EC_MOUSE:
                    switch (m_cevInfo.irEvents[evi].Event.MouseEvent.dwEventFlags) {
                    case ET_MOUSE_MOVED:
                        m_cevInfo.MouseInfo.xyMove = rmsevt.dwMousePosition;
                    case ET_VSCROLL:
                        break;
                    case ET_HSCROLL:
                        break;
                    case 0:
                        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
                            m_cevInfo.MouseInfo.Buttons[mi].bState.bNext = ((1 << mi) & rmsevt.dwButtonState) > 0;
                        }
                        break;
                    }
                case EC_KEYBOARD:
                    m_cevInfo.KeyboardInfo.bsButtons[rkevt.wVirtualKeyCode].bNext = rkevt.bKeyDown;
                    m_cevInfo.KeyboardInfo.cTypedChars[rkevt.wVirtualKeyCode].ascii = rkevt.uChar.AsciiChar;
                    m_cevInfo.KeyboardInfo.cTypedChars[rkevt.wVirtualKeyCode].unicode = rkevt.uChar.UnicodeChar;
                    break;
                case EC_FOCUS:
                    m_cwInfo.bIsFocused = rfevt.bSetFocus;
                    break;
                case EC_WINDOW_SIZE:
                    break;
                }
            }
        }
        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
            auto& rBtn = m_cevInfo.MouseInfo.Buttons[mi];
            rBtn.bState.bPressed = rBtn.bState.bReleased = false;
            if (rBtn.bState.bNext != rBtn.bState.bLast) {
                if (rBtn.bState.bNext == true) {
                    rBtn.xyHeld = m_cevInfo.MouseInfo.xyMove;
                    rBtn.bState.bPressed = rBtn.bState.bHeld = true;
                }
                else {
                    rBtn.bState.bReleased = true; rBtn.bState.bHeld = false;
                }
            }
            rBtn.bState.bLast = rBtn.bState.bNext;
        }
        for (UInt16 ki = 0; ki < KC_COUNT; ki++) {
            ButtonState& rbs = m_cevInfo.KeyboardInfo.bsButtons[ki];
            rbs.bPressed = rbs.bReleased = false;
            if (rbs.bNext != rbs.bLast) {
                if (rbs.bNext == true) {
                    rbs.bPressed = rbs.bHeld = true;
                
                }
                else {
                    rbs.bReleased = true; rbs.bHeld = false;
                }
            }
            rbs.bLast = rbs.bNext;
        }
    }
    // --</on_event_methods>--
    
    // --<other_methods>--
    void CmdEngine::MakeSound(SoundTypes sType) {
        switch (sType) {
        case SoundTypes::ST_BEEP:
            Beep(m_unSoundFreq, m_unSoundDur);
            break;
        case SoundTypes::ST_CMD_BELL:
            system("\a");
            break;
        default: break;
        }
    }
    void CmdEngine::ChangeSoundFreq(Int32 nFreq) {
        m_unSoundFreq += nFreq;
        if ((m_unSoundFreq + nFreq) < 100) { m_unSoundFreq = 100; }
        else if ((m_unSoundFreq + nFreq) > 18'000) { m_unSoundFreq = 18'000; }
    }
    void CmdEngine::ChangeSoundDur(Int32 nDur) {
        m_unSoundDur += nDur;
        if ((m_unSoundDur + nDur) < 1) { m_unSoundDur = 1; }
        else if ((m_unSoundDur + nDur) > 10) { m_unSoundDur = 10; }
    }
    // --</other_methods>--
}