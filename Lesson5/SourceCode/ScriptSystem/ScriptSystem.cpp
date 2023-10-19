#include "ScriptSystem.h"
#include <fstream>
#include <sstream>

CScriptSystem::CScriptSystem()
{
    script = lua.load_file("controlScript.lua");
    return;
}

void CScriptSystem::controlScript(float& vel, const float dt, bool testLeft, bool testRight)
{
    lua["dt"] = dt;

    //i know this looks terrible but i kept getting linking errors because of
    //getInputState in inputHandler and lost all hope after hours of trying
    lua["testLeft"] = testLeft;
    lua["testRight"] = testRight;
    float dd = script();
    vel += dd;
}
