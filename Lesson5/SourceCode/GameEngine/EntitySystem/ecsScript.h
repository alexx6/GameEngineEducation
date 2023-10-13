#pragma once
#include "flecs.h"
#include "ScriptProxy.h"

struct ScriptProxyPtr
{
	class CScriptProxy* ptr;
};

void register_ecs_script_system(flecs::world& ecs);


