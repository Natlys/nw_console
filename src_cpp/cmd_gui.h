#ifndef CMD_GUI_H
#define CMD_GUI_H

#include <cmd_core.hpp>
#include <cmd_structs.h>

namespace CMD
{
	class CMD_API CWidget
	{
	public:
		using SubWidgets = std::unordered_map<UInt32, CWidget*>;
	public:
		CWidget(const char* strName);
		~CWidget();
		virtual ~CWidget();
		// --getters
		inline const char* GetName() { return &m_strName[0]; }
		inline UInt32 GetId() { return m_unId; }
		inline V2xy GetCoord() { return m_xyCrd; }
		inline V2xy GetSize() { return m_whSize; }
		inline SubWidgets& GetSubWidgets() { return m_SubWidgets; }
		inline CWidget* GetSubWidget(UInt32 unId) { return m_SubWidgets.find(unId) == m_SubWidgets.end() ? nullptr : m_SubWidgets[unId]; }
		inline bool IsEnabled() { return m_bIsEnabled; }
		inline bool IsHovered() { return m_bIsHovered; }
		inline bool IsActive() { return m_bIsActive; }
		// --setters
		inline void SetName(const char* strName) { m_strName = strName; }
		inline void SetEnabled(bool bIsEnabled);
		inline void SetCoord(UInt16 unX, UInt16 unY);
		inline void SetSize(UInt16 unWidth, UInt16 unHeight) { m_whSize.X = unWidth; m_whSize.Y = unHeight; }
		inline void AddSubWidget(CWidget* pcWidget);
		inline void RmvSubWidget(UInt32 unId);
		// --core_methods
		void OnDraw();
		void OnRedraw();
		void OnHovered(UInt16 xCrd, UInt16 yCrd);
		void OnActivate(bool bIsActive);
	private:
		static IdStack s_IdStack;
		UInt32 m_unId = 0;
		String m_strName = "";
		bool m_bIsEnabled = false;
		bool m_bIsHovered = false;
		bool m_bIsActive = false;
		V2xy m_xyCrd = { 0, 0 };
		V2wh m_whSize = { 1, 1 };
		UInt16 m_Color = CCN_BG_1 | CCN_FG_16;

		SubWidgets m_SubWidgets;
	};
	inline void CWidget::SetEnabled(bool bIsEnabled) {
		m_bIsEnabled = bIsEnabled;
		m_Color = bIsEnabled ? CCN_BG_4 | CCN_FG_8 : CCN_BG_2 | CCN_FG_4;
		for (auto& itWidget : m_SubWidgets) { SetEnabled(bIsEnabled); }
		OnDraw();
	}
	inline void CWidget::SetCoord(UInt16 unX, UInt16 unY) {
		OnRedraw();
		m_xyCrd.X = unX; m_xyCrd.Y = unY;
		OnDraw();
	}
	inline void CWidget::AddSubWidget(CWidget* pcWidget) {
		if (pcWidget == nullptr) { return; }
		m_SubWidgets[pcWidget->GetId()] = pcWidget;
	}
	inline void CWidget::RmvSubWidget(UInt32 unId) {
		auto& itWgt = m_SubWidgets.find(unId);
		if (itWgt == m_SubWidgets.end()) { return; }
		m_SubWidgets.erase(itWgt);
	}
}
namespace CMD
{
	enum CMenuActions : UInt32 {
		CMA_DISABLE = 0, CMA_ENABLE = 1,
		CMA_ACT, CMA_DEACT, CMA_BACK,
		CMA_MOVE_LT, CMA_MOVE_RT, CMA_MOVE_UP, CMA_MOVE_DN
	};
	/// CMenu class for CMD graphical user interface
	class CMD_API CMenu
	{
		using MenuItems = HashMap<String, CMenu>;
	public:
		UInt16 xCrd = 0, yCrd = 0;
		UInt16 wSize = 10, hSize = 5;
		UInt16 PadLt = 1, PadRt = 1, PadTp = 1, PadBt = 1;
		bool bIsEnabled = false;
		UInt16 Color = CCN_BG_4 | CCN_FG_8;
	public:
		CMenu();
		CMenu(const char* strName);
		~CMenu();
		// --getters
		inline const char* GetName() const { return &m_strName[0]; }
		inline MenuItems& GetItems() { return m_Items; }
		// --setters
		void SetCurrItem(CMenu* pMenu);
		void SetCurrItem(const char* strName);
		// --core_methods
		void OnDraw();
		void OnAction(CMenuActions cmAction);
		// --operators
		inline CMenu& operator[](const char* strName);
	private:
		CMenu* m_pOverMenu = nullptr;
		Char m_strName[256];
		MenuItems m_Items;
		MenuItems::iterator m_CurrItem;
	};
	inline CMenu& CMenu::operator[](const char* strName) {
		m_Items[strName] = CMenu(strName);
		m_Items[strName].m_pOverMenu = this;
		return m_Items[strName];
	}
		inline CWidget* GetSubWidget(UInt32 unId) { return m_SubWidgets.find(unId) == m_SubWidgets.end()? nullptr : m_SubWidgets[unId]; }
		inline bool IsEnabled() { return m_bIsEnabled; }
		// --setters
		inline void SetName(const char* strName) { m_strName = strName; }
		inline void SetCoord(UInt16 unX, UInt16 unY) { m_xyCrd.X = unX; m_xyCrd.Y = unY; }
		inline void SetSize(UInt16 unWidth, UInt16 unHeight) { m_whSize.X = unWidth; m_whSize.Y = unHeight; }
		inline void AddSubWidget(CWidget* pcWidget) {
			if (pcWidget == nullptr) { return; }
			m_SubWidgets[pcWidget->GetId()] = pcWidget;
		}
		inline void RmvSubWidget(UInt32 unId) {
			auto& itWgt = m_SubWidgets.find(unId);
			if (itWgt == m_SubWidgets.end()) { return; }
			m_SubWidgets.erase(itWgt);
		}
		// --core_methods
		virtual void Enable() = 0;
		virtual void Disable() = 0;
		virtual void Render() = 0;
		virtual void OnMouseEvent(MOUSE_EVENT_RECORD& rmEvt) = 0;
		virtual void OnKeyEvent(MOUSE_EVENT_RECORD& rkEvt) = 0;
	private:
		static IdStack s_IdStack;
	protected:
		UInt32 m_unId = 0;
		String m_strName = "";
		V2xy m_xyCrd = { 0, 0 };
		V2wh m_whSize = { 1, 1 };
		bool m_bIsEnabled = false;

		SubWidgets m_SubWidgets;
	};
	class CMD_API GuiMenuItem : public CWidget
	{
	public:
		GuiMenuItem();
		~GuiMenuItem();

		// --getters
		// --setters
		// --core_methods
		virtual void Enable() override;
		virtual void Disable() override;
		virtual void Render() override;
		virtual void OnMouseEvent(MOUSE_EVENT_RECORD& rmEvt) override;
		virtual void OnKeyEvent(MOUSE_EVENT_RECORD& rkEvt) override;
	private:
	};
}

#endif	// CMD_GUI_H