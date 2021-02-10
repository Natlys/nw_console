#include "nwc_pch.hpp"
#include "nwc_engine.h"

#define NWC_INPUT_FLAGS ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT

namespace NWC
{
    CmdEngine::CmdEngine() :
        m_wInfo(CWindowInfo()),
        m_pxInfo(CPixelInfo()),
        m_pCout(nullptr), m_pCin(nullptr)
    {
        this->SetWndSize(50, 20);
        this->SetPxSize(8, 16);
        m_fmBuf.SetSizeWH(GetWndWidth(), GetWndHeight());
        m_pCout = GetStdHandle(STD_OUTPUT_HANDLE);
        m_pCin = GetStdHandle(STD_INPUT_HANDLE);
        m_wInfo.strTitle = "cwindow";
    }
    CmdEngine::~CmdEngine() { }

    // --setters
    void CmdEngine::SetTitle(const char* strTitle) { m_wInfo.strTitle = strTitle; SetConsoleTitleA(&strTitle[0]); }
    void CmdEngine::SetWndSize(UInt16 unWidth, UInt16 unHeight) {
        m_wInfo.xywhRect.Left = m_wInfo.xywhRect.Top = 0;
        m_wInfo.xywhRect.Right = unWidth; m_wInfo.xywhRect.Bottom = unHeight;
    }
    void CmdEngine::SetPxSize(UInt16 nWidth, UInt16 nHeight){
        m_pxInfo.dwFontSize.X = nWidth;
        m_pxInfo.dwFontSize.Y = nHeight;
        m_pxInfo.FontFamily = FF_DONTCARE;
        m_pxInfo.FontWeight = FW_NORMAL;
        m_pxInfo.nFont = 0;
        swprintf_s(m_pxInfo.FaceName, L"Consolas");
        m_pxInfo.cbSize = sizeof(m_pxInfo);
    }

    void CmdEngine::SetWndInfo(const CWindowInfo& rcwInfo) { m_wInfo = rcwInfo; SetConsoleWindowInfo(m_fmBuf.GetNative(), TRUE, &m_wInfo.xywhRect); }
    void CmdEngine::SetPxInfo(const CPixelInfo& rcpxInfo) { m_pxInfo = rcpxInfo; SetCurrentConsoleFontEx(m_fmBuf.GetNative(), TRUE, &m_pxInfo); }
    void CmdEngine::SetCursorInfo(const CCursorInfo& rcurInfo) { m_curInfo = rcurInfo; SetConsoleCursorInfo(m_fmBuf.GetNative(), &m_curInfo); }
    
    // --<core_methods>--
    void CmdEngine::Run() {
        Init();
        if (!m_bIsRunning) { return; }
        if (m_States.empty()) { return; }

        auto fnRunLoop = [this]()->void { while (m_bIsRunning) { Update(); } Quit(); };
        m_thrRun = Thread(fnRunLoop);
    }
    bool CmdEngine::Init()
    {
        if (m_bIsRunning || m_Memory.GetDataBeg() != nullptr) { return false; }
        m_bIsRunning = true;
        m_Memory = MemArena(new Byte[1 << 20], 1 << 20);

        SetTitle(&m_wInfo.strTitle[0]);
        if (!SetConsoleMode(m_pCin, NWC_INPUT_FLAGS)) { Quit(); return false; }

        {
            V4xywh xywhMinRect = { 0, 0, 1, 1 };
            if (!SetConsoleWindowInfo(m_fmBuf.GetNative(), TRUE, &xywhMinRect)) { Quit(); return false; }
            if (!SetCurrentConsoleFontEx(m_fmBuf.GetNative(), TRUE, &m_pxInfo)) { Quit(); return false; }

            m_wInfo.whMaxSize = GetLargestConsoleWindowSize(m_pCout);
            if (m_wInfo.GetHeight() > m_wInfo.whMaxSize.Y) { m_wInfo.xywhRect.Top = 0; m_wInfo.xywhRect.Bottom = m_wInfo.whMaxSize.Y; }
            if (m_wInfo.GetHeight() > m_wInfo.whMaxSize.Y) { m_wInfo.xywhRect.Top = 0; m_wInfo.xywhRect.Bottom = m_wInfo.whMaxSize.Y; }

            m_fmBuf.Remake();
            if (!SetConsoleWindowInfo(m_fmBuf.GetNative(), TRUE, &m_wInfo.xywhRect)) { Quit(); return false; }
            if (!SetConsoleActiveScreenBuffer(m_fmBuf.GetNative())) { Quit(); return false; }
        }

        for (auto& itState : m_States) { if (!itState->Init()) { Quit(); return false; } }

        return m_bIsRunning;
    }
    void CmdEngine::Quit()
    {
        if (m_bIsRunning || m_Memory.GetDataBeg() == nullptr) { return; }
        m_bIsRunning = false;
        
        for (auto& itState : m_States) { itState->OnQuit(); }

        delete[] m_Memory.GetDataBeg();
        m_Memory = MemArena(nullptr, 0);
        SetConsoleActiveScreenBuffer(m_pCout);
    }

