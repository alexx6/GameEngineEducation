#pragma once

#include <sol/sol.hpp>
#include "IScriptProxy.h"
#include "ScriptSystem.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
public:
	CScriptProxy();
	CScriptSystem* getSystem();
	
private:
	CScriptSystem* m_scriptSystem;
};

