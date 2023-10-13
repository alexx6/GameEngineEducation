#include "IScriptSystem.h"
#include <sol/sol.hpp>
#include <string>
#include <InputHandler.h>

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
public:
	CScriptSystem();

	virtual void Update() override {};
	//virtual IScriptProxy* CreateProxy(const char* filename) override;
	virtual void ProcessScript(IScriptProxy* scriptProxy) override {};
	void controlScript(float& vel, InputHandler* ptr, const float dt);
	void initControlScript();
private:
	sol::state lua;
	std::string script;
};