    void CmdEngine::Update()
    {
        TimeSys::Update();
        Char strTime[16]{ 0 };
        sprintf(strTime, "ups: %3.2f", 1.0f / TimeSys::GetDeltaS());
        DrawBytesXY(GetWndWidth() - 16, 2, GetWndWidth(), 3, NWC::CCD_FG_GREEN, &strTime[0], 16);

        SwapBuffers();
        m_fmBuf.Clear();
        PollEvents();
        UpdateCursor();
        UpdateKeyboard();
        
        for (auto& itState : m_States) { itState->Update(); }
    }

    void CmdEngine::OnEvent(AEvent& rEvt)
    {
        if (rEvt.IsInCategory(EC_MOUSE)) {
            MouseEvent* pmEvt = static_cast<MouseEvent*>(&rEvt);
            switch (pmEvt->evType) {
            case ET_MOUSE_MOVE:
                m_evInfo.msInfo.xMoveDelta = pmEvt->nX - m_evInfo.msInfo.xMove;
                m_evInfo.msInfo.yMoveDelta = pmEvt->nY - m_evInfo.msInfo.yMove;
                m_evInfo.msInfo.xMove = pmEvt->nX;
                m_evInfo.msInfo.yMove = pmEvt->nY;
                break;
            case ET_MOUSE_SCROLL:
                m_evInfo.msInfo.xScroll = pmEvt->nX;
                m_evInfo.msInfo.yScroll = pmEvt->nY;
                break;
            case ET_MOUSE_RELEASE:
                m_evInfo.msInfo.bsButtons[pmEvt->nButton].bNew = false;
                break;
            case ET_MOUSE_PRESS:
                m_evInfo.msInfo.bsButtons[pmEvt->nButton].bNew = true;
                break;
            }
            if (rEvt.bIsHandled) return;
            for (auto& itState : m_States) { itState->OnEvent(*pmEvt); }
        }
        else if (rEvt.IsInCategory(EC_KEYBOARD)) {
            KeyboardEvent* pkEvt = static_cast<KeyboardEvent*>(&rEvt);
            switch (pkEvt->evType) {
            case ET_KEY_RELEASE:
                m_evInfo.kbInfo.bsKeys[pkEvt->unKeyCode].bNew = false;
                switch (pkEvt->unKeyCode) {
                case KC_ESCAPE:
                    StopRunning();
                    rEvt.bIsHandled = true;
                    break;
                default: break;
                }
                break;
            case ET_KEY_PRESS:
                m_evInfo.kbInfo.bsKeys[pkEvt->unKeyCode].bNew = true;
                switch (pkEvt->unKeyCode) {
                case KC_ESCAPE:
                    break;
                default: break;
                }
                break;
            case ET_KEY_CHAR:
                break;
            }
            if (rEvt.bIsHandled) { return; }
            for (auto& itState : m_States) { itState->OnEvent(*pkEvt); }
        }
        else if (rEvt.IsInCategory(EC_WINDOW)) {
            WindowEvent* pwEvt = static_cast<WindowEvent*>(&rEvt);
            switch (pwEvt->evType) {
            case ET_WINDOW_RESIZE:
                break;
            case ET_WINDOW_MOVE:
                break;
            case ET_WINDOW_FOCUS:
                break;
            case ET_WINDOW_CLOSE:
                StopRunning();
                rEvt.bIsHandled = true;
                break;
            }
            if (rEvt.bIsHandled) { return; }
            for (auto& itState : m_States) { itState->OnEvent(*pwEvt); }
        }
    }
    // --==</core_methods>==--
    
