#pragma once
#include <unordered_map>

#include "Core.h"

struct RelationshipsComponent
{
	std::unordered_map<Entity, uint8_t> Relationships;

	RelationshipsComponent() = default;
};
