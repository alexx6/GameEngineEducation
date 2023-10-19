#include "ecsScript.h"
#include "ecsSystems.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_script_system(flecs::world& ecs)
{

    static auto inputQuery = ecs.query<InputHandlerPtr>();

    ecs.system<Velocity, const Speed, ScriptProxyPtr, const Controllable>()
        .each([&](flecs::entity e, Velocity& vel, const Speed& spd, ScriptProxyPtr spp, const Controllable&)
        {
            inputQuery.each([&](InputHandlerPtr input)
                {
                    spp.ptr->getSystem()->controlScript(vel.x, e.delta_time(), 
                    input.ptr->GetInputState().test(eIC_GoLeft), input.ptr->GetInputState().test(eIC_GoRight));
                });
        });
}