    // --==<implementation_methods>==--
    inline void CmdEngine::SwapBuffers() {
        if (!WriteConsoleOutputW(m_fmBuf.GetNative(), &m_fmBuf.GetPxData()[0],
            { m_fmBuf.GetWidth(), m_fmBuf.GetHeight() }, { 0, 0 }, &m_fmBuf.GetInfo().srWindow)) { StopRunning(); return; }
    }
    inline void CmdEngine::PollEvents() {
        GetNumberOfConsoleInputEvents(m_pCin, &m_evInfo.unEvGetCount);
        if (m_evInfo.unEvGetCount > 0) {
            ReadConsoleInputA(m_pCin, m_evInfo.irEvents, m_evInfo.unEvGetCount, &m_evInfo.unEvReadCount);
            for (UInt16 evi = 0; evi < m_evInfo.unEvGetCount; evi++) {
                UInt32 evTypeId = m_evInfo.irEvents[evi].EventType;
                if (evTypeId == NWC_MS_EVT) {
                    MOUSE_EVENT_RECORD& rEvt = m_evInfo.irEvents[evi].Event.MouseEvent;
                    if (rEvt.dwEventFlags == NWC_MS_MOVED) {
                        MouseEvent msEvt(ET_MOUSE_MOVE, rEvt.dwMousePosition.X, rEvt.dwMousePosition.Y);
                        OnEvent(msEvt);
                    }
                    else {
                        for (UInt8 mi = 0; mi < NWC_MS_BTN_COUNT; mi++) {
                            auto& rmb = m_evInfo.msInfo.bsButtons[mi];
                            rmb.bNew = ((1 << mi) & rEvt.dwButtonState) > 0;
                            if (rmb.bNew != rmb.bOld) {
                                MouseEvent msEvt(rmb.bNew ? ET_MOUSE_PRESS : ET_MOUSE_RELEASE, mi);
                                OnEvent(msEvt);
                            }
                        }
                    }
                }
                else if (evTypeId == NWC_KEY_EVT) {
                    KEY_EVENT_RECORD& rEvt = m_evInfo.irEvents[evi].Event.KeyEvent;
                    if (rEvt.bKeyDown){
                        if (rEvt.wRepeatCount == 1) {
                            KeyboardEvent kbEvt(ET_KEY_PRESS, rEvt.wVirtualKeyCode);
                            OnEvent(kbEvt);
                        }
                        else {
                        }
                    }
                    else {
                        KeyboardEvent kbEvt(ET_KEY_RELEASE, rEvt.wVirtualKeyCode);
                        OnEvent(kbEvt);
                        if (rEvt.uChar.AsciiChar >= ' ' && rEvt.uChar.AsciiChar <= 'z') {
                            KeyboardEvent kbEvt(ET_KEY_CHAR, rEvt.uChar.AsciiChar);
                            OnEvent(kbEvt);
                        }
                    }
                }
                else if (evTypeId == NWC_FOCUS_EVT) {
                    WindowEvent wEvt(ET_WINDOW_FOCUS, m_evInfo.irEvents[evi].Event.FocusEvent.bSetFocus);
                    OnEvent(wEvt);
                }
                else if (evTypeId == NWC_WND_SIZE_EVT) {
                    WindowEvent wEvt(ET_WINDOW_RESIZE, m_evInfo.irEvents[evi].Event.WindowBufferSizeEvent.dwSize.X, m_evInfo.irEvents[evi].Event.WindowBufferSizeEvent.dwSize.Y);
                    OnEvent(wEvt);
                }
                else if (evTypeId == NWC_MENU_EVT) {
                    MENU_EVENT_RECORD& rEvt = m_evInfo.irEvents[evi].Event.MenuEvent;
                }
            }
        }
    }
    inline void CmdEngine::UpdateCursor() {
        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
            ButtonState& rbs = m_evInfo.msInfo.bsButtons[mi];
            rbs.bPressed = rbs.bReleased = false;
            if (rbs.bNew != rbs.bOld) {
                if (rbs.bNew == true) {
                    m_evInfo.msInfo.xHeld[mi] = m_evInfo.msInfo.xMove;
                    m_evInfo.msInfo.yHeld[mi] = m_evInfo.msInfo.yMove;
                    rbs.bPressed = rbs.bHeld = true;
                }
                else {
                    rbs.bReleased = true; rbs.bHeld = false;
                }
            }
            rbs.bOld = rbs.bNew;
        }
    }
    inline void CmdEngine::UpdateKeyboard() {
        for (UInt16 ki = 0; ki < KC_COUNT; ki++) {
            ButtonState& rbs = m_evInfo.kbInfo.bsKeys[ki];
            rbs.bPressed = rbs.bReleased = false;
            if (rbs.bNew != rbs.bOld) {
                if (rbs.bNew == true) {
                    rbs.bPressed = rbs.bHeld = true;

                }
                else {
                    rbs.bReleased = true; rbs.bHeld = false;
                }
            }
            rbs.bOld = rbs.bNew;
        }
    }
    // --==</implementation_methods>==--
}