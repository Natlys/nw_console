#include <cmd_pch.hpp>
#include <cmd_gui.h>

#include <cmd_engine.h>

#include <nwlib/nwl_physics_2d.h>

IdStack CMD::CWidget::s_IdStack = IdStack();

namespace CMD
{
	CWidget::CWidget() :
		m_unId(0), m_strName("cwidget"),
		xyCoord{ 0, 0 }, whSize{ 10, 5 }, xywhPadding{ 1, 1, 1, 1 },
		xywhDrawRect{ 0, 0, 10, 10 },
		colorDefault(CCN_BG_4 | CCN_FG_8), colorDisable(CCN_BG_1 | CCN_FG_4),
		colorFocus(CCN_BG_8 | CCN_FG_12), colorAction(CCN_BG_8 | CCN_FG_12),
		colorCurrent(CCN_BG_4 | CCN_FG_8),
		m_wStates{ 0 },
		m_fnAction{ []()->UInt32 { return CWS_DEFAULT; } }
	{
		m_unId = s_IdStack.GetFreeId();
		m_strName = m_strName + "_" + std::to_string(m_unId);
	}
	CWidget::~CWidget()
	{
		s_IdStack.SetFreeId(m_unId);
	}
	// --setters
	void CWidget::SetName(const char* strName) { m_strName = strName; }
	void CWidget::SetAction(const Action& rAct) { m_fnAction = rAct; }
}

namespace CMD
{
	CMenuItem::CMenuItem() : CWidget() { }
	CMenuItem::~CMenuItem() { }

	// --setters
	// --core_methods
	void CMenuItem::OnDraw()
	{
		xywhDrawRect.x = xyCoord.x + xywhPadding.x;
		xywhDrawRect.y = xyCoord.y + xywhPadding.y;
		xywhDrawRect.z = xyCoord.x - xywhPadding.z + whSize.x;
		xywhDrawRect.w = xyCoord.y - xywhPadding.w + whSize.y;
		CEngine::Get().DrawRectXY(static_cast<UInt16>(xywhDrawRect.x), static_cast<UInt16>(xywhDrawRect.y),
			static_cast<UInt16>(xywhDrawRect.z), static_cast<UInt16>(xywhDrawRect.w), colorCurrent);
		CEngine::Get().DrawBytesXY(static_cast<UInt16>(xywhDrawRect.x), static_cast<UInt16>(xywhDrawRect.y),
			colorCurrent, &m_strName[0], strlen(&m_strName[0]));
	}
	void CMenuItem::OnEvent(MouseEvent& rmEvt)
	{
		switch (rmEvt.evType) {
		case ET_MOUSE_PRESS:
			if (GetState() == CWS_FOCUS) { OnState(CWS_ACT); }
			break;
		case ET_MOUSE_RELEASE:
			if (GetState() == CWS_FOCUS) { OnState(CWS_DEACT); }
			break;
		case ET_MOUSE_MOVE:
			if (IsCollidPointRect({ rmEvt.nX, rmEvt.nY }, xyCoord, xyCoord + whSize)) { OnState(CWS_FOCUS); }
			else { OnState(CWS_DEFOCUS); }
			break;
		default: break;
		}
	}
	void CMenuItem::OnEvent(KeyboardEvent& rkEvt)
	{
		switch (rkEvt.evType) {
		case ET_KEY_PRESS:
			switch (rkEvt.unKeyCode) {
			case CMD::KC_ENTER:
				OnState(CWS_ACT);
				break;
			case CMD::KC_BACKSPACE:
				break;
			default: break;
			}
		case ET_KEY_RELEASE:
			switch (rkEvt.unKeyCode) {
			case CMD::KC_ENTER:
				OnState(CWS_DEACT);
				break;
			default: break;
			}
		default: break;
		}
	}
	UInt32 CMenuItem::OnState(CWidgetStates wState)
	{
		if (GetState() == CWS_DISABLE && wState != CWS_ENABLE) { return 0; }
		switch (wState) {
		case CWS_ENABLE:
			colorCurrent = colorDefault;
			break;
		case CWS_DISABLE:
			colorCurrent = colorDisable;
			break;
		case CWS_ACT:
			colorCurrent = colorAction;
			m_fnAction();
			break;
		case CWS_DEACT:
			colorCurrent = colorDefault;
			break;
		case CWS_FOCUS:
			colorCurrent = colorFocus;
			break;
		case CWS_DEFOCUS:
			colorCurrent = colorDefault;
			break;
		default: break;
		}
		for (UInt32 si = 1; si > 10; si--) { m_wStates[si] = m_wStates[si - 1]; }
		m_wStates[0] = wState;
		return wState;
	}
}