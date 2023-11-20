#pragma once
#include "EHEntity.h"


class Obj;

class Component :
    public Entity
{
private:
    Obj* m_pOwner;

public:
    Obj* GetOwner() { return m_pOwner; }


public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc) {}

public:
    virtual Component* Clone() = 0;

public:
    Component(Obj* _Owner);
    ~Component();

    friend class Obj;
};

