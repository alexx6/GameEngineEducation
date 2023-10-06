#pragma once
#include "flecs.h"

struct Controllable {};
struct JumpSpeed { float val; };
struct CubeSpawner{};
struct HasCooldown { float cooldownLeft = 0.0f; int shotsFired = 0; };
struct TimeToLive { float left; bool enabled; };
struct IntervalBetweenShots { float interval; float left; };
struct ReloadSettings { int shots; int shotsLeft; float duration; float timeLeft; };

void register_ecs_control_systems(flecs::world &ecs);

