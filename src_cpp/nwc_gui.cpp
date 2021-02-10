#include <nwc_pch.hpp>
#include <nwc_gui.h>

#include <nwc_engine.h>

IdStack NWC::CWidget::s_IdStack = IdStack();

namespace NWC
{
	CWidget::CWidget() :
		m_unId(0), m_strName("cwidget"),
		xyCoord{ 0, 0 }, whSize{ 10, 5 }, rectPadding{ 1, 1, 1, 1 },
		pxDefault{ static_cast<Char16>(CPT_SOLID), CCN_BG_4 | CCN_FG_8 }, pxDisable{ static_cast<Char16>(CPT_SOLID), CCN_BG_1 | CCN_FG_4 },
		pxFocus{ static_cast<Char16>(CPT_SOLID), CCN_BG_8 | CCN_FG_12 }, pxAction{ static_cast<Char16>(CPT_SOLID), CCN_BG_8 | CCN_FG_12 },
		pxDraw{ pxDefault },
		m_wState(CWS_DEFAULT),
		m_fnAction{ []()->UInt32 { return CWS_DEFAULT; } }
	{
		m_unId = s_IdStack.GetFreeId();
		m_strName = m_strName + "_" + std::to_string(m_unId);
	}
	CWidget::~CWidget() { s_IdStack.SetFreeId(m_unId); }
	// --setters
	void CWidget::SetName(const char* strName) { m_strName = strName; }
	void CWidget::SetAction(const Action& rAct) { m_fnAction = rAct; }
}

namespace NWC
{
	CMenuItem::CMenuItem() : CWidget() { }
	CMenuItem::~CMenuItem() { }

	// --setters
	// --core_methods
	void CMenuItem::OnDraw()
	{
		V4i rectDraw;
		rectDraw.x = xyCoord.x + rectPadding.x;
		rectDraw.y = xyCoord.y + rectPadding.y;
		rectDraw.z = xyCoord.x - rectPadding.z + whSize.x;
		rectDraw.w = xyCoord.y - rectPadding.w + whSize.y;
		CmdEngine::Get().DrawRectXY(rectDraw.x, rectDraw.y,
			rectDraw.z, rectDraw.w, pxDraw);
		CmdEngine::Get().DrawBytesXY(
			rectDraw.x, rectDraw.y, rectDraw.z, rectDraw.w,
			pxDraw.Attributes, &m_strName[0], strlen(&m_strName[0]));
	}
	void CMenuItem::OnState(CWidgetStates wState)
	{
		if (GetState() == CWS_DISABLE && wState != CWS_ENABLE) { return; }
		switch (wState) {
		case CWS_ENABLE:
			pxDraw = pxDefault;
			break;
		case CWS_DISABLE:
			pxDraw = pxDisable;
			break;
		case CWS_ACT:
			pxDraw = pxAction;
			m_fnAction();
			break;
		case CWS_DEACT:
			pxDraw = pxDefault;
			break;
		case CWS_FOCUS:
			pxDraw = pxFocus;
			break;
		case CWS_DEFOCUS:
			pxDraw = pxDefault;
			break;
		default: break;
		}
		m_wState = wState;
	}
}