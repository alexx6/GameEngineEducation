#include "ecsPhys.h"
#include "ecsControl.h"
#include "ecsMesh.h"
#include <stdlib.h>
#include <math.h>

static float rand_flt(float from, float to)
{
  return from + (float(rand()) / RAND_MAX) * (to - from);
}

void register_ecs_phys_systems(flecs::world &ecs)
{
    static auto canCollectQuery = ecs.query<CanCollect, Position>();

  ecs.system<Velocity, const Gravity, BouncePlane*, Position*>()
    .each([&](flecs::entity e, Velocity &vel, const Gravity &grav, BouncePlane *plane, Position *pos)
    {
      if (plane && pos)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
          return;
      }
      vel.x += grav.x * e.delta_time();
      vel.y += grav.y * e.delta_time();
      vel.z += grav.z * e.delta_time();
    });


  ecs.system<Velocity, Position, const BouncePlane, const Bounciness>()
    .each([&](Velocity &vel, Position &pos, const BouncePlane &plane, const Bounciness &bounciness)
    {
      float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
      float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
      if (dotPos < plane.w)
      {
        pos.x -= (dotPos - plane.w) * plane.x;
        pos.y -= (dotPos - plane.w) * plane.y;
        pos.z -= (dotPos - plane.w) * plane.z;

        vel.x -= (1.f + bounciness.val) * plane.x * dotVel;
        vel.y -= (1.f + bounciness.val) * plane.y * dotVel;
        vel.z -= (1.f + bounciness.val) * plane.z * dotVel;
      }
    });


  ecs.system<Velocity, const FrictionAmount>()
    .each([&](flecs::entity e, Velocity &vel, const FrictionAmount &friction)
    {
      vel.x -= vel.x * friction.val * e.delta_time();
      vel.y -= vel.y * friction.val * e.delta_time();
      vel.z -= vel.z * friction.val * e.delta_time();
    });


  ecs.system<Position, const Velocity>()
    .each([&](flecs::entity e, Position &pos, const Velocity &vel)
    {
      pos.x += vel.x * e.delta_time();
      pos.y += vel.y * e.delta_time();
      pos.z += vel.z * e.delta_time();
    });


  ecs.system<Position, const ShiverAmount>()
    .each([&](flecs::entity e, Position &pos, const ShiverAmount &shiver)
    {
      pos.x += rand_flt(-shiver.val, shiver.val);
      pos.y += rand_flt(-shiver.val, shiver.val);
      pos.z += rand_flt(-shiver.val, shiver.val);
    });

  ecs.system < const BouncePlane, Position, TimeToLive, const DetectCollisions >()
      .each([&](flecs::entity e, const BouncePlane& plane, Position& pos, TimeToLive& timeToLive, const DetectCollisions&)
    {
        float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
        if (dotPos < plane.w)
        {
            timeToLive.enabled = true;
        }
    });
    
  ecs.system<TimeToLive, RenderProxyPtr>()
    .each([&](flecs::entity e, TimeToLive& timeToLive, RenderProxyPtr& proxy)
    {
        if (timeToLive.left <= 0.0f)
        {
            delete proxy.ptr;
            e.destruct();
            return;
        }

        if (timeToLive.enabled)
            timeToLive.left -= e.delta_time();
    });

  static auto cubeSpawnerQuery = ecs.query <CubeSpawner, ReloadSettings>();

  ecs.system<Position, Collectible, RenderProxyPtr>()
    .each([&](flecs::entity e_c, Position& position_c, Collectible& collectible, RenderProxyPtr& proxy)
    {
        canCollectQuery.each([&](flecs::entity e, CanCollect&, Position& position)
        {
            if (fabsf(position_c.x - position.x) < 1.0f
                && fabsf(position_c.y - position.y) < 1.0f
                && fabsf(position_c.z - position.z) < 1.0f)
            {
                delete proxy.ptr;
                e_c.destruct();

                cubeSpawnerQuery.each([&](flecs::entity e_s, CubeSpawner&, ReloadSettings& reload)
                {
                        reload.shotsLeft += collectible.points;
                        if (reload.shotsLeft > reload.shots)
                            reload.shotsLeft = reload.shots;
                });
            }
        });
    });
}

