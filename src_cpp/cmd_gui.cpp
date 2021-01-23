#include <cmd_pch.hpp>
#include <cmd_gui.h>

#include <cmd_engine.h>

CMD::IdStack CMD::CWidget::s_IdStack = CMD::IdStack();

namespace CMD
{
	CWidget::CWidget(const char* strName) : m_unId(0), m_strName(strName) {
		m_unId = s_IdStack.GetFreeId();
		m_strName = m_strName + "_" + std::to_string(m_unId);
	}
	CWidget::~CWidget(){
		s_IdStack.SetFreeId(m_unId);
	}

	// --setters
	// --==<core_methods>==--
	void CWidget::OnDraw()
	{
		CmdEngine::Get().DrawStrXY(m_xyCrd.X, m_xyCrd.Y, m_Color, &m_strName[0]);
	}
	void CWidget::OnRedraw()
	{
		CmdEngine::Get().DrawStrXY(m_xyCrd.X, m_xyCrd.Y, CCN_BG_1 | CCN_FG_1, &m_strName[0]);
	}
	void CWidget::OnHovered(UInt16 xCrd, UInt16 yCrd)
	{
		if (xCrd >= m_xyCrd.X && yCrd >= m_xyCrd.Y &&
			xCrd <= m_xyCrd.X + m_whSize.X && yCrd <= m_xyCrd.Y + m_whSize.Y) {
			m_bIsHovered = true;
		}
		else { m_bIsHovered = false; }
		m_Color = m_bIsHovered ? CCN_BG_8 | CCN_FG_12 : CCN_BG_4 | CCN_FG_8;
		OnDraw();
	}
	void CWidget::OnActivate(bool bIsActive)
	{
		m_bIsActive = bIsActive;
		m_Color = bIsActive ? CCN_BG_12 | CCN_FG_16 : CCN_BG_2 | CCN_FG_4;
		for (auto& itWidget : m_SubWidgets) { SetEnabled(bIsActive); }
		OnDraw();
	}
	// --==</core_methods>==--
}

namespace CMD
{
	CMenu::CMenu() : CMenu("cmenu") { }
	CMenu::CMenu(const char* strName) : m_strName("cmenu"),
		m_CurrItem(m_Items.end()),
		xCrd(0), yCrd(0),
		wSize(10), hSize(4)
	{
		strcpy_s(m_strName, &strName[0]);
	}
	CMenu::~CMenu() { }

	// --setters
	void CMenu::SetCurrItem(CMenu* pMenu) {
		m_CurrItem->second.Color = CCN_BG_4 | CCN_FG_8;
		m_CurrItem = m_Items.begin();
		if (pMenu == nullptr) { return; }
		m_CurrItem = m_Items.find(pMenu->GetName());
		m_CurrItem->second.Color = CCN_BG_8 | CCN_FG_12;
	}
	void CMenu::SetCurrItem(const char* strName) {
		m_CurrItem = m_Items.find(strName);
		if (m_CurrItem == m_Items.end()) { m_CurrItem = m_Items.begin(); }
		m_CurrItem->second.Color = CCN_BG_8 | CCN_FG_12;
	}
	// --core_methods
	void CMenu::OnDraw()
	{
		Int16 xCrdRel0 = xCrd + PadLt, yCrdRel0 = yCrd + PadTp;
		Int16 xCrdRel1 = xCrd + wSize - PadRt, yCrdRel1 = xCrd + hSize - PadBt;
		if (m_pOverMenu != nullptr) {
			xCrdRel0 += m_pOverMenu->xCrd;
			yCrdRel0 += m_pOverMenu->yCrd;
			xCrdRel1 += m_pOverMenu->xCrd;
			yCrdRel1 += m_pOverMenu->yCrd;
		}
		//CmdEngine::Get().DrawRectXY(xCrdRel0, yCrdRel0, xCrdRel1, yCrdRel1, Color);
		CmdEngine::Get().DrawStrXY(xCrdRel0, yCrdRel0, Color, &m_strName[0]);
		if (m_Items.empty()) { return; }
		for (MenuItems::iterator itItem = m_Items.begin(); itItem != m_Items.end(); itItem++) { itItem->second.OnDraw(); }
	}
	void CMenu::OnAction(CMenuActions cmAction)
	{
		if (m_CurrItem == m_Items.end()) { SetCurrItem(m_Items.begin()->second.GetName()); }
		switch (cmAction) {
		case CMA_ACT:
			break;
		case CMA_DEACT:
			break;
		case CMA_MOVE_LT:
			m_CurrItem--;
			break;
		case CMA_MOVE_RT:
			m_CurrItem++;
			break;
		case CMA_MOVE_DN:
			m_CurrItem--;
			break;
		case CMA_MOVE_UP:
			m_CurrItem++;
			break;
		default:	break;
		}
		if (m_CurrItem == m_Items.end()) { SetCurrItem(m_Items.begin()->second.GetName()); }
		m_CurrItem->second.Color = CCN_BG_8 | CCN_FG_12;
		OnDraw();
	}
}