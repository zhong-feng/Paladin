#pragma once
#include "CItem.h"
class CWeapon :
    public CItem
{
public:
    CWeapon();
    ~CWeapon();

public:
    int attack;

    int strength;
    int intelligence;
};

