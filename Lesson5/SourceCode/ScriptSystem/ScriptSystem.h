#include "IScriptSystem.h"
#include <sol/sol.hpp>
#include <string>
#include "../GameEngine/InputHandler.h"

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
public:
	CScriptSystem();

	virtual void Update() override {};
	virtual void ProcessScript(IScriptProxy* scriptProxy) override {};
	void controlScript(float& vel, const float dt, bool testLeft, bool testRight);
private:
	sol::state lua;
	sol::load_result script;
};