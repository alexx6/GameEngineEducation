#pragma once
#include "flecs.h"
#include "tinyxml2.h"
#include "EntitySystem/EntitySystem.h"
#include "EntitySystem/ecsSystems.h"
#include "EntitySystem/ecsMesh.h"
#include "EntitySystem/ecsControl.h"
#include "EntitySystem/ecsPhys.h"
#include "EntitySystem/ecsScript.h"
#include <string>

class XmlEcsParser
{
public:
	static void apply(flecs::entity& entity, std::string configName);

private:
	static void applyGravity(flecs::entity& entity, tinyxml2::XMLElement* e);
	static void applyPosition(flecs::entity& entity, tinyxml2::XMLElement* e);
	static void applyVelocity(flecs::entity& entity, tinyxml2::XMLElement* e);
	static void applyBouncePlane(flecs::entity& entity, tinyxml2::XMLElement* e);

};

