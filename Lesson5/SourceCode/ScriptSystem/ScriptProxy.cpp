#include "ScriptProxy.h"


CScriptProxy::CScriptProxy()
{
	m_scriptSystem = new CScriptSystem();
}

CScriptSystem* CScriptProxy::getSystem()
{
	return m_scriptSystem;
}
