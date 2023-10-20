#include "XmlEcsParser.h"

void XmlEcsParser::apply(flecs::entity& entity, std::string configName)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(configName.c_str());
	tinyxml2::XMLElement* params = doc.FirstChildElement("entityParams");

	if (!params)
		return;

	//Applying components with multiple parameters
	applyGravity(entity, params->FirstChildElement("gravity"));
	applyPosition(entity, params->FirstChildElement("position"));
	applyVelocity(entity, params->FirstChildElement("velocity"));
	applyBouncePlane(entity, params->FirstChildElement("bouncePlane"));

	//Applying properties and components with single parameter

	if (tinyxml2::XMLElement* el = params->FirstChildElement("bounciness"))
		entity.set(Bounciness{ el->FloatText() });

	if (tinyxml2::XMLElement* el = params->FirstChildElement("frictionAmount"))
		entity.set(FrictionAmount{ el->FloatText() });

	if (tinyxml2::XMLElement* el = params->FirstChildElement("jumpSpeed"))
		entity.set(JumpSpeed{ el->FloatText() });

	if (params->FirstChildElement("cubeMesh"))
		entity.add<CubeMesh>();

	if (params->FirstChildElement("controllable"))
		entity.add<Controllable>();
}

void XmlEcsParser::applyGravity(flecs::entity& entity, tinyxml2::XMLElement* e)
{
	if (!e)
		return;
	
	tinyxml2::XMLElement* x = e->FirstChildElement("x");
	tinyxml2::XMLElement* y = e->FirstChildElement("y");
	tinyxml2::XMLElement* z = e->FirstChildElement("z");

	entity.set(Gravity{ x ? x->FloatText() : 0.0f,
						y ? y->FloatText() : 0.0f,
						z ? z->FloatText() : 0.0f });
}

void XmlEcsParser::applyPosition(flecs::entity& entity, tinyxml2::XMLElement* e)
{
	if (!e)
		return;

	tinyxml2::XMLElement* x = e->FirstChildElement("x");
	tinyxml2::XMLElement* y = e->FirstChildElement("y");
	tinyxml2::XMLElement* z = e->FirstChildElement("z");

	entity.set(Position{ x ? x->FloatText() : 0.0f,
						y ? y->FloatText() : 0.0f,
						z ? z->FloatText() : 0.0f });
}

void XmlEcsParser::applyVelocity(flecs::entity& entity, tinyxml2::XMLElement* e)
{
	if (!e)
		return;

	tinyxml2::XMLElement* x = e->FirstChildElement("x");
	tinyxml2::XMLElement* y = e->FirstChildElement("y");
	tinyxml2::XMLElement* z = e->FirstChildElement("z");

	entity.set(Velocity{ x ? x->FloatText() : 0.0f,
						y ? y->FloatText() : 0.0f,
						z ? z->FloatText() : 0.0f });
}

void XmlEcsParser::applyBouncePlane(flecs::entity& entity, tinyxml2::XMLElement* e)
{
	if (!e)
		return;

	tinyxml2::XMLElement* x = e->FirstChildElement("x");
	tinyxml2::XMLElement* y = e->FirstChildElement("y");
	tinyxml2::XMLElement* z = e->FirstChildElement("z");
	tinyxml2::XMLElement* w = e->FirstChildElement("w");

	entity.set(BouncePlane{ x ? x->FloatText() : 0.0f,
						y ? y->FloatText() : 0.0f,
						z ? z->FloatText() : 0.0f,
						w ? w->FloatText() : 0.0f });
}
