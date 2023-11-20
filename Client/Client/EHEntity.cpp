#include "pch.h"
#include "EHEntity.h"

UINT_PTR Entity::g_NextID = 0;


Entity::Entity()
	: m_ID(g_NextID++)
	, m_bDead(false)
{
}

Entity::Entity(const Entity& _other)
	: m_ID(g_NextID++)
	, m_bDead(false)
{
}

Entity::~Entity()
{
}
