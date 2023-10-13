#include "ScriptSystem.h"
#include <fstream>
#include <sstream>

CScriptSystem::CScriptSystem()
{
    return;
}

void CScriptSystem::initControlScript()
{  
    std::ifstream f("controlScript.lua");
    if (!f)
        return;
    std::stringstream ss;
    ss << f.rdbuf();
    script = ss.str();
}


void CScriptSystem::controlScript(float& vel, InputHandler* ptr, const float dt)
{
    sol::state lua1;
    lua1.open_libraries();
    lua1["dt"] = dt;
    lua1["testLeft"] = ptr->GetInputState().test(eIC_GoLeft);
    lua1["testRight"] = ptr->GetInputState().test(eIC_GoRight);
    float dd = lua1.script(script);
    vel += dd;
}
