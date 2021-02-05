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
		CPixel pxDefault;
		CPixel pxDisable;
		CPixel pxFocus;
		CPixel pxAction;
		CPixel pxDraw;
		V2i xyCoord;
		V2i whSize;
		V4i rectPadding;
	public:
		CWidget();
		virtual ~CWidget();
		// --getters
		inline const char* GetName() const { return &m_strName[0]; }
		inline UInt32 GetId() const { return m_unId; }
		inline CWidgetStates GetState() const { return m_wState; }
		// --setters
		void SetName(const char* strName);
		void SetAction(const Action& rAct);
		// --core_methods
		virtual void OnDraw() = 0;
		virtual void OnState(CWidgetStates wState) = 0;
	protected:
		String m_strName;
		UInt32 m_unId = 0;
		CWidgetStates m_wState;
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
		virtual void OnState(CWidgetStates wState) override;
	};
}

#endif	// CMD_GUI_H