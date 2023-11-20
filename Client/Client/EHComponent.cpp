#include "pch.h"
#include "EHComponent.h"

#include "EHObj.h"

Component::Component(Obj* _Owner)
	: m_pOwner(_Owner)
{
}

Component::~Component()
{
}
