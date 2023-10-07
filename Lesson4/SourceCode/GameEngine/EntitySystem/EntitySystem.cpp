#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    auto cubeSpawner = ecs.entity()
        .set(IntervalBetweenShots{ 0.2f, 0.0f })
        .set(ReloadSettings{ 6, 6, 2.0f, 0.0f })
        .add<CubeSpawner>()
        .add<HasCooldown>();

    auto collectible1 = ecs.entity()
        .set(Position{ 10.f, -5.f, 20.f })
        .set(Collectible{ 3 })
        .add<CubeMesh>();

    auto collectible2 = ecs.entity()
        .set(Position{ -10.f, -5.f, 20.f })
        .set(Collectible{ 0 })
        .add<CubeMesh>();
}

void EntitySystem::Update()
{
    ecs.progress();
}