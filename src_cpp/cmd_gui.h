#ifndef CMD_GUI_H
#define CMD_GUI_H

#include <cmd_core.hpp>
#include <cmd_structs.h>

namespace CMD
{
	enum CWidgetStates : UInt8 {
		CWS_DEFAULT = 0,
		CWS_DISABLE, CWS_ENABLE,
		CWS_ACT, CWS_DEACT,
		CWS_FOCUS, CWS_DEFOCUS,
		CWS_NEXT, CWS_BACK,
		CWS_MOVE_LT, CWA_MOVE_RT, CWS_MOVE_UP, CWS_MOVE_DN
	};
	class CMD_API CWidget
	{
	public:
		using Action = std::function<UInt32()>;
	public:
		UInt16 colorDefault;
		UInt16 colorDisable;
		UInt16 colorFocus;
		UInt16 colorAction;
		UInt16 colorCurrent;
		V2i xyCoord;
		V2i whSize;
		V4i xywhPadding;
		V4i xywhDrawRect;
	public:
		CWidget();
		virtual ~CWidget();
		// --getters
		inline const char* GetName() const { return &m_strName[0]; }
		inline UInt32 GetId() const { return m_unId; }
		inline CWidgetStates GetState(UInt32 unIdx = 0) const { if (unIdx >= 10) { return CWS_DEFAULT; } return m_wStates[unIdx]; }
		// --setters
		void SetName(const char* strName);
		void SetAction(const Action& rAct);
		// --core_methods
		virtual void OnDraw() = 0;
		virtual void OnEvent(MouseEvent& rmEvt) = 0;
		virtual void OnEvent(KeyboardEvent& rkEvt) = 0;
		virtual UInt32 OnState(CWidgetStates wState) = 0;
	protected:
		String m_strName;
		UInt32 m_unId = 0;
		CWidgetStates m_wStates[10];
		Action m_fnAction;
	private:
		static IdStack s_IdStack;
	};
}
namespace CMD
{
	/// CMenu class for CMD graphical user interface
	class CMD_API CMenuItem : public CWidget
	{
	public:
		CMenuItem();
		virtual ~CMenuItem();
		// --core_methods
		virtual void OnDraw() override;
		virtual void OnEvent(MouseEvent& rmEvt) override;
		virtual void OnEvent(KeyboardEvent& rmEvt) override;
		virtual UInt32 OnState(CWidgetStates wState) override;
	};
}

#endif	// CMD_GUI_H