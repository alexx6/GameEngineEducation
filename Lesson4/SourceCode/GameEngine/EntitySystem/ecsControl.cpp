#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();

  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVel = 0.f;
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVel -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVel += spd;
        vel.x += deltaVel * e.delta_time();
      });
    });

  ecs.system<IntervalBetweenShots, ReloadSettings, const CubeSpawner>()
    .each([&](flecs::entity e, IntervalBetweenShots& interval, ReloadSettings& reload, const CubeSpawner&)
    {
        float dt = e.delta_time();
        interval.left -= dt;
        reload.timeLeft -= dt;
        if (interval.left <= 0 && reload.timeLeft <= 0)
        {
            inputQuery.each([&](InputHandlerPtr input)
            {
                if (input.ptr->GetInputState().test(eIC_Shoot))
                {
                    e.world().entity()
                        .set(Position{ 0.f, 5.f, 0.f })
                        .set(Velocity{ 0.f, 0.f, 10.f })
                        .set(Speed{ 10.f })
                        .set(JumpSpeed{ 10.f })
                        .set(Gravity{ 0.f, -9.8065f, 0.f })
                        .set(BouncePlane{ 0.f, 1.f, 0.f, -10.f })
                        .set(Bounciness{ 0.9f })
                        .set(TimeToLive{ 5.0f, false })
                        .add<CanCollect>()
                        .add<DetectCollisions>()
                        .add<Controllable>()
                        .add<CubeMesh>();
                    
                    interval.left = interval.interval;
                    reload.shotsLeft -= 1;
                    if (!reload.shotsLeft)
                    {
                        reload.shotsLeft = reload.shots;
                        reload.timeLeft = reload.duration;
                    }
                }
            });

        }
    });


  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });
}

