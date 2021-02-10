#ifndef NWC_ENGINE_STATES
#define NWC_ENGINE_STATES

#include <nwc_core.hpp>
#include <nwc_engine.h>

namespace NWC
{
	class NWC_API CmdMenuState : public AEngineState
	{
	public:
		CmdMenuState();
		~CmdMenuState();
		// --core_methods
		virtual bool Init() override;
		virtual void OnQuit() override;
		virtual void Update() override;
		virtual void OnEvent(MouseEvent& rmEvt) override;
		virtual void OnEvent(KeyboardEvent& rkEvt) override;
		virtual void OnEvent(WindowEvent& rwEvt) override;
	private:
		CmdEngine& rCmd;
	};
}

#endif	// NWC_ENGINE_STATES